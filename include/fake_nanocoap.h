/*
 * DISCLAIMER : functions prototypes and documentations come from RIOT nanocoap+gcoap.
 *
 * This layer has been implemented for development and demonstrations purposes
 */

#ifndef SCRIBE_COAP_FAKE_NANOCOAP_H
#define SCRIBE_COAP_FAKE_NANOCOAP_H

#if (defined(SCRIBE_COAP_SINK_ENABLED)) && (!defined(RIOT_VERSION))
#include <sys/types.h>
#include <stdint.h>
#include <stdbool.h>

#define COAP_CODE_CONTENT           ((2 << 5) | 5)   /**< Response Code: 2.05 Content */
#define COAP_FORMAT_TEXT            (0)
#define COAP_OPT_FINISH_PAYLOAD     (0x0001)

typedef void coap_pkt_t;
typedef uint32_t coap_block_slicer_t;

extern void coap_block2_init(coap_pkt_t *pkt, coap_block_slicer_t *slicer);

/**
 * @brief   Initializes a CoAP response packet on a buffer
 *
 * Initializes payload location within the buffer based on packet setup.
 *
 * @param[out] pdu      Response metadata
 * @param[in] buf       Buffer containing the PDU
 * @param[in] len       Length of the buffer
 * @param[in] code      Response code
 *
 * @return  0 on success
 * @return  < 0 on error
 */
extern int gcoap_resp_init(coap_pkt_t *pdu, uint8_t *buf, size_t len, unsigned code);

/**
 * @brief   Append a Content-Format option to the pkt buffer
 *
 * @post pkt.payload advanced to first byte after option
 * @post pkt.payload_len reduced by option length
 *
 * @param[in,out] pkt         pkt referencing target buffer
 * @param[in]     format      COAP_FORMAT_xxx to use
 *
 * @return        number of bytes written to buffer
 * @return        <0 on error
 * @return        -ENOSPC if no available options or insufficient buffer space
 */
extern ssize_t coap_opt_add_format(coap_pkt_t *pkt, uint16_t format);

/**
 * @brief   Add block2 option in descriptive use from a slicer object
 *
 * When calling this function to initialize a packet with a block option, the
 * more flag must be set to prevent the creation of an option with a length too
 * small to contain the size bit.
 *
 * @post pkt.payload advanced to first byte after option
 * @post pkt.payload_len reduced by option length
 *
 * @param[in,out] pkt         pkt referencing target buffer
 * @param[in]     slicer      coap blockwise slicer helper struct
 * @param[in]     more        more flag (1 or 0)
 *
 * @return        number of bytes written to buffer
 * @return        <0 on error
 * @return        -ENOSPC if no available options or insufficient buffer space
 */
extern ssize_t coap_opt_add_block2(coap_pkt_t *pkt, coap_block_slicer_t *slicer, bool more);

/**
 * @brief   Finalizes options as required and prepares for payload
 *
 * @post pkt.payload advanced to first available byte after options
 * @post pkt.payload_len is maximum bytes available for payload
 *
 * @param[in,out] pkt         pkt to update
 * @param[in]     flags       see COAP_OPT_FINISH... macros
 *
 * @return        total number of bytes written to buffer
 * @return        -ENOSPC if no buffer space for payload marker
 */
extern ssize_t coap_opt_finish(coap_pkt_t *pkt, uint16_t flags);

/**
 * @brief Add a byte array to a block2 reply when building the response using
 *        a coap_pkt_t structure to assemble the message,
 *
 * This function is used to add an array of bytes to a CoAP block2 reply. it
 * checks which parts of the string should be added to the reply and ignores
 * parts that are outside the current block2 request.
 *
 * @param[in,out]   pdu     pkt to assemble the message in
 * @param[in,out]   slicer  slicer to use
 * @param[in]       c       byte array to copy
 * @param[in]       len     length of the byte array
 *
 * @retval          0               Success
 * @retval          -EOVERFLOW      Not enough space in buffer
 * @retval          <0              Other error
 */
extern int coap_blockwise_put_bytes_pkt(coap_pkt_t *pdu, coap_block_slicer_t *slicer,
                                        const void *c, size_t len);

/**
 * @brief Finish a block2 response
 *
 * This function finalizes the block2 response header
 *
 * Checks whether the `more` bit should be set in the block2 option and
 * sets/clears it if required.  Doesn't return the number of bytes, as this
 * function overwrites bytes in the packet rather than adding new.
 *
 * @param[in,out]   slicer      Preallocated slicer struct to use
 *
 * @retval      true if the `more` bit is set in the block option
 * @retval      false if the `more` bit is not set the block option
 */
extern bool coap_block2_finish(coap_block_slicer_t *slicer);

#endif /* (defined(SCRIBE_COAP_SINK_ENABLED)) && (!defined(RIOT_VERSION)) */
#endif /* SCRIBE_COAP_FAKE_NANOCOAP_H */
