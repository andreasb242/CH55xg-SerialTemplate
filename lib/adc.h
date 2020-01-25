/**
 * Library to read ADC Value (only CH552g and above!)
 *
 * Andreas Butti, (c) 2020
 * License: MIT
 */

#pragma once

#include "inc.h"

/**
 * Initialize the ADC
 *
 * @param div ADC Clock
 *
 * @return Bytes read
 */
void adcInit(uint8_t clock);

/**
 * Select ADC Channel
 *
 * @param channel Channel, 0  .. 3
 *
 * @return Bytes read
 */
void adcChannelSelect(uint8_t channel);
