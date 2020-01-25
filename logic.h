/**
 * Main Project Logic
 *
 * Andreas Butti, (c) 2020
 * License: MIT
 */

#pragma once

#include "lib/inc.h"

/**
 * Called from the main loop
 */
void logicLoop();

/**
 * Called for each received char
 */
void logicCharReceived(char c);

/**
 * Called before device gets powered down by USB
 */
void logicPowerDown();

