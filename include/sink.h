#ifndef SCRIBE_SINK_H
#define SCRIBE_SINK_H

#include <stddef.h>
#include <assert.h>
#include <stdint.h>

#include "code.h"

typedef struct scribe_sink_s scribe_sink_t;

typedef scribe_code_t (*scribe_sink_prepare_method_t)(scribe_sink_t *sink, void *data);
typedef scribe_code_t (*scribe_sink_write_method_t)(scribe_sink_t *sink,
                                                    const void *data, size_t bytesize);
typedef scribe_code_t (*scribe_sink_commit_method_t)(scribe_sink_t *sink);

typedef struct scribe_sink_class_s {
    scribe_sink_prepare_method_t prepare;
    scribe_sink_write_method_t   write;
    scribe_sink_commit_method_t  commit;
} scribe_sink_class_t;

#define SCRIBE_SINK_CLASS_INITIALIZER(prepare_method, write_method, commit_method) \
{                                                                                  \
    .prepare = prepare_method,                                                     \
    .write   = write_method,                                                       \
    .commit  = commit_method,                                                      \
}

/* Not relying on offsetof(scribe_sink_class_t, write) to automatically scale
 * when adding/removing methods */
static const size_t scribe_sink_class_last_method_offset =
    sizeof(scribe_sink_class_t) - sizeof(uintptr_t);

static inline scribe_code_t scribe_sink_class_check_base(const scribe_sink_class_t *sink_class,
                                                         size_t first_method_offset,
                                                         size_t last_method_offset) {
    if (sink_class == NULL) {
        return SCRIBE_CODE_NULL_SINK_CLASS;
    }

    assert(last_method_offset <= scribe_sink_class_last_method_offset);
    assert(first_method_offset <= last_method_offset);
    if ((last_method_offset > scribe_sink_class_last_method_offset) ||
        (first_method_offset > last_method_offset)) {
        return SCRIBE_CODE_INTERNAL_INVALID_METHODS_OFFSETS;
    }

    const uint8_t *class_start = (const uint8_t *)sink_class;
    for (size_t offset_it = first_method_offset; offset_it <= last_method_offset;
         offset_it+=sizeof(void *)) {
        const void **method = (const void **)&class_start[offset_it];
        if (*method == NULL) {
            return SCRIBE_CODE_NULL_SINK_CLASS_METHOD;
        }
    }

    return SCRIBE_CODE_OK;
}

static inline scribe_code_t scribe_sink_class_check(const scribe_sink_class_t *sink_class) {
    return scribe_sink_class_check_base(sink_class, 0, scribe_sink_class_last_method_offset);
}

static inline scribe_code_t scribe_sink_class_check_method(const scribe_sink_class_t *sink_class,
                                                           size_t method_offset) {
    return scribe_sink_class_check_base(sink_class, method_offset, method_offset);
}

struct scribe_sink_s {
    const scribe_sink_class_t *klass;
};

static inline scribe_code_t scribe_sink_check(const scribe_sink_t *sink) {
    if (sink == NULL) {
        return SCRIBE_CODE_NULL_SINK;
    }
    return scribe_sink_class_check(sink->klass);
}

static inline scribe_code_t scribe_sink_check_method(const scribe_sink_t *sink,
                                                     size_t method_offset_in_class) {
    if (sink == NULL) {
        return SCRIBE_CODE_NULL_SINK;
    }
    return scribe_sink_class_check_method(sink->klass, method_offset_in_class);
}

#define SCRIBE_SINK_CHECK_METHOD(sink, method_name) \
scribe_sink_check_method(sink, offsetof(scribe_sink_class_t, method_name))

static inline scribe_code_t scribe_sink_prepare(scribe_sink_t *sink, void *data) {
    const scribe_code_t code = SCRIBE_SINK_CHECK_METHOD(sink, prepare);
    if (code != SCRIBE_CODE_OK) {
        return code;
    }
    return sink->klass->prepare(sink, data);
}

static inline scribe_code_t scribe_sink_write(scribe_sink_t *sink,
                                              const void *data, size_t bytesize) {
    const scribe_code_t code = SCRIBE_SINK_CHECK_METHOD(sink, write);
    if (code != SCRIBE_CODE_OK) {
        return code;
    }
    return sink->klass->write(sink, data, bytesize);
}

static inline scribe_code_t scribe_sink_commit(scribe_sink_t *sink) {
    const scribe_code_t code = SCRIBE_SINK_CHECK_METHOD(sink, commit);
    if (code != SCRIBE_CODE_OK) {
        return code;
    }
    return sink->klass->commit(sink);
}

#endif /* SCRIBE_SINK_H */
