/*
 * macros.h
 *
 *  Created on: 19-Feb-2017
 *      Author: djvishnu92
 */

#ifndef MACROS_H_
#define MACROS_H_
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdarg.h>



#include "inc/hw_ints.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "inc/hw_nvic.h"



#include "driverlib/gpio.h"
#include "driverlib/interrupt.h"
#include "driverlib/pin_map.h"
#include "driverlib/sysctl.h"
#include "driverlib/timer.h"
#include "driverlib/systick.h"
#include "driverlib/uart.h"
#include "driverlib/adc.h"


enum state { DataGet , Processing };


#define SIZE_UART_STRING 75
#define UART_NEWLINE UARTCharPut(UART0_BASE,10);UARTCharPut(UART0_BASE,13)
#define UART_HTAB UARTCharPut(UART0_BASE, 9)

#define DEBUG 1

#define SUCCESS '1'
#define FAIL '0'

void ClockSetup(void);
void UART0Setup(void);

void SendStringUART(char str[]);
void SendintUART(uint32_t num);
void FloatToString(float num,int dec, char str[]);
void UARTIntHandler(void);
#endif /* MACROS_H_ */
