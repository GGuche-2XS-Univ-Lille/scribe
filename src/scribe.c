#include <assert.h>
#include <setjmp.h>
#include <inttypes.h>

#include "scribe.h"

#include "log.h"


// TODO Mutexes here instead of requiring it from callers ?

static                jmp_buf                 scribe_savepoint;
static                coap_block_slicer_t     scribe_slicer               = {
    .start = 0,
    .end   = 64,
    .cur   = 0
};
static                coap_pkt_t             *scribe_pdu                  = NULL;
static                size_t                  scribe_written_bytes_count  = 0;
static          const uint8_t                *scribe_data                 = NULL;
static                size_t                  scribe_data_bytesize        = 0;
static                uint32_t                scribe_block_number         = 0;

static inline scribe_code_t write_bytes(const uint8_t *bytes, size_t bytesize) {
    SCRIBE_LOG_DEBUG("(bytes=%p, bytesize=%zu)\n", bytes, bytesize);

    assert(bytes != NULL);
    assert(bytesize > 0);

    if (scribe_slicer.cur >= scribe_slicer.end) {
        SCRIBE_LOG_DEBUG(": scribe_slicer.cur (%zu) > scribe_slicer.end (%zu)"
                         ": returning SCRIBE_OK\n", scribe_slicer.cur, scribe_slicer.end);
        return SCRIBE_CODE_OK;
    }

    const size_t free_bytes_in_pkt_count = scribe_slicer.end - scribe_slicer.cur;
    if (bytesize > free_bytes_in_pkt_count) {
        /* Store as much bytes as possible in the current packet */
        const int res = coap_blockwise_put_bytes_pkt(scribe_pdu, &scribe_slicer,
                                                     bytes, free_bytes_in_pkt_count);
        if (res < 0) {
            SCRIBE_LOG_ERROR(": failed to write %zu remaining free bytes : res=%d\n",
                             free_bytes_in_pkt_count, res);
            return SCRIBE_CODE_WRITE_FAILURE;
        }
#ifdef RIOT_VERSION
        fprintf(stdout, "%.*s", (int)bytesize, (const char *)bytes);
#   ifndef NDEBUG
        fprintf(stdout, "\n");
#   endif
#endif

        scribe_data                 = bytes    + free_bytes_in_pkt_count;
        scribe_data_bytesize        = bytesize - free_bytes_in_pkt_count;
        scribe_written_bytes_count += free_bytes_in_pkt_count;
        scribe_block_number++;

        SCRIBE_LOG_DEBUG(": jumping to savepoint "
                         ": scribe_data=%p, scribe_data_bytesize=%zu,"
                         " scribe_written_bytes_count=%zu, scribe_block_number=%" PRIu32 "\n",
                         scribe_data, scribe_data_bytesize, scribe_written_bytes_count,
                         scribe_block_number);
        longjmp(scribe_savepoint, SCRIBE_CODE_FLUSH);
        /* UNREACHABLE */
    }

    scribe_block_number = 0;
    const int res = coap_blockwise_put_bytes_pkt(scribe_pdu, &scribe_slicer, bytes, bytesize);
    if (res < 0) {
        SCRIBE_LOG_ERROR(": failed to write %zu bytes : res=%d\n", bytesize, res);
        return SCRIBE_CODE_WRITE_FAILURE;
    }

    scribe_written_bytes_count += bytesize;
    scribe_data                 = NULL;
    scribe_data_bytesize        = 0;

#ifdef RIOT_VERSION
    fprintf(stdout, "%.*s", (int)bytesize, (const char *)bytes);
#   ifndef NDEBUG
    fprintf(stdout, "\n");
#   endif
#endif

    SCRIBE_LOG_DEBUG(": scribe_written_bytes_count=%zu bytes\n", scribe_written_bytes_count);
    return SCRIBE_CODE_OK;
}

