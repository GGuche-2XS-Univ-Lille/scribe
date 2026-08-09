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

    coap_pkt_t *pdu = (coap_pkt_t *)data;

    assert(pdu != NULL);
    if (pdu == NULL) {
        SCRIBE_LOG_ERROR("NULL incoming pdu.\n");
        return SCRIBE_CODE_NO_DATA;
    }

    this_coap_sink->members.pdu = pdu;

    coap_block2_init(pdu, &(this_coap_sink->members.slicer));


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
    this_coap_sink->members.pdu = NULL;
    return SCRIBE_CODE_OK;
}

const scribe_coap_sink_class_t scribe_coap_sink_class =
    SCRIBE_COAP_SINK_CLASS_INITIALIZER(scribe_coap_sink_prepare_method, \
                                       scribe_coap_sink_write_method,   \
                                       scribe_coap_sink_commit_method);

#endif /* SCRIBE_COAP_SINK_ENABLED */
