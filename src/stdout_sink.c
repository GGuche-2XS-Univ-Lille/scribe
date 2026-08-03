#include <stdio.h>
#include <limits.h>

#include "stdout_sink.h"

scribe_code_t scribe_stdout_sink_prepare_method(scribe_sink_t *sink, void *data) {
    /* Does nothing */
    (void)sink;
    (void)data;
    return SCRIBE_CODE_OK;
}

scribe_code_t scribe_stdout_sink_start_method(scribe_sink_t *sink) {
    /* Does nothing */
    (void)sink;
    return SCRIBE_CODE_OK;
}

scribe_code_t scribe_stdout_sink_write_method(scribe_sink_t *sink,
                                              const void *data, size_t bytesize) {
    (void)sink;
    if (bytesize > (size_t)INT_MAX) {
        return SCRIBE_CODE_WRITE_FAILURE;
    }
    if (printf("%.*s", (int)bytesize, (const char *)data) < 0) {
        return SCRIBE_CODE_WRITE_FAILURE;
    }
    return SCRIBE_CODE_OK;
}

scribe_code_t scribe_stdout_sink_end_method(scribe_sink_t *sink) {
    (void)sink;
    if (printf("\n") < 0) {
        return SCRIBE_CODE_WRITE_FAILURE;
    }

    return SCRIBE_CODE_OK;
}

scribe_code_t scribe_stdout_sink_commit_method(scribe_sink_t *sink) {
    /* Does nothing */
    (void)sink;
    return SCRIBE_CODE_OK;
}

const scribe_stdout_sink_class_t scribe_stdout_sink_class =
    SCRIBE_STDOUT_SINK_CLASS_INITIALIZER(scribe_stdout_sink_prepare_method, \
                                                                            \
                                         scribe_stdout_sink_start_method,   \
                                         scribe_stdout_sink_write_method,   \
                                         scribe_stdout_sink_end_method,     \
                                                                            \
                                         scribe_stdout_sink_commit_method);
