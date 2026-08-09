#ifndef SCRIBE_COAP_SINK_H
#define SCRIBE_COAP_SINK_H

#ifdef SCRIBE_COAP_SINK_ENABLED

#include "sink.h"

#ifdef RIOT_VERSION
    #include "net/nanocoap.h"
    #define SCRIBE_COAP_SINK_SLICER_DEFAULT_INITIALIZER() \
    {                                                     \
        .start     = 0,                                   \
        .end       = 0,                                   \
        .cur       = 0,                                   \
        .opt_value = NULL                                 \
    }
#else
    #include "fake_nanocoap.h"
    #define SCRIBE_COAP_SINK_SLICER_DEFAULT_INITIALIZER() 0
#endif

extern scribe_code_t scribe_coap_sink_prepare_method(scribe_sink_t *sink, void *data);
extern scribe_code_t scribe_coap_sink_write_method(scribe_sink_t *sink,
                                                   const void *data, size_t bytesize);
extern scribe_code_t scribe_coap_sink_commit_method(scribe_sink_t *sink);

typedef scribe_sink_class_t scribe_coap_sink_class_t;
extern const scribe_coap_sink_class_t scribe_coap_sink_class;

#define SCRIBE_COAP_SINK_CLASS_INITIALIZER(prepare_method, write_method, commit_method) \
SCRIBE_SINK_CLASS_INITIALIZER(prepare_method, write_method, commit_method)

typedef struct scribe_coap_sink_instance_members_s {
    coap_pkt_t         *pdu;
    coap_block_slicer_t slicer;
} scribe_coap_sink_instance_members_t;

#define SCRIBE_COAP_SINK_INSTANCE_DEFAULT_MEMBERS  NULL

#define SCRIBE_COAP_SINK_INSTANCE_MEMBERS_INITIALIZER(pdu_ptr) \
{                                                              \
    .pdu = pdu_ptr,                                            \
    .slicer = SCRIBE_COAP_SINK_SLICER_DEFAULT_INITIALIZER(),   \
}

#define SCRIBE_COAP_SINK_INSTANCE_MEMBERS_DEFAULT_INITIALIZER() \
SCRIBE_COAP_SINK_INSTANCE_MEMBERS_INITIALIZER( SCRIBE_COAP_SINK_INSTANCE_DEFAULT_MEMBERS )

typedef struct scribe_coap_sink_s {
    const scribe_coap_sink_class_t *klass;
    scribe_coap_sink_instance_members_t members;
} scribe_coap_sink_t;

#define SCRIBE_COAP_SINK_INITIALIZER(pdu_ptr)                         \
{                                                                     \
    .klass   = &scribe_coap_sink_class,                               \
    .members = SCRIBE_COAP_SINK_INSTANCE_MEMBERS_INITIALIZER(pdu_ptr) \
}

#define SCRIBE_COAP_SINK_DEFAULT_INITIALIZER() \
SCRIBE_COAP_SINK_INITIALIZER( SCRIBE_COAP_SINK_INSTANCE_DEFAULT_MEMBERS )

static inline scribe_code_t scribe_coap_sink_prepare(scribe_coap_sink_t *coap_sink,
                                                     void *data) {
    return scribe_sink_prepare((scribe_sink_t *)coap_sink, data);
}

static inline scribe_code_t scribe_coap_sink_write(scribe_coap_sink_t *coap_sink,
                                                   const void *data, size_t bytesize) {
    return scribe_sink_write((scribe_sink_t *)coap_sink, data, bytesize);
}

static inline scribe_code_t scribe_coap_sink_commit(scribe_coap_sink_t *coap_sink) {
    return scribe_sink_commit((scribe_sink_t *)coap_sink);
}

#endif /* SCRIBE_COAP_SINK_ENABLED */
#endif /* SCRIBE_COAP_SINK_H */
