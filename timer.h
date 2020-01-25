/**
 * Timer file controls Timer1
 *
 * Andreas Butti, (c) 2020
 * License: MIT
 */

#pragma once

#include "lib/inc.h"

/**
 * Internal timer
 */
extern volatile uint32_t g_Timer;

/**
 * Setup Timer
 */
void timerSetup();

/**
 * Called from timer interrupt
 */
inline void timer0clock();
