#ifndef __FUNCTIONS__
#define __FUNCTIONS__

#include "inc/hw_memmap.h"
#include "driverlib/uart.h"

//------------UART_OutChar------------
// Output 8-bit to serial port
// Input: letter is an 8-bit ASCII character to be transferred
// Output: none
void UART_OutChar(unsigned char data){
  UARTCharPut(UART0_BASE, data);
}

//------------UART_OutString------------
// Output String (NULL termination)
// Input: pointer to a NULL-terminated string to be transferred
// Output: none
void UART_OutString(char *pt){
  while(*pt){
    UART_OutChar(*pt);
    pt++;
  }
}

////------------round_Ints------------
// Round the division of 2 unsigned ints
// Input: dividend(sum of last N ADC samples) and divisor(number of ADC samples)
// Output: unsigned int
unsigned int round_Ints(unsigned int dnd, unsigned int div){
	return (dnd + (div/2))/div;
}

#endif // HELPER FUNCTIONS
