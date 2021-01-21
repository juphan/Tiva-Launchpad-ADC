#ifndef __INTERRUPT_HANDLERS__
#define __INTERRUPT_HANDLERS__

#include "driverlib/adc.h"
#include "helper_functions.h"

const unsigned int OVERSAMPLE = 200; // Oversampling rate

// ADC Interrupt Handler (Read from ADC and send to UART)
void ADC1_Handler(void){
	// Read EMG values from Myoware sensor (PE1)
	ADCIntClear(ADC1_BASE, 2);                // Clear interrupt flag
	ADCSequenceDataGet(ADC1_BASE, 2, result); // Store ADC reading from PE3
	
	// Average readings
	avgResults += result[0]; // Sum of 200 readings
	counter++;               
	
	// Send string to UART
	if(counter == OVERSAMPLE){ // Average last 200 readings for 1 ADC output
		sprintf(buffer, "%d\n", round_Ints(avgResults, OVERSAMPLE)); // Round int division
		UART_OutString(buffer); // Sampling frequency = 1000Hz
		avgResults = 0;
		counter = 0;
	}
	
}

#endif // INTERRUPT_HANDLERS
