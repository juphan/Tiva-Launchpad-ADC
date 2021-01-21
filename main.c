#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_ints.h"
#include "inc/hw_memmap.h"
#include "driverlib/adc.h"
#include "driverlib/interrupt.h"
#include "driverlib/uart.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"
#include "driverlib/timer.h"
#include "driverlib/sysctl.h"

#include "globalVARS.h"
#include "helper_functions.h"
#include "initialize.h"
#include "interruptHandlers.h"

//*****************************************************************************
// Instructions
/* 1) Tiva Launchpad has a 12-bit ADC with Vref from 0-3.3V
			- Resolution = (Vref+ - Vref-)/(2^12) = 0.8mV
			- Vmeasured should be within the range of 0-3V for accuracy
			- Vmeasured (0-3V) is converted to Vmapped (0-4095)
			- Conversion is done using this formula:
				(Vmapped/4095) = Vmeasured/(Vref+ - Vref-)

   2) Tiva Launchpad can be powered using 3.3V or 5V
      - Ensure the sensor and the Tiva Launchpad have a common GND
       
   3) Connect the sensor
			- Pin PE3 can sample voltage
			- ADC samples at a rate of 200kSPS
			- Oversampling rate of x200 (200 samples will be averaged for a more accurate reading)
			- Values will be sent to a connected PC through UART at a rate of 1000 samples/sec
	 
	 4) Start up the Data Logger program to log data in a CSV file 
	    - Max baud rate is 115200 bits/s
			- Max output through UART is around 1000 samples/sec
*/
//*****************************************************************************

// Main
int main(void){
	// Set 80Mhz clock
	SysCtlClockSet(SYSCTL_SYSDIV_2_5|SYSCTL_USE_PLL|SYSCTL_OSC_MAIN|SYSCTL_XTAL_16MHZ);
	
	// Initialize
	Init_LEDs();
	Init_UART();
	Init_ADC();
	IntMasterEnable();             
	
	// Forever while loop
  while(1){
  }
}
