/**
 * Project main, setup everything
 *
 * Andreas Butti, (c) 2020
 * License: MIT
 */

#include "lib/inc.h"
#include "lib/hardware.h"
#include "logic.h"
#include "lib/usb-cdc.h"
#include "lib/timer.h"

/**
 * Interrupt needs to be here in the Main file
 * else it simple won't be called.
 */
void DeviceInterrupt(void) __interrupt(INT_NO_USB) {
	usbInterrupt();
}


/**
 * Timer 0 interrupt
 */
void timer0() __interrupt(INT_NO_TMR0) {
	timer0clock();
}


/**
 * Firmware main
 */
void main() {
	// CH55x clock selection configuration
	ConfigureSystemClock();

	// Modify the main frequency and wait for the internal crystal to stabilize.
	delay_ms(5);

	// Initialize timer
	timerSetup();

	// Initialize Hardware
	logicInit();

	// Enable USB Port
	USBDeviceCfg();

	// Endpoint configuration
	USBDeviceEndPointCfg();

	// Interrupt initialization
	USBDeviceIntCfg();

	// Pre-use send length must be cleared
	UEP0_T_LEN = 0;
	UEP1_T_LEN = 0;
	UEP2_T_LEN = 0;

	// Main Loop
	while(1) {
		UsbCdc_processInput();

		logicLoop();
	}
}
