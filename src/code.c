#include "code.h"

#include <assert.h>

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
    /* For some reasons, "arm-none-eabi-gcc 15.2.Rel1 (Build arm-15.86)) 15.2.1 20251203"
     * seems to consider that the enumeration cannot be < O.
     * To the best of my knowledge C enumeration underlying type are usually signed integers,
     * but it appears to not be the case here (stdc version ?)
     */
#if !defined(__arm__) && !defined(__thumb__)
    assert(code >= SCRIBE_CODE_FIRST);
#endif
    assert(code <= SCRIBE_CODE_LAST);
    if (
#if !defined(__arm__) && !defined(__thumb__)
        (code < SCRIBE_CODE_FIRST) ||
#endif
        (code > SCRIBE_CODE_LAST)) {
        return "Unknown scribe code";
    }

    return scribe_code_labels[code];
}
