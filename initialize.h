#ifndef __INITIALIZE__
#define __INITIALIZE__

#include "inc/hw_ints.h"
#include "inc/hw_memmap.h"
#include "driverlib/adc.h"
#include "driverlib/interrupt.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"
#include "driverlib/timer.h"
#include "driverlib/sysctl.h"

// Setup LEDs
void Init_LEDs(){
	// Enable Peripheral Clocks 
  SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
	
  // Enable pin PF1-PF3 for GPIOOutput (LED lights RBG)
  GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3);
	
	// Turn on red light
	GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1, 0x02);
}

// Setup UART settings
void Init_UART(void){
    // Enable Peripheral Clocks
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);

	  // Configure pins (PA0->U0Rx) and (PA1->U0Tx)
    GPIOPinConfigure(GPIO_PA0_U0RX);
    GPIOPinConfigure(GPIO_PA1_U0TX);
    GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);

    // Configure UART
    UARTConfigSetExpClk(UART0_BASE, SysCtlClockGet(), 115200, (UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE | UART_CONFIG_PAR_NONE)); // Max baud rate = 115200
}

// Setup ADC settings
void Init_ADC(void){
	// Enable Peripheral Clocks
	SysCtlPeripheralEnable(SYSCTL_PERIPH_ADC1);
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);
	
	// Set pins as ADC inputs
	GPIOPinTypeADC(GPIO_PORTE_BASE, GPIO_PIN_3); // AIN0 as ADC input (Channel 0)
	
	// Configure sequence
	ADCSequenceDisable(ADC1_BASE, 2); //Disable ADC1, SS2, before configuration
	ADCSequenceConfigure(ADC1_BASE, 2, ADC_TRIGGER_TIMER, 0); // ADC1, SS2, Sample-triggered by timer, Priority 0 with respect to other sample sequences
  
	// Configure step sequence
	// Completion will set RIS, Mark as last sample of sequence 
	ADCSequenceStepConfigure(ADC1_BASE, 2, 0, ADC_CTL_CH0 | ADC_CTL_IE | ADC_CTL_END); // Sample PE3
	
	// Set priority
	IntPrioritySet(INT_ADC1SS2, 0x00);       // Priority 0
	IntEnable(INT_ADC1SS2);                  // Enable interrupt for ADC1, SS2
	ADCIntEnableEx(ADC1_BASE, ADC_INT_SS2);  // Arm interrupt
	
	// Set Timer0A for ADC interrupt
	SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER0);    
	TimerConfigure(TIMER0_BASE, TIMER_CFG_PERIODIC); // Periodic
	TimerLoadSet(TIMER0_BASE, TIMER_A, 400);         // ADC Sampling Frequency = (80MHz)/(400 Clock Cycles) = 200kHz 
	TimerControlTrigger(TIMER0_BASE, TIMER_A, true); // Enable Timer0A for ADC timer-sampling
	TimerEnable(TIMER0_BASE, TIMER_A);               // Enable Timer0A
	
	// Enable ADC1
	ADCSequenceEnable(ADC1_BASE, 2); // Enable ADC1, Sequencer 2
  ADCIntClear(ADC1_BASE, 2);       // Clear interrupt status flag
}

#endif // INITIALIZE
