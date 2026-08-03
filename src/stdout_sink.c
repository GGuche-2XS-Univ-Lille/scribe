#include <stdio.h>
#include <limits.h>

#include "stdout_sink.h"

scribe_code_t scribe_stdout_sink_prepare_method(scribe_sink_t *this_sink, void *data) {
    /* Does nothing */
    (void)this_sink;
    (void)data;
    return SCRIBE_CODE_OK;
}

scribe_code_t scribe_stdout_sink_write_method(scribe_sink_t *this_sink,
                                              const void *data, size_t bytesize) {
    (void)this_sink;
    if (bytesize > (size_t)INT_MAX) {
        return SCRIBE_CODE_WRITE_FAILURE;
    }
    if (printf("%.*s", (int)bytesize, (const char *)data) < 0) {
        return SCRIBE_CODE_WRITE_FAILURE;
    }
    return SCRIBE_CODE_OK;
}

scribe_code_t scribe_stdout_sink_commit_method(scribe_sink_t *this_sink) {
    /* Does nothing */
    (void)this_sink;
    return SCRIBE_CODE_OK;
}

const scribe_stdout_sink_class_t scribe_stdout_sink_class =
    SCRIBE_STDOUT_SINK_CLASS_INITIALIZER(scribe_stdout_sink_prepare_method, \
                                         scribe_stdout_sink_write_method,   \
                                         scribe_stdout_sink_commit_method);
