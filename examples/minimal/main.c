#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "scribe.h"
#include "stdout_sink.h"
#ifdef SCRIBE_COAP_SINK_ENABLED
#include "coap_sink.h"
#endif

static scribe_stdout_sink_t stdout_sink = SCRIBE_STDOUT_SINK_INITIALIZER();
#define STDOUT_SINK_INDEX ((size_t)0)

#ifdef SCRIBE_COAP_SINK_ENABLED

static scribe_coap_sink_instance_members_t coap_sink_prepare_data =
    SCRIBE_COAP_SINK_INSTANCE_MEMBERS_DEFAULT_INITIALIZER();

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

#ifdef OLD
static int write_message(const char *message) {
    scribe_code_t code = scribe_start();
    if (code != SCRIBE_CODE_OK) {
        printf("Error: failed to start message '%s'\n"
               "  - %s ( code : %d)\n",
               message,
               scribe_get_code_label(code), code);
        return EXIT_FAILURE;
    }

    const size_t message_length = strlen(message);
    code = scribe_write(message, message_length);
    if (code != SCRIBE_CODE_OK) {
        printf("Error: failed to write message '%s'\n"
               "  - %s ( code : %d)\n",
               message,
               scribe_get_code_label(code), code);
        return EXIT_FAILURE;
    }

    code = scribe_end();
    if (code != SCRIBE_CODE_OK) {
        printf("Error: failed to write message '%s'\n"
               "  - %s ( code : %d)\n",
               message,
               scribe_get_code_label(code), code);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
#endif // #ifdef OLD

static int write_message(const char *message) {
    const size_t message_length = strlen(message);
    scribe_code_t code = scribe_write(message, message_length);
    if (code != SCRIBE_CODE_OK) {
        printf("Error: failed to write message '%s'\n"
               "  - %s ( code : %d)\n",
               message,
               scribe_get_code_label(code), code);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

static void usage(const char *exe_name) {
    const char *name = ((exe_name == NULL) || (exe_name[0] == '\0')) ?
                       "minimal" : exe_name;
    printf("Usage:\n"
           "  %s\n",
           name);
}

int main(int argc, const char *argv[]) {
    if (argc < 1) {
        usage(NULL);
        return EXIT_FAILURE;
    }

    if (argc > 1) {
        usage(argv[0]);
        return EXIT_FAILURE;
    }

    int           result = EXIT_FAILURE;
    scribe_code_t code   = scribe_initialize(sinks, SINKS_COUNT);
    if (code != SCRIBE_CODE_OK) {
        printf("Error: failed to initialize Scribe\n"
               "  - %s ( code : %d)\n",
               scribe_get_code_label(code), code);
        return result;
    }

#ifdef SCRIBE_COAP_SINK_ENABLED
    coap_sink_prepare_data.pdu = (coap_pkt_t *)0xCAFEBABE;
#endif

    void *sinks_prepare_data[SINKS_COUNT] = {
        [STDOUT_SINK_INDEX] = NULL,
#ifdef SCRIBE_COAP_SINK_ENABLED
        [  COAP_SINK_INDEX] = &coap_sink_prepare_data,
#endif
    };
    code = scribe_prepare(sinks_prepare_data);
    if (code != SCRIBE_CODE_OK) {
        printf("Error: failed to prepare Scribe contents\n"
               "  - %s ( code : %d)\n",
               scribe_get_code_label(code), code);
        goto end;
    }

    result = write_message("{temperature : 27, temperature_unit = C}\n");
    if (result != EXIT_SUCCESS) {
        goto commit;
    }
    result = write_message("{temperature : 33, temperature_unit = C}\n");

commit:
    code = scribe_commit();
    if (code != SCRIBE_CODE_OK) {
        printf("Error: failed to commit Scribe contents\n"
               "  - %s (code : %d)\n",
               scribe_get_code_label(code), code);
        if (result == EXIT_SUCCESS) {
            result = EXIT_FAILURE;
        }
    }

end :
#ifdef SCRIBE_COAP_SINK_ENABLED
    coap_sink_prepare_data.pdu = NULL;
#endif
    scribe_release();

    return EXIT_SUCCESS;
}
