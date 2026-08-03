#ifndef SCRIBE_H
#define SCRIBE_H

#include <stddef.h>

#include "code.h"
#include "sink.h"

extern scribe_code_t scribe_initialize(scribe_sink_t **sinks, size_t sinks_count);

extern scribe_code_t scribe_prepare(void **data);

extern scribe_code_t scribe_start(void);
extern scribe_code_t scribe_write(const void *data, size_t bytesize);
extern scribe_code_t scribe_end(void);

extern scribe_code_t scribe_commit(void);

extern void          scribe_release(void);

#endif /* SCRIBE_H */
