#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "log.h"
#include "scribe.h"

#ifdef SCRIBE_LOG_ENABLED

#define APP_LOG_ERROR(format, ...) SCRIBE_LOG_ERROR(format, ##__VA_ARGS__)
#define APP_LOG_INFO(format, ...)  SCRIBE_LOG_INFO(format, ##__VA_ARGS__)
#define APP_LOG_DEBUG(format, ...) SCRIBE_LOG_DEBUG(format, ##__VA_ARGS__)

#else /* SCRIBE_LOG_ENABLED */

#define APP_LOG_ERROR(format, ...) printf(format, ##__VA_ARGS__)
#define APP_LOG_INFO(format, ...)  printf(format, ##__VA_ARGS__)

#ifdef NDEBUG
#   define APP_LOG_DEBUG(format, ...)  do {} while (0)
#else
#   define APP_LOG_DEBUG(format, ...) printf(format, ##__VA_ARGS__)
#endif

#endif /* SCRIBE_LOG_ENABLED */

static void usage(const char *exe_name) {
    APP_LOG_DEBUG("(exe_name=%p)\n", exe_name);
    const char *name = ((exe_name == NULL) || (exe_name[0] == '\0')) ?
    "minimal" : exe_name;
    printf("Usage:\n"
    "  %s\n",
    name);
}

static int write_message(const char *message) {
    APP_LOG_DEBUG("(message=%p)\n", message);

    const size_t        message_length  = strlen(message);
    const scribe_code_t code            = scribe_write(message, message_length);
    if (code != SCRIBE_CODE_OK) {
        APP_LOG_ERROR(": failed to write message '%s'\n"
                      "  - %s ( code : %d)\n",
                      message,
                      scribe_code_get_label(code), code);
        return EXIT_FAILURE;
    }

    APP_LOG_DEBUG("(message=%p):written bytes count:%zu\n", message, message_length);
    return EXIT_SUCCESS;
}

int main(int argc, const char *argv[]) {
    APP_LOG_DEBUG("(argc=%d, argv=%p)\n", argc, argv);

    if (argc < 1) {
        APP_LOG_ERROR(": Invalid arguments count : %d\n", argc);

        usage(NULL);
        return EXIT_FAILURE;
    }

    if (argc > 1) {
        APP_LOG_ERROR(": Invalid arguments count : %d\n", argc);

        usage(argv[0]);
        return EXIT_FAILURE;
    }

          uint8_t       buffer[128] = {0};
          int           result      = EXIT_FAILURE;
    const scribe_code_t code        =
        scribe_initialize((coap_pkt_t *)0xCAFEBABE, buffer, sizeof(buffer));
    switch (code) {
        case SCRIBE_CODE_OK:
            APP_LOG_DEBUG(": scribe has been initialized\n");
            break;
        case SCRIBE_CODE_FLUSH: {
            APP_LOG_INFO(": scribe has required to flush the current packet\n");
            goto end;
        }
        default: {
            APP_LOG_ERROR("Error: failed to initialize Scribe\n"
            "  - %s ( code : %d)\n",
                          scribe_code_get_label(code), code);
            return result;
        }
    }

    result = write_message("{temperature : 27, temperature_unit = C}\n");
    if (result != EXIT_SUCCESS) {
        goto end;
    }
    result = write_message("{temperature : 33, temperature_unit = C}\n");

end:
    const size_t written_bytes_count = scribe_get_written_bytes_count();
    APP_LOG_INFO("scribe has written %zu bytes\n", written_bytes_count);

    scribe_release();

    return EXIT_SUCCESS;
}
