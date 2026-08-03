#include "coap_sink.h"

#ifdef SCRIBE_COAP_SINK_ENABLED

#include <assert.h>

scribe_code_t scribe_coap_sink_prepare_method(scribe_sink_t *this_sink, void *data) {
    scribe_coap_sink_t *this_coap_sink = (scribe_coap_sink_t *)this_sink;

    scribe_coap_sink_instance_members_t *params = (scribe_coap_sink_instance_members_t *)data;

    assert(this_coap_sink->members.pdu == NULL);
    if (this_coap_sink->members.pdu != NULL) {
        return SCRIBE_CODE_INVALID_SINK_STATE;
    }

    assert(params->pdu != NULL);
    if (params->pdu == NULL) {
        return SCRIBE_CODE_NO_DATA;
    }

    this_coap_sink->members = *params;
    this_coap_sink->members.written_bytes_count = 0;

    return SCRIBE_CODE_OK;
}

scribe_code_t scribe_coap_sink_write_method(scribe_sink_t *this_sink,
                                              const void *data, size_t bytesize) {
    scribe_coap_sink_t *this_coap_sink = (scribe_coap_sink_t *)this_sink;

    if (coap_blockwise_put_bytes_pkt(this_coap_sink->members.pdu,
                                     &(this_coap_sink->members.slicer),
                                     data, bytesize) < 0) {
        return SCRIBE_CODE_WRITE_FAILURE;
    }

    this_coap_sink->members.written_bytes_count += bytesize;
    return SCRIBE_CODE_OK;
}

scribe_code_t scribe_coap_sink_commit_method(scribe_sink_t *this_sink) {
    scribe_coap_sink_t *this_coap_sink = (scribe_coap_sink_t *)this_sink;
    this_coap_sink->members.pdu = NULL;
    return SCRIBE_CODE_OK;
}

const scribe_coap_sink_class_t scribe_coap_sink_class =
    SCRIBE_COAP_SINK_CLASS_INITIALIZER(scribe_coap_sink_prepare_method, \
                                       scribe_coap_sink_write_method,   \
                                       scribe_coap_sink_commit_method);

#endif /* SCRIBE_COAP_SINK_ENABLED */
