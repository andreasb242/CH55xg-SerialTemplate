/**
 * Hardware initialisation
 *
 * Andreas Butti, (c) 2020
 * License: MIT
 */

#include "inc.h"

// USB BUFFER -----------------------------------------------------------------

// Endpoint 0 OUT & IN buffer, must be an even address
__xdata __at (0x0000) uint8_t  Ep0Buffer[DEFAULT_ENDP0_SIZE];

// Endpoint 1 upload buffer
__xdata __at (0x0040) uint8_t  Ep1Buffer[DEFAULT_ENDP1_SIZE];

// Endpoint 2 IN & OUT buffer, must be an even address
__xdata __at (0x0080) uint8_t  Ep2Buffer[2 * MAX_PACKET_SIZE];

// ----------------------------------------------------------------------------


/**
 * Configure System Clock, system clock is set in the Makefile
 */
void ConfigureSystemClock() {
	SAFE_MOD = 0x55;
	SAFE_MOD = 0xAA;

#if FREQ_SYS == 32000000
	CLOCK_CFG = (CLOCK_CFG & ~ MASK_SYS_CK_SEL) | 0x07;  // 32MHz
#elif FREQ_SYS == 24000000
	CLOCK_CFG = (CLOCK_CFG & ~ MASK_SYS_CK_SEL) | 0x06;  // 24MHz
#elif FREQ_SYS == 16000000
	CLOCK_CFG = (CLOCK_CFG & ~ MASK_SYS_CK_SEL) | 0x05;  // 16MHz
#elif FREQ_SYS == 12000000
	CLOCK_CFG = (CLOCK_CFG & ~ MASK_SYS_CK_SEL) | 0x04;  // 12MHz
#elif FREQ_SYS == 6000000
	CLOCK_CFG = (CLOCK_CFG & ~ MASK_SYS_CK_SEL) | 0x03;  // 6MHz
#elif FREQ_SYS == 3000000
	CLOCK_CFG = (CLOCK_CFG & ~ MASK_SYS_CK_SEL) | 0x02;  // 3MHz
#elif FREQ_SYS == 750000
	CLOCK_CFG = (CLOCK_CFG & ~ MASK_SYS_CK_SEL) | 0x01;  // 750KHz
#elif FREQ_SYS == 187500
	CLOCK_CFG = (CLOCK_CFG & ~ MASK_SYS_CK_SEL) | 0x00;  // 187.5MHz
#else
#error FREQ_SYS invalid or not set
#endif

	SAFE_MOD = 0x00;
}

/**
 * Delay Microseconds
 *
 * @param n Microseconds
 */
void delay_us(uint16_t n) {
#ifdef	FREQ_SYS
#if		FREQ_SYS <= 6000000
	n >>= 2;
#endif
#if		FREQ_SYS <= 3000000
	n >>= 2;
#endif
#if		FREQ_SYS <= 750000
	n >>= 4;
#endif
#endif
	while (n) {  // total = 12~13 Fsys cycles, 1uS @Fsys=12MHz
		++SAFE_MOD;  // 2 Fsys cycles, for higher Fsys, add operation here
#ifdef	FREQ_SYS
#if		FREQ_SYS >= 14000000
		++SAFE_MOD;
#endif
#if		FREQ_SYS >= 16000000
		++SAFE_MOD;
#endif
#if		FREQ_SYS >= 18000000
		++ SAFE_MOD;
#endif
#if		FREQ_SYS >= 20000000
		++ SAFE_MOD;
#endif
#if		FREQ_SYS >= 22000000
		++ SAFE_MOD;
#endif
#if		FREQ_SYS >= 24000000
		++ SAFE_MOD;
#endif
#if		FREQ_SYS >= 26000000
		++ SAFE_MOD;
#endif
#if		FREQ_SYS >= 28000000
		++ SAFE_MOD;
#endif
#if		FREQ_SYS >= 30000000
		++ SAFE_MOD;
#endif
#if		FREQ_SYS >= 32000000
		++ SAFE_MOD;
#endif
#endif
		--n;
	}
}

