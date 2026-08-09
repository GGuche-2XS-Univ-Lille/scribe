#include <assert.h>

#include "scribe.h"

#include "log.h"

// TODO Mutexes here instead of requiring it from callers ?

static scribe_sink_t **scribe_sinks       = NULL;
static size_t          scribe_sinks_count = 0;

static size_t          scribe_written_bytes_count = 0;

static inline scribe_code_t scribe_check(void) {
    SCRIBE_LOG_DEBUG("()\n");
    const scribe_code_t code = ((scribe_sinks == NULL) || (scribe_sinks_count == 0)) ?
                               SCRIBE_CODE_NOT_INITIALIZED : SCRIBE_CODE_OK;

    if (code != SCRIBE_CODE_OK) {
        SCRIBE_LOG_DEBUG(":%d (%d)\n", scribe_code_get_label(code), code);
    }

    return code;
}

scribe_code_t scribe_initialize(scribe_sink_t **sinks, size_t sinks_count) {
    SCRIBE_LOG_DEBUG("(sinks=%p, sinks_count:%zu)\n", sinks, sinks_count);

    if (scribe_sinks != NULL) {
        SCRIBE_LOG_ERROR(": already initialized\n");
        return SCRIBE_CODE_ALREADY_INITIALIZED;
    }

    if (sinks == NULL) {
        SCRIBE_LOG_ERROR(": sinks array is NULL\n");
        return SCRIBE_CODE_NULL_SINKS;
    }

    if (sinks_count == 0) {
        SCRIBE_LOG_ERROR(": invalid sinks count : %zu\n", sinks_count);
        return SCRIBE_CODE_INVALID_SINKS_COUNT;
    }

    scribe_code_t code;
    for (size_t i = 0; i < sinks_count; i++) {
        code = scribe_sink_check(sinks[i]);
        if (code != SCRIBE_CODE_OK) {
            SCRIBE_LOG_ERROR(": error while processing sink %zu : %s (%d)\n",
                             i, scribe_code_get_label(code), code);
            return code;
        }
    }

    scribe_sinks               = sinks;
    scribe_sinks_count         = sinks_count;
    scribe_written_bytes_count = 0;
    return SCRIBE_CODE_OK;
}

scribe_code_t scribe_prepare(void **data) {
    SCRIBE_LOG_DEBUG("(data=%p)\n", data);

    scribe_code_t code = scribe_check();
    if (code != SCRIBE_CODE_OK) {
        return code;
    }
    for (size_t i = 0; i < scribe_sinks_count; i++) {
        code = scribe_sink_prepare(scribe_sinks[i], data[i]);
        if (code != SCRIBE_CODE_OK) {
            SCRIBE_LOG_ERROR(": error while processing sink %zu : %s (%d)\n",
                             i, scribe_code_get_label(code), code);
            return code;
        }
    }
    scribe_written_bytes_count = 0;
    return SCRIBE_CODE_OK;
}

scribe_code_t scribe_write(const void *data, size_t bytesize) {
    SCRIBE_LOG_DEBUG("(data=%p, bytesize=%zu)\n", data, bytesize);

    scribe_code_t code = scribe_check();
    if (code != SCRIBE_CODE_OK) {
        return code;
    }
    if (data == NULL) {
        SCRIBE_LOG_ERROR(": No data\n");
        return SCRIBE_CODE_NO_DATA;
    }
    if (bytesize == 0) {
        SCRIBE_LOG_ERROR(": Invalid bytesize : %zu\n", bytesize);
        return SCRIBE_CODE_INVALID_DATA_BYTESIZE;
    }
    for (size_t i = 0; i < scribe_sinks_count; i++) {
        code = scribe_sink_write(scribe_sinks[i], data, bytesize);
        if (code != SCRIBE_CODE_OK) {
            SCRIBE_LOG_ERROR(": error while processing sink %zu : %s (%d)\n",
                             i, scribe_code_get_label(code), code);
            return code;
        }
    }
    scribe_written_bytes_count += bytesize;
    return SCRIBE_CODE_OK;
}

size_t scribe_get_written_bytes_count(void) {
    SCRIBE_LOG_DEBUG("():written bytes count:%zu\n", scribe_written_bytes_count);

    return scribe_written_bytes_count;
}

scribe_code_t scribe_commit(size_t *written_bytes_count) {
    SCRIBE_LOG_DEBUG("(written_bytes_count=%p)\n", written_bytes_count);

    scribe_code_t code = scribe_check();
    if (code != SCRIBE_CODE_OK) {
        return code;
    }
    for (size_t i = 0; i < scribe_sinks_count; i++) {
        code = scribe_sink_commit(scribe_sinks[i]);
        if (code != SCRIBE_CODE_OK) {
            SCRIBE_LOG_ERROR(": error while processing sink %zu : %s (%d)\n",
                             i, scribe_code_get_label(code), code);
            return code;
        }
    }
    if (written_bytes_count != NULL) {
        *written_bytes_count = scribe_written_bytes_count;
    }
    scribe_written_bytes_count = 0;
    return SCRIBE_CODE_OK;
}

void scribe_release(void) {
    SCRIBE_LOG_DEBUG("()\n");
    scribe_sinks       = NULL;
    scribe_sinks_count = 0;
    scribe_written_bytes_count = 0;
}
