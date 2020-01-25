/**
 * Main USB Logic
 *
 * Andreas Butti, (c) 2020
 * License: MIT
 */

#pragma once

#include <stdint.h>
#include <string.h>

#include "base/ch554.h"
#include "base/ch554_usb.h"

#include <8051.h>

#define bool uint8_t
#define true 1
#define false 0

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

