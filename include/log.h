#ifndef SCRIBE_LOG_H
#define SCRIBE_LOG_H

typedef enum scribe_log_severity_level_e {
    SCRIBE_LOG_SEVERITY_LEVEL_EMERGENCY   = 0,
    SCRIBE_LOG_SEVERITY_LEVEL_EMERG       = SCRIBE_LOG_SEVERITY_LEVEL_EMERGENCY,
    SCRIBE_LOG_SEVERITY_LEVEL_ALERT       = 1,
    SCRIBE_LOG_SEVERITY_LEVEL_CRITICAL    = 2,
    SCRIBE_LOG_SEVERITY_LEVEL_CRIT        = SCRIBE_LOG_SEVERITY_LEVEL_CRITICAL,
    SCRIBE_LOG_SEVERITY_LEVEL_ERROR       = 3,
    SCRIBE_LOG_SEVERITY_LEVEL_ERR         = SCRIBE_LOG_SEVERITY_LEVEL_ERROR,
    SCRIBE_LOG_SEVERITY_LEVEL_WARNING     = 4,
    SCRIBE_LOG_SEVERITY_LEVEL_WARN        = SCRIBE_LOG_SEVERITY_LEVEL_WARNING,
    SCRIBE_LOG_SEVERITY_LEVEL_NOTICE      = 5,
    SCRIBE_LOG_SEVERITY_LEVEL_INFORMATION = 6,
    SCRIBE_LOG_SEVERITY_LEVEL_INFO        = SCRIBE_LOG_SEVERITY_LEVEL_INFORMATION,

    SCRIBE_LOG_SEVERITY_LEVEL_FIRST       = SCRIBE_LOG_SEVERITY_LEVEL_EMERGENCY,

#ifndef NDEBUG
    SCRIBE_LOG_SEVERITY_LEVEL_DEBUG       = 7,
    SCRIBE_LOG_SEVERITY_LEVEL_LAST        = SCRIBE_LOG_SEVERITY_LEVEL_DEBUG,
#else
    SCRIBE_LOG_SEVERITY_LEVEL_LAST        = SCRIBE_LOG_SEVERITY_LEVEL_INFORMATION,
#endif

#ifndef SCRIBE_LOG_SEVERITY_LEVEL_DEFAULT
    SCRIBE_LOG_SEVERITY_LEVEL_DEFAULT     = SCRIBE_LOG_SEVERITY_LEVEL_WARNING,
#endif

} scribe_log_severity_level_t;

#define SCRIBE_LOG_SEVERITY_LEVELS_COUNT \
((size_t)(SCRIBE_LOG_SEVERITY_LEVEL_LAST - SCRIBE_LOG_SEVERITY_LEVEL_FIRST + 1))

#define SCRIBE_LOG_SEVERITY_LEVEL_EMERGENCY_LABEL   "[emergency]"
#define SCRIBE_LOG_SEVERITY_LEVEL_EMERG_LABEL       SCRIBE_LOG_SEVERITY_LEVEL_EMERGENCY_LABEL
#define SCRIBE_LOG_SEVERITY_LEVEL_ALERT_LABEL       "[alert]"
#define SCRIBE_LOG_SEVERITY_LEVEL_CRITICAL_LABEL    "[critical]"
#define SCRIBE_LOG_SEVERITY_LEVEL_CRIT_LABEL        SCRIBE_LOG_SEVERITY_LEVEL_CRITICAL_LABEL
#define SCRIBE_LOG_SEVERITY_LEVEL_ERROR_LABEL       "[error]"
#define SCRIBE_LOG_SEVERITY_LEVEL_ERR_LABEL         SCRIBE_LOG_SEVERITY_LEVEL_ERR_LABEL,
#define SCRIBE_LOG_SEVERITY_LEVEL_WARNING_LABEL     "[warning]"
#define SCRIBE_LOG_SEVERITY_LEVEL_WARN_LABEL        SCRIBE_LOG_SEVERITY_LEVEL_WARNING_LABEL
#define SCRIBE_LOG_SEVERITY_LEVEL_NOTICE_LABEL      "[notice]"
#define SCRIBE_LOG_SEVERITY_LEVEL_INFORMATION_LABEL "[information]"
#define SCRIBE_LOG_SEVERITY_LEVEL_INFO_LABEL        SCRIBE_LOG_SEVERITY_LEVEL_INFORMATION_LABEL