scribe_code_t scribe_initialize(coap_pkt_t *pdu, uint8_t *buffer, size_t buffer_bytesize) {
    SCRIBE_LOG_DEBUG("(pdu=%p, buffer:%p, buffer_bytesize:%zu)\n", pdu, buffer, buffer_bytesize);

    if (scribe_pdu != NULL) {
        SCRIBE_LOG_ERROR(": already initialized\n");
        return SCRIBE_CODE_ALREADY_INITIALIZED;
    }

    if (pdu == NULL) {
        SCRIBE_LOG_ERROR(": PDU is NULL\n");
        return SCRIBE_CODE_NO_PDU;
    }

    if (buffer == NULL) {
        SCRIBE_LOG_ERROR(": buffer is NULL\n");
        return SCRIBE_CODE_NO_BUFFER;
    }

    if (buffer_bytesize == 0) {
        SCRIBE_LOG_ERROR(": invalid buffer bytesize (0)\n");
        return SCRIBE_CODE_INVALID_BUFFER_BYTESIZE;
    }

    coap_block2_init(pdu, &scribe_slicer);

    /* Check the requested block_number is the same that the expected one */
    if (scribe_data != NULL) {
        uint32_t blknum = 0;
        uint8_t szx     = 0;
        const int res   = coap_get_blockopt(pdu, COAP_OPT_BLOCK2, &blknum, &szx);
        if (res < 0) {
            SCRIBE_LOG_ERROR(": failed to get coap blockopt : %d\n", res);
            return SCRIBE_CODE_INVALID_BLOCK_NUMBER;
        }
        if (blknum != scribe_block_number) {
            SCRIBE_LOG_ERROR(": block number (%" PRIu32
                             " differs from expected block number (%" PRIu32 ")\n",
                             blknum, scribe_block_number);
            return SCRIBE_CODE_INVALID_BLOCK_NUMBER;
        }
    }

    ssize_t res = gcoap_resp_init(pdu, buffer, buffer_bytesize, COAP_CODE_CONTENT);
    if (res < 0) {
        SCRIBE_LOG_ERROR(": failed to initialize coap response : %zd\n", res);
        return SCRIBE_CODE_INITIALIZATION_FAILURE;
    }

    res = coap_opt_add_format(pdu, COAP_FORMAT_JSON);
    if (res < 0) {
        SCRIBE_LOG_ERROR(": failed to add coap format option : %zd\n", res);
        return SCRIBE_CODE_INITIALIZATION_FAILURE;
    }

    res = coap_opt_add_block2(pdu, &scribe_slicer, true);
    if (res < 0) {
        SCRIBE_LOG_ERROR(": failed to add block2 option : %zd\n", res);
        return SCRIBE_CODE_INITIALIZATION_FAILURE;
    }

    res = coap_opt_finish(pdu, COAP_OPT_FINISH_PAYLOAD);
    if (res < 0) {
        SCRIBE_LOG_ERROR(": failed to finish options : %zd\n", res);
        return SCRIBE_CODE_INITIALIZATION_FAILURE;
    }

    scribe_pdu                 = pdu;
    scribe_written_bytes_count = 0;
    scribe_block_number        = 0;

    scribe_code_t return_value = (scribe_code_t)setjmp(scribe_savepoint);
    if (return_value == SCRIBE_CODE_OK) {
        /* We are not coming back from write_bytes */
        if (scribe_data != NULL) {
            /* There are some bytes left from former write_bytes call, let's push them to coap */
            coap_block_slicer_t *this_slicer = &scribe_slicer;
            this_slicer->cur = this_slicer->start;

            const uint8_t *data            = scribe_data;
                  size_t   data_bytesize   = scribe_data_bytesize;

            return_value = write_bytes(data, data_bytesize);
        }
    } /* else we are coming back from write_bytes, which has returned SCRIBE_CODE_FLUSH */

    return return_value;
}

scribe_code_t scribe_write(const void *data, size_t bytesize) {
    SCRIBE_LOG_DEBUG("(data=%p, bytesize=%zu)\n", data, bytesize);

    if (scribe_pdu == NULL) {
        SCRIBE_LOG_ERROR(": Not initialized\n");
        return SCRIBE_CODE_NOT_INITIALIZED;
    }
    if (data == NULL) {
        SCRIBE_LOG_ERROR(": No data\n");
        return SCRIBE_CODE_NO_DATA;
    }
    if (bytesize == 0) {
        SCRIBE_LOG_ERROR(": Invalid bytesize : %zu\n", bytesize);
        return SCRIBE_CODE_INVALID_DATA_BYTESIZE;
    }

    return write_bytes(data, bytesize);
}

size_t scribe_get_written_bytes_count(void) {
    SCRIBE_LOG_DEBUG("():written bytes count:%zu\n", scribe_written_bytes_count);
    return scribe_written_bytes_count;
}

void scribe_release(void) {
    SCRIBE_LOG_DEBUG("()\n");

    coap_block2_finish(&scribe_slicer);
    scribe_pdu                 = NULL;
    scribe_written_bytes_count = 0;
    scribe_data                = NULL;
    scribe_data_bytesize       = 0;
    scribe_block_number        = 0;
}
