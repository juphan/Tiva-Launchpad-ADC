#ifndef __GLOBAL_VARS__
#define __GLOBAL_VARS__

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

uint32_t result[1] = {0};  // ADC readings 
unsigned int avgResults = 0;  // Average results
int counter = 0;  // Counter for oversampling
char buffer[40];  // String buffer sent to UART (e.g. "0,2000,4095\n")

#endif // GLOBAL_VARS