#ifndef NDEBUG
#   define SCRIBE_LOG_SEVERITY_LEVEL_DEBUG_LABEL    "[debug]"
#endif

#define SCRIBE_LOG_SEVERITY_LEVEL_UNKNOWN_LABEL     "[unknown]"

#ifdef SCRIBE_LOG_ENABLED

extern void scribe_log_set_severity_level(scribe_log_severity_level_t severity_level);
extern scribe_log_severity_level_t scribe_log_get_severity_level(void);
extern const char *scribe_log_get_severity_level_label(scribe_log_severity_level_t severity_level);
extern void scribe_log(scribe_log_severity_level_t severity_level, const char *format, ...);

#define SCRIBE_LOG(severity_level, format, ...)                                                   \
do {                                                                                              \
    scribe_log(severity_level, ":%s:%s:%d:" format, __FILE__, __func__, __LINE__, ##__VA_ARGS__); \
} while (0)

#else /* SCRIBE_LOG_ENABLED */

#define scribe_log_set_severity_level(severity_level) do {} while(0)
#define scribe_log_get_severity_level() (-1)
#define scribe_log_get_severity_level_label(severity_level) SCRIBE_LOG_SEVERITY_LEVEL_UNKNOWN_LABEL
#define scribe_log(severity_level, format, ...) do {} while(0)

#define SCRIBE_LOG(severity_level, format, ...) do {} while (0)

#endif /* SCRIBE_LOG_ENABLED */

#define SCRIBE_LOG_EMERGENCY(format, ...) \
SCRIBE_LOG(SCRIBE_LOG_SEVERITY_LEVEL_EMERGENCY, format, ##__VA_ARGS__)
#define SCRIBE_LOG_EMERG(format, ...)  SCRIBE_LOG_EMERGENCY(format, ##__VA_ARGS__)

#define SCRIBE_LOG_ALERT(format, ...) \
SCRIBE_LOG(SCRIBE_LOG_SEVERITY_LEVEL_ALERT, format, ##__VA_ARGS__)

#define SCRIBE_LOG_CRITICAL(format, ...) \
SCRIBE_LOG(SCRIBE_LOG_SEVERITY_LEVEL_CRITICAL, format, ##__VA_ARGS__)
#define SCRIBE_LOG_CRIT(format, ...)   SCRIBE_LOG_CRITICAL(format, ##__VA_ARGS__)

#define SCRIBE_LOG_ERROR(format, ...) \
SCRIBE_LOG(SCRIBE_LOG_SEVERITY_LEVEL_ERROR, format, ##__VA_ARGS__)
#define SCRIBE_LOG_ERR(format, ...)    SCRIBE_LOG_ERROR(format, ##__VA_ARGS__)

#define SCRIBE_LOG_WARNING(format, ...) \
SCRIBE_LOG(SCRIBE_LOG_SEVERITY_LEVEL_WARNING, format, ##__VA_ARGS__)
#define SCRIBE_LOG_WARN(format, ...)   SCRIBE_LOG_WARNING(format, ##__VA_ARGS__)

#define SCRIBE_LOG_NOTICE(format, ...) \
SCRIBE_LOG(SCRIBE_LOG_SEVERITY_LEVEL_NOTICE, format, ##__VA_ARGS__)

#define SCRIBE_LOG_INFORMATION(format, ...) \
SCRIBE_LOG(SCRIBE_LOG_SEVERITY_LEVEL_INFORMATION, format, ##__VA_ARGS__)
#define SCRIBE_LOG_INFO(format, ...)   SCRIBE_LOG_INFORMATION(format, ##__VA_ARGS__)

#ifdef NDEBUG
#   define SCRIBE_LOG_DEBUG(format, ...) do {} while(0)
#else
#   define SCRIBE_LOG_DEBUG(format, ...) \
    SCRIBE_LOG(SCRIBE_LOG_SEVERITY_LEVEL_DEBUG, format, ##__VA_ARGS__)
#endif

#endif /* SCRIBE_LOG_H */
