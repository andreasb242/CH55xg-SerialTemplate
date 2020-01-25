/**
 * Main USB Logic
 *
 * Andreas Butti, (c) 2020
 * License: MIT
 */

#pragma once

#include <stdint.h>
#include <string.h>

#include <ch554.h>
#include <ch554_usb.h>
#include <debug.h>

#include <8051.h>

#define bool uint8_t
#define true 1
#define false 0


// Ignore some defines for the IDE,
// make sure this is defined in your IDE,
// but not in the makefile, so this is
// ignored for the build
#ifdef IDE_ENVIRONMENT
#define __xdata
#define __at(x)
#define __code
#define __idata
#define __interrupt(x)
#define SBIT(a, b, c)

uint8_t P1_0 = 0;
uint8_t P1_1 = 0;
uint8_t P1_2 = 0;
uint8_t P1_3 = 0;
uint8_t P1_4 = 0;
uint8_t P1_5 = 0;
uint8_t P1_6 = 0;
uint8_t P1_7 = 0;

uint8_t P2_0 = 0;
uint8_t P2_1 = 0;
uint8_t P2_2 = 0;
uint8_t P2_3 = 0;
uint8_t P2_4 = 0;
uint8_t P2_5 = 0;
uint8_t P2_6 = 0;
uint8_t P2_7 = 0;

uint8_t P3_0 = 0;
uint8_t P3_1 = 0;
uint8_t P3_2 = 0;
uint8_t P3_3 = 0;
uint8_t P3_4 = 0;
uint8_t P3_5 = 0;
uint8_t P3_6 = 0;
uint8_t P3_7 = 0;

#endif

//#define PRINT_DBG(str) print(str "\r\n")
#define PRINT_DBG(str)

/**
 * USB device mode configuration
 */
void USBDeviceCfg();

/**
 * Enable USB Endpoint
 */
void USBDeviceEndPointCfg();

/**
 * Main Loop
 */
void mainLoop();

/**
 * USB device mode interrupt initialization
 */
void USBDeviceIntCfg();

