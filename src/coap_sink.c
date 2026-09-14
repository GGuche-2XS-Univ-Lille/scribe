#include "coap_sink.h"

#ifdef SCRIBE_COAP_SINK_ENABLED

#include <assert.h>

#include "log.h"

scribe_code_t scribe_coap_sink_prepare_method(scribe_sink_t *this_sink, void *data) {
    SCRIBE_LOG_DEBUG("(this=%p, data=%p)\n", this_sink, data);
    scribe_coap_sink_t *this_coap_sink = (scribe_coap_sink_t *)this_sink;

    assert(this_coap_sink->members.pdu == NULL);
    if (this_coap_sink->members.pdu != NULL) {
        SCRIBE_LOG_ERROR("sink has already a pdu set.\n");
        return SCRIBE_CODE_INVALID_SINK_STATE;
    }

    assert(data != NULL);
    if (data == NULL) {
        SCRIBE_LOG_ERROR("NULL incoming data.\n");
        return SCRIBE_CODE_NO_DATA;
    }

    scribe_coap_sink_prepare_data_t *prepare_data = (scribe_coap_sink_prepare_data_t *)data;

    coap_pkt_t          *pdu    = (coap_pkt_t *)prepare_data->pdu;
    coap_block_slicer_t *slicer = &(this_coap_sink->members.slicer);

    assert(pdu != NULL);
    if (pdu == NULL) {
        SCRIBE_LOG_ERROR("NULL incoming pdu.\n");
        return SCRIBE_CODE_NO_DATA;
    }

    if (prepare_data->buffer == NULL) {
        SCRIBE_LOG_ERROR("NULL incoming buffer.\n");
        return SCRIBE_CODE_NO_DATA;
    }

    if (prepare_data->bytesize == 0) {
        SCRIBE_LOG_ERROR("invalid bytesize (0).\n");
        return SCRIBE_CODE_INVALID_DATA_BYTESIZE;
    }

    coap_block2_init(pdu, slicer);

    ssize_t res =
        gcoap_resp_init(pdu, prepare_data->buffer, prepare_data->bytesize, COAP_CODE_CONTENT);
    if (res < 0) {
        SCRIBE_LOG_ERROR("failed to initialize coap response : %zd\n", res);
        return SCRIBE_CODE_PREPARATION_FAILURE;
    }

    res = coap_opt_add_format(pdu, COAP_FORMAT_TEXT);
    if (res < 0) {
        printf("failed to add coap format option : %zd\n", res);
        return SCRIBE_CODE_PREPARATION_FAILURE;
    }

    res = coap_opt_add_block2(pdu, slicer, true);
    if (res < 0) {
        printf("failed to add block2 option : %zd\n", res);
        return SCRIBE_CODE_PREPARATION_FAILURE;
    }

    res = coap_opt_finish(pdu, COAP_OPT_FINISH_PAYLOAD);
    if (res < 0) {
        printf("failed to finish options : %zd\n", res);
        return SCRIBE_CODE_PREPARATION_FAILURE;
    }

    this_coap_sink->members.pdu = pdu;

    return SCRIBE_CODE_OK;
}

scribe_code_t scribe_coap_sink_write_method(scribe_sink_t *this_sink,
                                            const void *data, size_t bytesize) {
    SCRIBE_LOG_DEBUG("(this=%p, data=%p, bytesize=%zu)\n", this_sink, data, bytesize);
    scribe_coap_sink_t *this_coap_sink = (scribe_coap_sink_t *)this_sink;

    if (coap_blockwise_put_bytes_pkt(this_coap_sink->members.pdu,
                                     &(this_coap_sink->members.slicer),
                                     data, bytesize) < 0) {
        SCRIBE_LOG_ERROR("Failed to write %zu bytes from %p\n");
        return SCRIBE_CODE_WRITE_FAILURE;
    }

    return SCRIBE_CODE_OK;
}

scribe_code_t scribe_coap_sink_commit_method(scribe_sink_t *this_sink) {
    SCRIBE_LOG_DEBUG("(this=%p)\n", this_sink);

    scribe_coap_sink_t *this_coap_sink = (scribe_coap_sink_t *)this_sink;

    coap_block2_finish(&(this_coap_sink->members.slicer));
    this_coap_sink->members.pdu = NULL;
    return SCRIBE_CODE_OK;
}

const scribe_coap_sink_class_t scribe_coap_sink_class =
    SCRIBE_COAP_SINK_CLASS_INITIALIZER(scribe_coap_sink_prepare_method, \
                                       scribe_coap_sink_write_method,   \
                                       scribe_coap_sink_commit_method);

#endif /* SCRIBE_COAP_SINK_ENABLED */
