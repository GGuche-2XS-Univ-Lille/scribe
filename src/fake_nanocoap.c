#include "fake_nanocoap.h"

#if (!defined(RIOT_VERSION))

#include <stdio.h>
#include <inttypes.h>
#include <errno.h>
#include <limits.h>

#include "log.h"

void coap_block2_init(coap_pkt_t *pkt, coap_block_slicer_t *slicer) {
#ifdef NDEBUG
    (void)pkt;
    (void)slicer;
#endif

    SCRIBE_LOG_DEBUG("(pkt=%p, slicer=%p\n", pkt, slicer);
}

static int mock_coap_get_blockopt_return_value = 0;
int mock_coap_get_blockopt_set_return_value(int value) {
    switch(value) {
        case -1:
            /* FALLTHROUGH */
        case 0:
            /* FALLTHROUGH */
        case 1:
            mock_coap_get_blockopt_return_value = value;
            return 0;
        default:
            return -1;
    }
}

int coap_get_blockopt(coap_pkt_t *pkt, uint16_t option, uint32_t *blknum, uint8_t *szx) {
    if (pkt == NULL)    return -2;
    if (blknum == NULL) return -3;
    if (szx == NULL)    return -4;
    switch(option) {
        case COAP_OPT_Q_BLOCK1:
            /* FALLTHROUGH */
        case COAP_OPT_BLOCK2:
            /* FALLTHROUGH */
        case COAP_OPT_BLOCK1:
            /* FALLTHROUGH */
        case COAP_OPT_Q_BLOCK2:
            break;
        default:
            return -5;
    }
    SCRIBE_LOG_DEBUG("(pkt=%p, option=%" PRIu16 ", blknum=%p, szx=%p)");
    return mock_coap_get_blockopt_return_value;
}

int gcoap_resp_init(coap_pkt_t *pdu, uint8_t *buf, size_t len, unsigned code) {
#ifdef NDEBUG
    (void)pdu;
    (void)buf;
    (void)len;
    (void)code;
#endif
    SCRIBE_LOG_DEBUG("(pdu=%p, buf=%p, len=%zu, code=%x\n", pdu, buf, len, code);
    return 0;
}

ssize_t coap_opt_add_format(coap_pkt_t *pkt, uint16_t format) {
#ifdef NDEBUG
    (void)pkt;
    (void)format;
#endif
    SCRIBE_LOG_DEBUG("(pkt=%p, format=0x%" PRIu16 ")\n", pkt, format);
    return 0;
}

ssize_t coap_opt_add_block2(coap_pkt_t *pkt, coap_block_slicer_t *slicer, bool more) {
#ifdef NDEBUG
    (void)pkt;
    (void)slicer;
    (void)more;
#endif
    SCRIBE_LOG_DEBUG("(pkt=%p, slicer=%p, more=%s)\n",
                                    pkt, slicer, (more) ? "true" : "false");
    return 0;
}

ssize_t coap_opt_finish(coap_pkt_t *pkt, uint16_t flags) {
#ifdef NDEBUG
    (void)pkt;
    (void)flags;
#endif
    SCRIBE_LOG_DEBUG("(pkt=%p, 0x%" PRIx16 ")\n", pkt, flags);
    return 0;
}

int coap_blockwise_put_bytes_pkt(coap_pkt_t *pdu, coap_block_slicer_t *slicer,
                                 const void *c, size_t len) {
#ifdef NDEBUG
    (void)pdu;
    (void)slicer;
#endif
    SCRIBE_LOG_DEBUG("(pdu=%p, slicer=%p, data=%p, len:%zu)\n", pdu, slicer, c, len);
    if (len > (size_t)INT_MAX) {
        SCRIBE_LOG_ERROR("Not enough space in buffer (max=%d)\n", INT_MAX);
        return -EOVERFLOW;
    }
    fprintf(stdout, "%.*s", (int)len, (const char *)c);
    return 0;
}

bool coap_block2_finish(coap_block_slicer_t *slicer) {
#ifdef NDEBUG
    (void)slicer;
#endif
    SCRIBE_LOG_DEBUG("(slicer=%p\n", slicer);
    return true;
}

#endif  /* (!defined(RIOT_VERSION)) */
