#include "fake_nanocoap.h"

#ifdef SCRIBE_COAP_SINK_ENABLED

#include <stdio.h>
#include <inttypes.h>
#include <errno.h>
#include <limits.h>

#define FAKE_NANOCOAP_LOG_FUNCTION(file_ptr, format, ...)                                       \
do {                                                                                            \
    fprintf(file_ptr, "FAKE_NANOCOAP:%s:%d:" format, __func__, __LINE__, ##__VA_ARGS__); \
} while (0)

#define FAKE_NANOCOAP_LOG_FUNCTION_INFO_EX(file_ptr, format, ...) \
FAKE_NANOCOAP_LOG_FUNCTION(file_ptr, "[INFO]:" format, ##__VA_ARGS__)

#define FAKE_NANOCOAP_LOG_FUNCTION_ERROR_EX(file_ptr, format, ...) \
FAKE_NANOCOAP_LOG_FUNCTION(file_ptr, "[ERROR]:" format, ##__VA_ARGS__)

#define FAKE_NANOCOAP_LOG_FUNCTION_INFO(format, ...) \
FAKE_NANOCOAP_LOG_FUNCTION_INFO_EX(stdout, format, ##__VA_ARGS__)

#define FAKE_NANOCOAP_LOG_FUNCTION_ERROR(format, ...) \
FAKE_NANOCOAP_LOG_FUNCTION_ERROR_EX(stderr, format, ##__VA_ARGS__)

void coap_block2_init(coap_pkt_t *pkt, coap_block_slicer_t *slicer) {
    FAKE_NANOCOAP_LOG_FUNCTION_INFO("(pkt=%p, slicer=%p\n", pkt, slicer);
}

int gcoap_resp_init(coap_pkt_t *pdu, uint8_t *buf, size_t len, unsigned code) {
    FAKE_NANOCOAP_LOG_FUNCTION_INFO("(pdu=%p, buf=%p, len=%zu, code=%x\n", pdu, buf, len, code);
    return 0;
}

ssize_t coap_opt_add_format(coap_pkt_t *pkt, uint16_t format) {
    FAKE_NANOCOAP_LOG_FUNCTION_INFO("(pkt=%p, format=0x%" PRIu16 ")\n", pkt, format);
    return 0;
}

ssize_t coap_opt_add_block2(coap_pkt_t *pkt, coap_block_slicer_t *slicer, bool more) {
    FAKE_NANOCOAP_LOG_FUNCTION_INFO("(pkt=%p, slicer=%p, more=%s)\n",
                                    pkt, slicer, (more) ? "true" : "false");
    return 0;
}

ssize_t coap_opt_finish(coap_pkt_t *pkt, uint16_t flags) {
    FAKE_NANOCOAP_LOG_FUNCTION_INFO("(pkt=%p, 0x%" PRIx16 ")\n", pkt, flags);
    return 0;
}

int coap_blockwise_put_bytes_pkt(coap_pkt_t *pdu, coap_block_slicer_t *slicer,
                                 const void *c, size_t len) {
    FAKE_NANOCOAP_LOG_FUNCTION_INFO("(pdu=%p, slicer=%p, data=%p, len:%zu)\n",
                                    pdu, slicer, c, len);
    if (len > (size_t)INT_MAX) {
        FAKE_NANOCOAP_LOG_FUNCTION_ERROR("Not enough space in buffer (max=%d)\n", INT_MAX);
        return -EOVERFLOW;
    }
    fprintf(stdout, "%.*s", (int)len, (const char *)c);
    return 0;
}

bool coap_block2_finish(coap_block_slicer_t *slicer) {
    FAKE_NANOCOAP_LOG_FUNCTION_INFO("(slicer=%p\n", slicer);
    return true;
}

#endif /* SCRIBE_COAP_SINK_ENABLED */
