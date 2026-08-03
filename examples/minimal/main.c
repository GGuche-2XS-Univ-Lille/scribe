#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "stdout_sink.h"
#include "scribe.h"

static scribe_stdout_sink_t stdout_sink = SCRIBE_STDOUT_SINK_INITIALIZER();


#define SINKS_COUNT  ((size_t)1)

static scribe_sink_t *sinks[1] = {
    (scribe_sink_t *)&stdout_sink,
};

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

    void *sinks_prepare_data[SINKS_COUNT] = {
        NULL
    };
    code = scribe_prepare(sinks_prepare_data);
    if (code != SCRIBE_CODE_OK) {
        printf("Error: failed to prepare Scribe contents\n"
               "  - %s ( code : %d)\n",
               scribe_get_code_label(code), code);
        goto end;
    }

    result = write_message("{temperature : 27, temperature_unit = C}");
    if (result != EXIT_SUCCESS) {
        goto commit;
    }
    result = write_message("{temperature : 33, temperature_unit = C}");

commit:
    code = scribe_commit();
    if (code != SCRIBE_CODE_OK) {
        printf("Error: failed to commit Scribe contents\n"
               "  - %s ( code : %d)\n",
               scribe_get_code_label(code), code);
        if (result == EXIT_SUCCESS) {
            result = EXIT_FAILURE;
        }
    }

end :
    scribe_release();

    return EXIT_SUCCESS;
}
