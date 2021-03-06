/**
 * @file bcm2835_mailbox.c
 *
 */
/* Copyright (C) 2016 ,2017 by Arjan van Vught mailto:info@raspberrypi-dmx.nl
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:

 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.

 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#include <stdint.h>

#include "bcm2835.h"

#define BCM2835_MAILBOX_STATUS_WF	0x80000000	///< Write full
#define	BCM2835_MAILBOX_STATUS_RE	0x40000000	///< Read empty

/**
 * @ingroup Mailbox
 *
 */
void bcm2835_mailbox_flush(void) {
	while (!(BCM2835_MAILBOX->STATUS & BCM2835_MAILBOX_STATUS_RE)) {
		(void) BCM2835_MAILBOX->READ;
		udelay(20);
	}
}

/**
 * @ingroup Mailbox
 *
 * @param channel
 * @return
 */
uint32_t bcm2835_mailbox_read(const uint8_t channel) {
	uint32_t data;

	do {
		while (BCM2835_MAILBOX->STATUS & BCM2835_MAILBOX_STATUS_RE)
			; // do nothing

		data = BCM2835_MAILBOX->READ;

	} while ((uint8_t) (data & 0xf) != channel);

	return (data & ~0xf);
}

/**
 * @ingroup Mailbox
 *
 * @param channel
 * @param data
 */
void bcm2835_mailbox_write(const uint8_t channel, const uint32_t data) {
	while (BCM2835_MAILBOX->STATUS & BCM2835_MAILBOX_STATUS_WF)
		; // do nothing
	BCM2835_MAILBOX->WRITE = (data & ~0xf) | (uint32_t) (channel & 0xf);
}
