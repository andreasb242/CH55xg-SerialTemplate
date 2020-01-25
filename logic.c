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
	while (g_sendBytes) {
		//UsbCdc_puts("ABCDEFGHIJ");
		g_sendBytes -= 10;
	}
}

/**
 * Called for each received char
 */
void logicCharReceived(char c) {
	if (c == 's') {
		// 1 MByte
		g_sendBytes = 1000 * 1000;
	}
}

/**
 * Called before device gets powered down by USB
 */
void logicPowerDown() {
}



