/**
 * Main Project Logic
 *
 * Andreas Butti, (c) 2020
 * License: MIT
 */

#include "logic.h"
#include "lib/usb-cdc.h"

/**
 * Bytes to send for speedtest
 */
uint32_t g_sendBytes = 0;

/**
 * Called from the main loop
 */
void logicLoop() {
	if (g_sendBytes) {
		// Wait for send buffer empty
		UsbCdc_puts("ABCDEFGHIJKLMNOPQRSTUVWXY");
		g_sendBytes -= 25;

		if (g_sendBytes == 0) {
			// To detect end by test script
			UsbCdc_putc('\n');
		}
	} else {
		P3_2 = 1;
	}
}

/**
 * Called for each received char
 */
void logicCharReceived(char c) {
	if (c == 's') {
		// 1 MByte
		g_sendBytes = 10 * 1000;
		P3_2 = 0;
	}
}

/**
 * Called before device gets powered down by USB
 */
void logicPowerDown() {
}



