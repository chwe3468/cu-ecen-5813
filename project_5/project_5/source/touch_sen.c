/*
 * touch_sen.c
 *
 *  Created on: Feb 11, 2020
 *  	Author: Ben Roloff
 *  	link: https://www.digikey.com/eewiki/display/microcontroller/Using+the+Capacitive+Touch+Sensor+on+the+FRDM-KL46Z
 *      Editor: chutao
 */

#include "MKL25Z4.h"
#include "touch_sen.h"
#include "fsl_debug_console.h"
#include "logger.h"


//#define INCLUDE_LOG_DEBUG 1


tsi_position_t position;
#ifdef L_M_R_POSITION_MODE
const char * position_string[3] ={"left","middle","right"};
#endif

#ifdef L_R_POSITION_MODE
const char * position_string[3] ={"left","right"};
#endif

// TSI initialization function
void Touch_Init()
{
	// Enable clock for TSI PortB 16 and 17
	SIM->SCGC5 |= SIM_SCGC5_TSI_MASK;


	TSI0->GENCS = TSI_GENCS_OUTRGF_MASK |  // Out of range flag, set to 1 to clear
								//TSI_GENCS_ESOR_MASK |  // This is disabled to give an interrupt when out of range.  Enable to give an interrupt when end of scan
								TSI_GENCS_MODE(0u) |  // Set at 0 for capacitive sensing.  Other settings are 4 and 8 for threshold detection, and 12 for noise detection
								TSI_GENCS_REFCHRG(0u) | // 0-7 for Reference charge
								TSI_GENCS_DVOLT(0u) | // 0-3 sets the Voltage range
								TSI_GENCS_EXTCHRG(0u) | //0-7 for External charge
								TSI_GENCS_PS(0u) | // 0-7 for electrode prescaler
								TSI_GENCS_NSCN(31u) | // 0-31 + 1 for number of scans per electrode
								TSI_GENCS_TSIEN_MASK | // TSI enable bit
								//TSI_GENCS_TSIIEN_MASK | //TSI interrupt is disables
								TSI_GENCS_STPE_MASK | // Enables TSI in low power mode
								//TSI_GENCS_STM_MASK | // 0 for software trigger, 1 for hardware trigger
								//TSI_GENCS_SCNIP_MASK | // scan in progress flag
								TSI_GENCS_EOSF_MASK ; // End of scan flag, set to 1 to clear
								//TSI_GENCS_CURSW_MASK; // Do not swap current sources
}

// Function to read touch sensor from low to high capacitance for left to right
int Touch_Scan_LH(void)
{
	int scan;
	TSI0->DATA =  TSI_DATA_TSICH(10u); // Using channel 10 of The TSI
	TSI0->DATA |= TSI_DATA_SWTS_MASK; // Software trigger for scan
	scan = SCAN_DATA;
	TSI0->GENCS |= TSI_GENCS_EOSF_MASK ; // Reset end of scan flag

	return scan - SCAN_OFFSET;
}

// Function to read touch sensor from high to low capacitance for left to right
int Touch_Scan_HL(void)
{
	int scan;
	TSI0->DATA = 	TSI_DATA_TSICH(9u); // Using channel 9 of the TSI
	TSI0->DATA |=	TSI_DATA_SWTS_MASK; // Software trigger for scan
	scan = SCAN_DATA;
	TSI0->GENCS |=	TSI_GENCS_EOSF_MASK ; // Reset end of scan flag

	return scan - SCAN_OFFSET;
}

// Function to scan the position of slider
tsi_position_t Touch_Scan_Position(void)
{
	LOG_DEBUG("Scan Capacitance:");
	// read capacitance value
	int LH_value = Touch_Scan_LH();
	int HL_value = Touch_Scan_HL();

	LOG_DEBUG("LH_value: %d, HL_value: %d", LH_value, HL_value);

#ifdef L_M_R_POSITION_MODE
	// Check the capacitance, and decide the position
	if ((LH_value>50) && (LH_value<350) && (HL_value>50) && (HL_value<350))
	{
		position = left;
	}
	else if ((LH_value>450) && (LH_value<750) && (HL_value>450) && (HL_value<750))
	{
		position = middle;
	}
	else if ((LH_value>800) && (LH_value<1200) && (HL_value>800) && (HL_value<1200))
	{
		position = right;
	}
	LOG_DEBUG("Slider Position is  %s", position_string[position]);
#endif


#ifdef L_R_POSITION_MODE
	// Check the capacitance, and decide the position
	if ((LH_value>50) && (LH_value<1000) && (HL_value>50) && (HL_value<1000))
	{
		position = left;
	}
	else if ((LH_value>1100) && (LH_value<3000) && (HL_value>1100) && (HL_value<3000))
	{
		position = right;
	}
	else
	{
		position = unknown;
		LOG_DEBUG("Slider Position is a little off, calibration needed, default to left");
	}
	LOG_DEBUG("Slider Position is  %s", position_string[position]);
#endif

	return (position);

}

