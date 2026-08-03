#ifndef SCRIBE_STDOUT_SINK_H
#define SCRIBE_STDOUT_SINK_H

#include "sink.h"

extern scribe_code_t scribe_stdout_sink_prepare_method(scribe_sink_t *sink, void *data);
extern scribe_code_t scribe_stdout_sink_write_method(scribe_sink_t *sink,
                                                     const void *data, size_t bytesize);
extern scribe_code_t scribe_stdout_sink_commit_method(scribe_sink_t *sink);

typedef scribe_sink_class_t scribe_stdout_sink_class_t;
extern const scribe_stdout_sink_class_t scribe_stdout_sink_class;

#define SCRIBE_STDOUT_SINK_CLASS_INITIALIZER(prepare_method, write_method, commit_method) \
SCRIBE_SINK_CLASS_INITIALIZER(prepare_method, write_method, commit_method)

typedef struct scribe_stdout_sink_s {
    const scribe_stdout_sink_class_t *klass;
} scribe_stdout_sink_t;

#define SCRIBE_STDOUT_SINK_INITIALIZER() \
{                                        \
    .klass = &scribe_stdout_sink_class   \
}

#define SCRIBE_STDOUT_SINK_DEFAULT_INITIALIZER()  SCRIBE_STDOUT_SINK_INITIALIZER()

static inline scribe_code_t scribe_stdout_sink_prepare(scribe_stdout_sink_t *stdout_sink,
                                                       void *data) {
    return scribe_sink_prepare((scribe_sink_t *)stdout_sink, data);
}

static inline scribe_code_t scribe_stdout_sink_write(scribe_stdout_sink_t *stdout_sink,
                                                     const void *data, size_t bytesize) {
    return scribe_sink_write((scribe_sink_t *)stdout_sink, data, bytesize);
}

static inline scribe_code_t scribe_stdout_sink_commit(scribe_stdout_sink_t *stdout_sink) {
    return scribe_sink_commit((scribe_sink_t *)stdout_sink);
}


#endif /* SCRIBE_STDOUT_SINK_H */
