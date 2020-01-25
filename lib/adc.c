/**
 * Library to read ADC Value (only CH552g and above!)
 *
 * Andreas Butti, (c) 2020
 * License: MIT
 */

#include "adc.h"

/**
 * Initialize the ADC
 *
 * @param div ADC Clock
 *
 * @return Bytes read
 */
void adcInit(uint8_t clock) {
	ADC_CFG &= ~bADC_CLK | clock;

	// ADC Power enabled
	ADC_CFG |= bADC_EN;
}

/**
 * Select ADC Channel
 *
 * @param channel Channel, 0  .. 3
 *
 * @return Bytes read
 */
void adcChannelSelect(uint8_t channel) {
	switch (channel) {
	case 1: // AIN1
		ADC_CHAN1 = 0;
		ADC_CHAN0 = 1;
		P1_DIR_PU &= ~bAIN1;
		break;

	case 2: // AIN2
		ADC_CHAN1 = 1;
		ADC_CHAN0 = 0;
		P1_DIR_PU &= ~bAIN2;
		break;

	case 3: // AIN3
		ADC_CHAN1 = 1;
		ADC_CHAN0 = 1;
		P3_DIR_PU &= ~bAIN3;
		break;

	default: // AIN0
		ADC_CHAN1 = 0;
		ADC_CHAN0 = 0;
		P1_DIR_PU &= ~bAIN0;
		break;
	}
}