/**
 * Delay Milliseconds
 *
 * @param n Milliseconds
 */
void delay_ms(uint16_t n) {
	while (n) {
		delay_us(1000);
		--n;
	}
}

/**
 * USB device mode configuration
 */
void USBDeviceCfg() {
	// Clear USB control register
	//USB_CTRL = 0x00;
	// This bit is the device selection mode
	//USB_CTRL &= ~bUC_HOST_MODE;
	// USB device and internal pull-up enable, automatically return to NAK before interrupt flag is cleared during interrupt
	// USB_CTRL |= bUC_DEV_PU_EN | bUC_INT_BUSY | bUC_DMA_EN;

	// Set the register by one command to save a few bytes
	USB_CTRL = bUC_DEV_PU_EN | bUC_INT_BUSY | bUC_DMA_EN;

	// Device address initialization
	USB_DEV_AD = 0x00;

	// Select full speed 12M mode, default mode
	// USB_CTRL &= ~bUC_LOW_SPEED; (already reseted by USB_CTRL = ...)
	//UDEV_CTRL &= ~bUD_LOW_SPEED; (overwritten by the line below)

	// Disable DP/DM pull-down resistor
	UDEV_CTRL = bUD_PD_DIS;

	// Enable physical port
	UDEV_CTRL |= bUD_PORT_EN;
}

/**
 * Enable USB Endpoint
 */
void USBDeviceEndPointCfg() {
	// Endpoint 1 sends the data transfer address
	UEP1_DMA = (uint16_t) Ep1Buffer;

	// Endpoint 2 IN data transfer address
	UEP2_DMA = (uint16_t) Ep2Buffer;

	// Endpoint 2/3 Single Buffer Transceiver Enable
	UEP2_3_MOD = 0xCC;

	// Endpoint 2 automatically flips the sync flag, IN transaction returns NAK, OUT returns ACK
	UEP2_CTRL = bUEP_AUTO_TOG | UEP_T_RES_NAK | UEP_R_RES_ACK;

	// Endpoint 1 automatically flips the sync flag, and IN transaction returns NAK
	UEP1_CTRL = bUEP_AUTO_TOG | UEP_T_RES_NAK;

	// Endpoint 0 data transfer address
	UEP0_DMA = (uint16_t) Ep0Buffer;

	// Endpoint 1 upload buffer; endpoint 0 single 64 byte send and receive buffer
	UEP4_1_MOD = 0X40;

	// Manual flip, OUT transaction returns ACK, IN transaction returns NAK
	UEP0_CTRL = UEP_R_RES_ACK | UEP_T_RES_NAK;
}

/**
 * USB device mode interrupt initialization
 */
void USBDeviceIntCfg() {
	//	// Enable device hang interrupt
	//	USB_INT_EN |= bUIE_SUSPEND;
	//
	//	// Enable USB transfer completion interrupt
	//	USB_INT_EN |= bUIE_TRANSFER;
	//
	//	// Enable device mode USB bus reset interrupt
	//	USB_INT_EN |= bUIE_BUS_RST;

	// Do it all together, to save a few bytes
	USB_INT_EN |= bUIE_SUSPEND | bUIE_TRANSFER | bUIE_BUS_RST;

	// Clear interrupt flag
	USB_INT_FG |= 0x1F;

	// Enable USB interrupt
	IE_USB = 1;

	// Enable global interrupts
	EA = 1;
}

#define BOOT_ADDR  0x3800

/**
 * This function provided a way to access the internal bootloader
 */
void jumpToBootloader() {
	USB_INT_EN = 0;
	USB_CTRL = 0x06;

	delay_ms(100);

	// Disable all interrupts
	EA = 0;

	// Ignore in IDE, non standard C Syntax
#ifndef IDE_ENVIRONMENT

	__asm
		LJMP BOOT_ADDR /* Jump to bootloader */
	__endasm;
#endif
	while(1);
}


