#ifndef SCRIBE_COAP_FAKE_NANOCOAP_H
#define SCRIBE_COAP_FAKE_NANOCOAP_H

#ifdef SCRIBE_COAP_SINK_ENABLED
#include <sys/types.h>
#include <stdint.h>
#include <stdbool.h>

typedef void coap_pkt_t;
typedef uint32_t coap_block_slicer_t;

extern void coap_block2_init(coap_pkt_t *pkt, coap_block_slicer_t *slicer);
extern int gcoap_resp_init(coap_pkt_t *pdu, uint8_t *buf, size_t len, unsigned code);
extern ssize_t coap_opt_add_format(coap_pkt_t *pkt, uint16_t format);
extern ssize_t coap_opt_add_block2(coap_pkt_t *pkt, coap_block_slicer_t *slicer, bool more);
extern ssize_t coap_opt_finish(coap_pkt_t *pkt, uint16_t flags);
extern int coap_blockwise_put_bytes_pkt(coap_pkt_t *pdu, coap_block_slicer_t *slicer,
                                        const void *c, size_t len);
extern bool coap_block2_finish(coap_block_slicer_t *slicer);

#endif /* SCRIBE_COAP_SINK_ENABLED */
#endif /* SCRIBE_COAP_FAKE_NANOCOAP_H */
