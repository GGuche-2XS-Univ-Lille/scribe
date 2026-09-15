#include "code.h"

#include <assert.h>

static const char *scribe_code_labels[SCRIBE_CODE_COUNT] = {
    [                              SCRIBE_CODE_OK] = "OK",

    [                 SCRIBE_CODE_NOT_INITIALIZED] = "Not initialized",

    [             SCRIBE_CODE_ALREADY_INITIALIZED] = "Already initialized",
    [                          SCRIBE_CODE_NO_PDU] = "No PDU",
    [                       SCRIBE_CODE_NO_BUFFER] = "No buffer",
    [         SCRIBE_CODE_INVALID_BUFFER_BYTESIZE] = "Invalid buffer bytesize",
    [            SCRIBE_CODE_INVALID_BLOCK_NUMBER] = "Invalid block number",
    [          SCRIBE_CODE_INITIALIZATION_FAILURE] = "Initialization failure",

    [                         SCRIBE_CODE_NO_DATA] = "No data",
    [           SCRIBE_CODE_INVALID_DATA_BYTESIZE] = "Invalid data bytesize",
    [                   SCRIBE_CODE_WRITE_FAILURE] = "Write failure",

    [                           SCRIBE_CODE_FLUSH] = "Flush",
};

const char * scribe_code_get_label(scribe_code_t code) {
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
