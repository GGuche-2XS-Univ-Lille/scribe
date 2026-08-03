#include <assert.h>

#include "scribe.h"

// TODO Mutexes ?

static scribe_sink_t **scribe_sinks       = NULL;
static size_t          scribe_sinks_count = 0;

static inline scribe_code_t scribe_check(void) {
    const scribe_code_t code = ((scribe_sinks == NULL) || (scribe_sinks_count == 0)) ?
                               SCRIBE_CODE_NOT_INITIALIZED : SCRIBE_CODE_OK;
    return code;
}

scribe_code_t scribe_initialize(scribe_sink_t **sinks, size_t sinks_count) {
    if (scribe_sinks != NULL) {
        return SCRIBE_CODE_ALREADY_INITIALIZED;
    }

    if (sinks == NULL) {
        return SCRIBE_CODE_NULL_SINKS;
    }

    if (sinks_count == 0) {
        return SCRIBE_CODE_INVALID_SINKS_COUNT;
    }

    scribe_code_t code;
    for (size_t i = 0; i < sinks_count; i++) {
        code = scribe_sink_check(sinks[i]);
        if (code != SCRIBE_CODE_OK) {
            return code;
        }
    }

    scribe_sinks = sinks;
    scribe_sinks_count = sinks_count;
    return SCRIBE_CODE_OK;
}

scribe_code_t scribe_prepare(void **data) {
    scribe_code_t code = scribe_check();
    if (code != SCRIBE_CODE_OK) {
        return code;
    }
    for (size_t i = 0; i < scribe_sinks_count; i++) {
        code = scribe_sink_prepare(scribe_sinks[i], data[i]);
        if (code != SCRIBE_CODE_OK) {
            return code;
        }
    }
    return SCRIBE_CODE_OK;
}

scribe_code_t scribe_start(void) {
    scribe_code_t code = scribe_check();
    if (code != SCRIBE_CODE_OK) {
        return code;
    }
    for (size_t i = 0; i < scribe_sinks_count; i++) {
        code = scribe_sink_start(scribe_sinks[i]);
        if (code != SCRIBE_CODE_OK) {
            return code;
        }
    }
    return SCRIBE_CODE_OK;
}

scribe_code_t scribe_write(const void *data, size_t bytesize) {
    scribe_code_t code = scribe_check();
    if (code != SCRIBE_CODE_OK) {
        return code;
    }
    for (size_t i = 0; i < scribe_sinks_count; i++) {
        code = scribe_sink_write(scribe_sinks[i], data, bytesize);
        if (code != SCRIBE_CODE_OK) {
            return code;
        }
    }
    return SCRIBE_CODE_OK;
}

scribe_code_t scribe_end(void) {
    scribe_code_t code = scribe_check();
    if (code != SCRIBE_CODE_OK) {
        return code;
    }
    for (size_t i = 0; i < scribe_sinks_count; i++) {
        code = scribe_sink_end(scribe_sinks[i]);
        if (code != SCRIBE_CODE_OK) {
            return code;
        }
    }
    return SCRIBE_CODE_OK;
}

scribe_code_t scribe_commit(void) {
    scribe_code_t code = scribe_check();
    if (code != SCRIBE_CODE_OK) {
        return code;
    }
    for (size_t i = 0; i < scribe_sinks_count; i++) {
        code = scribe_sink_commit(scribe_sinks[i]);
        if (code != SCRIBE_CODE_OK) {
            return code;
        }
    }
    return SCRIBE_CODE_OK;
}

void scribe_release(void) {
    scribe_sinks       = NULL;
    scribe_sinks_count = 0;
}
