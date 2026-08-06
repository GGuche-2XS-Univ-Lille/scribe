#include "log.h"

#ifdef SCRIBE_LOG_ENABLED
#include <assert.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>

static const char *scribe_log_severity_level_labels[SCRIBE_LOG_SEVERITY_LEVELS_COUNT] = {
    [  SCRIBE_LOG_SEVERITY_LEVEL_EMERGENCY] = SCRIBE_LOG_SEVERITY_LEVEL_EMERGENCY_LABEL,
    [      SCRIBE_LOG_SEVERITY_LEVEL_ALERT] = SCRIBE_LOG_SEVERITY_LEVEL_ALERT_LABEL,
    [   SCRIBE_LOG_SEVERITY_LEVEL_CRITICAL] = SCRIBE_LOG_SEVERITY_LEVEL_CRITICAL_LABEL,
    [      SCRIBE_LOG_SEVERITY_LEVEL_ERROR] = SCRIBE_LOG_SEVERITY_LEVEL_ERROR_LABEL,
    [    SCRIBE_LOG_SEVERITY_LEVEL_WARNING] = SCRIBE_LOG_SEVERITY_LEVEL_WARNING_LABEL,
    [     SCRIBE_LOG_SEVERITY_LEVEL_NOTICE] = SCRIBE_LOG_SEVERITY_LEVEL_NOTICE_LABEL,
    [SCRIBE_LOG_SEVERITY_LEVEL_INFORMATION] = SCRIBE_LOG_SEVERITY_LEVEL_INFORMATION_LABEL,
#ifndef NDEBUG
    [      SCRIBE_LOG_SEVERITY_LEVEL_DEBUG] = SCRIBE_LOG_SEVERITY_LEVEL_DEBUG_LABEL,
#endif
};

static scribe_log_severity_level_t scribe_log_severity_level = SCRIBE_LOG_SEVERITY_LEVEL_DEFAULT;

static inline bool scribe_log_check_severity_level(scribe_log_severity_level_t severity_level) {
    assert(severity_level >= SCRIBE_LOG_SEVERITY_LEVEL_FIRST);
    assert(severity_level <= SCRIBE_LOG_SEVERITY_LEVEL_LAST);
    const bool result =     (severity_level >= SCRIBE_LOG_SEVERITY_LEVEL_FIRST)
                        &&  (severity_level <= SCRIBE_LOG_SEVERITY_LEVEL_LAST);
    return result;
}

void scribe_log_set_severity_level(scribe_log_severity_level_t severity_level) {
    if (scribe_log_check_severity_level(severity_level) == true) {
        scribe_log_severity_level = severity_level;
    }
}

scribe_log_severity_level_t scribe_log_get_severity_level(void) {
    return scribe_log_severity_level;
}

const char *scribe_log_get_severity_level_label(scribe_log_severity_level_t severity_level) {
    if (scribe_log_check_severity_level(severity_level) == false) {
        return SCRIBE_LOG_SEVERITY_LEVEL_UNKNOWN_LABEL;
    }
    return scribe_log_severity_level_labels[severity_level];
}

void scribe_log(scribe_log_severity_level_t severity_level, const char *format, ...) {
    if (severity_level > scribe_log_severity_level) {
        return;
    }

    const char *severity_level_label = scribe_log_get_severity_level_label(severity_level);
    va_list ap;

    (void)printf("%s", severity_level_label);
    va_start(ap, format);
    (void)vprintf(format, ap);
    va_end(ap);
}

#endif /* SCRIBE_LOG_ENABLED */
