/**
 * @file hardware_board.c
 *
 */
/* Copyright (C) 2016 by Arjan van Vught mailto:info@raspberrypi-dmx.nl
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

#include <bcm2835_vc.h>

#define MAX_NAME_LENGTH 24		///< Length for model name

///< Reference http://www.raspberrypi-spy.co.uk/2012/09/checking-your-raspberry-pi-board-version/
///< Reference http://elinux.org/RPi_HardwareHistory
struct _hardware_revision_code {
	const uint32_t value;
	const char name[MAX_NAME_LENGTH + 1];	///< Including '\0' byte
} static const board_version[] __attribute__((aligned(4))) = {
		{ 0x000000, "Model Unknown" },
		{ 0x000002, "Pi 1 Model B R1 256MB" },
		{ 0x000003, "Pi 1 Model B R1 256MB" },
		{ 0x000004, "Pi 1 Model B R2 256MB" },
		{ 0x000005, "Pi 1 Model B R2 256MB" },
		{ 0x000006, "Pi 1 Model B R2 256MB" },
		{ 0x000007, "Pi 1 Model A R2 256MB" },
		{ 0x000008, "Pi 1 Model A R2 256MB" },
		{ 0x000009, "Pi 1 Model A R2 256MB" },
		{ 0x00000d, "Pi 1 Model B R2 512MB" },
		{ 0x00000e, "Pi 1 Model B R2 512MB" },
		{ 0x00000f, "Pi 1 Model B R2 512MB" },
		{ 0x000010, "Pi 1 Model B+ 512MB V1.0" },
		{ 0x000011, "Compute Module 512MB" },
		{ 0x000012, "Pi 1 Model A+ 256MB V1.1" },
		{ 0x000013, "Pi 1 Model B+ 512MB V1.2" },
		{ 0x000014, "Compute Module 512MB" },
		{ 0x000015, "Pi 1 Model A+ 256MB V1.1" },
		{ 0x900021, "Pi 1 Model A+ 512MB" },
		{ 0xa01040, "Pi 2 Model B 1GB V1.0" },
		{ 0xa01041, "Pi 2 Model B 1GB V1.1" },
		{ 0xa21041, "Pi 2 Model B 1GB V1.1" },
		{ 0xa22042, "Pi 2 Model B 1GB V1.2" },		///< 2 Model B (with BCM2837)
		{ 0x900092, "Pi Zero 512MB V1.2" },
		{ 0x900093, "Pi Zero 512MB V1.3" },
		{ 0x9000c1, "Pi Zero W 512MB" },
		{ 0xa02082, "Pi 3 Model B 1GB V1.2" },
		{ 0xa22082, "Pi 3 Model B 1GB V1.2" }
};

/**
 * @ingroup hal
 *
 * @return
 */
const int32_t hardware_board_get_model_id(void) {
	return bcm2835_vc_get_get_board_revision();
}

/**
 * @ingroup hal
 *
 * @return
 */
const char *hardware_board_get_model(void) {
	const uint8_t array_length = sizeof(board_version) / sizeof(board_version[0]);
	const int32_t revision_code = bcm2835_vc_get_get_board_revision();

	uint8_t i;

	if (revision_code <= 0) {
		return board_version[0].name;
	}

	for (i = 1; i < array_length; i++) {
		if ((uint32_t)revision_code == board_version[i].value) {
			return board_version[i].name;
		}
	}

	return board_version[0].name;
}

/**
 * @ingroup hal
 *
 * @return
 */
const uint8_t hardware_board_get_model_length(void) {
	return MAX_NAME_LENGTH;
}
