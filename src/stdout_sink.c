#include <stdio.h>
#include <limits.h>

#include "stdout_sink.h"
#include "log.h"

scribe_code_t scribe_stdout_sink_prepare_method(scribe_sink_t *this_sink, void *data) {
    SCRIBE_LOG_DEBUG("(this=%p, data=%p)\n", this_sink, data);

    /* Does nothing */
    (void)this_sink;
    (void)data;
    return SCRIBE_CODE_OK;
}

scribe_code_t scribe_stdout_sink_write_method(scribe_sink_t *this_sink,
                                              const void *data, size_t bytesize) {
    SCRIBE_LOG_DEBUG("(this=%p, data=%p, bytesize=%zu)\n", this_sink, data, bytesize);

    (void)this_sink;
    if (bytesize > (size_t)INT_MAX) {
        SCRIBE_LOG_ERROR("Cannot write more than %zu bytes (%zu were requested)\n",
                         (size_t)INT_MAX, bytesize);
        return SCRIBE_CODE_WRITE_FAILURE;
    }
    if (printf("%.*s", (int)bytesize, (const char *)data) < 0) {
        SCRIBE_LOG_ERROR("Failed to write bytes\n");
        return SCRIBE_CODE_WRITE_FAILURE;
    }
    return SCRIBE_CODE_OK;
}

scribe_code_t scribe_stdout_sink_commit_method(scribe_sink_t *this_sink) {
    SCRIBE_LOG_DEBUG("(this=%p)\n", this_sink);

    /* Does nothing */
    (void)this_sink;
    return SCRIBE_CODE_OK;
}

const scribe_stdout_sink_class_t scribe_stdout_sink_class =
    SCRIBE_STDOUT_SINK_CLASS_INITIALIZER(scribe_stdout_sink_prepare_method, \
                                         scribe_stdout_sink_write_method,   \
                                         scribe_stdout_sink_commit_method);
