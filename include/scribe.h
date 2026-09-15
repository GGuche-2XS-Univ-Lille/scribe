#ifndef SCRIBE_H
#define SCRIBE_H

#include <stddef.h>

#include "code.h"

#ifdef RIOT_VERSION
#   include "net/nanocoap.h"
#else
#   include "fake_nanocoap.h"
#endif

extern scribe_code_t scribe_initialize(coap_pkt_t *pdu, uint8_t *buffer, size_t buffer_bytesize);
extern scribe_code_t scribe_write(const void *data, size_t bytesize);
extern size_t        scribe_get_written_bytes_count(void);
extern void          scribe_release(void);

#endif /* SCRIBE_H */
