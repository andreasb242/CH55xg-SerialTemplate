/**
 * USB CDC Implementation
 * Based on the example from
 * https://github.com/Blinkinlabs/ch554_sdcc/tree/master/examples/usb_device_cdc_i2c
 *
 * Andreas Butti, (c) 2020
 * License: MIT
 */

#pragma once

#include "inc.h"

/**
 * USB-CDC Transmit Buffer Length
 */
#define USBCDC_TRANSMIT_BUFFER_LEN  64

/**
 * Current buffer remaining bytes to be sent over USB-CDC
 */
extern volatile __idata uint8_t g_UartTransmitByteCount;

/**
 * Send usb data from buffer
 */
void UsbCdc_processOutput();

/**
 * Receive data from USB and process it, process only one byte at once
 */
void UsbCdc_processInput();

/**
 * Send one byte over USB CDC Serial port
 *
 * @param c Char to send
 */
void UsbCdc_putc(uint8_t c);

/**
 * Send uint8_t over CDC Serial port
 */
void UsbCdc_puti(uint8_t value);

/**
 * Send 0 terminated string over USB CDC Serial port
 *
 * @param str String to send (0 Terminator will not be sent)
 */
void UsbCdc_puts(char* str);

/**
 * USB Interrupt Handler
 */
void usbInterrupt();
