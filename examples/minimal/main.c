#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "log.h"
#include "scribe.h"
#include "stdout_sink.h"
#ifdef SCRIBE_COAP_SINK_ENABLED
#include "coap_sink.h"
#endif

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

static scribe_stdout_sink_t stdout_sink = SCRIBE_STDOUT_SINK_INITIALIZER();
#define STDOUT_SINK_INDEX ((size_t)0)

#ifdef SCRIBE_COAP_SINK_ENABLED

static scribe_coap_sink_t coap_sink = SCRIBE_COAP_SINK_DEFAULT_INITIALIZER();
#define COAP_SINK_INDEX ((size_t)1)

#define SINKS_COUNT ((size_t)2)

#else /* SCRIBE_COAP_SINK_ENABLED */

#define SINKS_COUNT  ((size_t)1)

#endif /* SCRIBE_COAP_SINK_ENABLED */

static scribe_sink_t *sinks[SINKS_COUNT] = {
    [STDOUT_SINK_INDEX] = (scribe_sink_t *)&stdout_sink,
#ifdef SCRIBE_COAP_SINK_ENABLED
    [  COAP_SINK_INDEX] = (scribe_sink_t *)&coap_sink,
#endif
};

static int write_message(const char *message) {
    APP_LOG_DEBUG("(message=%p)\n", message);

    const size_t message_length = strlen(message);
    scribe_code_t code = scribe_write(message, message_length);
    if (code != SCRIBE_CODE_OK) {
        APP_LOG_ERROR("failed to write message '%s'\n"
                      "  - %s ( code : %d)\n",
                      message,
                      scribe_code_get_label(code), code);
        return EXIT_FAILURE;
    }

    APP_LOG_DEBUG("(message=%p):written bytes count:%zu\n", message, message_length);
    return EXIT_SUCCESS;
}

static void usage(const char *exe_name) {
    APP_LOG_DEBUG("(exe_name=%p)\n", exe_name);
    const char *name = ((exe_name == NULL) || (exe_name[0] == '\0')) ?
                       "minimal" : exe_name;
    printf("Usage:\n"
           "  %s\n",
           name);
}

int main(int argc, const char *argv[]) {
    APP_LOG_DEBUG("(argc=%d, argv=%p)\n", argc, argv);

    if (argc < 1) {
        APP_LOG_ERROR("Invalid arguments count : %d\n", argc);

        usage(NULL);
        return EXIT_FAILURE;
    }

    if (argc > 1) {
        APP_LOG_ERROR("Invalid arguments count : %d\n", argc);

        usage(argv[0]);
        return EXIT_FAILURE;
    }

    int           result = EXIT_FAILURE;
    scribe_code_t code   = scribe_initialize(sinks, SINKS_COUNT);
    if (code != SCRIBE_CODE_OK) {
        APP_LOG_ERROR("Error: failed to initialize Scribe\n"
                      "  - %s ( code : %d)\n",
                      scribe_code_get_label(code), code);
        return result;
    }

#ifdef SCRIBE_COAP_SINK_ENABLED
    scribe_coap_sink_prepare_data_t coap_sink_prepare_data = {
        .pdu        = (coap_pkt_t *)0xCAFEBABE,
        .buffer     = (uint8_t *)0xC0CAC01A,
        .bytesize   = 42
    };
#endif

    void *sinks_prepare_data[SINKS_COUNT] = {
        [STDOUT_SINK_INDEX] = NULL,
#ifdef SCRIBE_COAP_SINK_ENABLED
        [  COAP_SINK_INDEX] = &coap_sink_prepare_data,
#endif
    };
    code = scribe_prepare(sinks_prepare_data);
    if (code != SCRIBE_CODE_OK) {
        APP_LOG_ERROR("Error: failed to prepare Scribe contents\n"
                      "  - %s ( code : %d)\n",
                      scribe_code_get_label(code), code);
        goto end;
    }

    result = write_message("{temperature : 27, temperature_unit = C}\n");
    if (result != EXIT_SUCCESS) {
        goto commit;
    }
    result = write_message("{temperature : 33, temperature_unit = C}\n");

commit:
    size_t written_bytes_count = 0;
    code = scribe_commit(&written_bytes_count);
    if (code != SCRIBE_CODE_OK) {
        APP_LOG_ERROR("Error: failed to commit Scribe contents\n"
                      "  - %s (code : %d)\n",
                      scribe_code_get_label(code), code);
        if (result == EXIT_SUCCESS) {
            result = EXIT_FAILURE;
        }
    }

    APP_LOG_INFO("scribe has written %zu bytes to sinks\n", written_bytes_count);

end :
    scribe_release();

    return EXIT_SUCCESS;
}
