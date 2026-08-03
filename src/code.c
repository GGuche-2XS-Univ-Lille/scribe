#include "code.h"

static const char *scribe_code_labels[SCRIBE_CODE_COUNT] = {
    [                              SCRIBE_CODE_OK] = "OK",
    [                 SCRIBE_CODE_NOT_INITIALIZED] = "Not initialized",
    [             SCRIBE_CODE_ALREADY_INITIALIZED] = "Already initialized",
    [                      SCRIBE_CODE_NULL_SINKS] = "NULL sinks",
    [             SCRIBE_CODE_INVALID_SINKS_COUNT] = "Invalid sinks count",
    [                       SCRIBE_CODE_NULL_SINK] = "NULL sink",
    [                 SCRIBE_CODE_NULL_SINK_CLASS] = "NULL sink class",
    [SCRIBE_CODE_INTERNAL_INVALID_METHODS_OFFSETS] = "Internal invalid methods offsets",
    [          SCRIBE_CODE_NULL_SINK_CLASS_METHOD] = "NULL sink class method",
    [              SCRIBE_CODE_INVALID_SINK_STATE] = "Invalid sink state",
    [                         SCRIBE_CODE_NO_DATA] = "No data",
    [           SCRIBE_CODE_INVALID_DATA_BYTESIZE] = "Invalid data bytesize",
    [                   SCRIBE_CODE_WRITE_FAILURE] = "Write failure",
};

const char * scribe_get_code_label(scribe_code_t code) {
    if ((code < SCRIBE_CODE_FIRST) || (code > SCRIBE_CODE_LAST)) {
        return "Unknown scribe code";
    }

    return scribe_code_labels[code];
}
