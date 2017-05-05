/*
 * uart.c
 *
 *  Created on: 04-May-2017
 *      Author: djvishnu92
 */

//#include "macros.h"
//
//void ClockSetup(void)
//{
//	SysCtlClockSet(SYSCTL_SYSDIV_1 | SYSCTL_USE_OSC |   SYSCTL_OSC_MAIN | SYSCTL_XTAL_16MHZ);       // Clock Configuration
//}
//
//void UART0Setup(void)
//{
//	SysCtlPeripheralEnable( SYSCTL_PERIPH_UART0 );           // UART Configuration
//	SysCtlPeripheralEnable( SYSCTL_PERIPH_GPIOA );
//
//	GPIOPinConfigure( GPIO_PA0_U0RX );
//	GPIOPinConfigure( GPIO_PA1_U0TX );
//	GPIOPinTypeUART( GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1 );
//
//	UARTConfigSetExpClk( UART0_BASE, SysCtlClockGet(), 115200,(UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE | UART_CONFIG_PAR_NONE));
//
//	IntMasterEnable();                                      //enable processor interrupts
//	IntEnable( INT_UART0 );                                 //enable the UART interrupt
//	UARTIntEnable( UART0_BASE, UART_INT_RX | UART_INT_RT ); //only enable RX and TX interrupts
//
//}
//void SendStringUART(char str[])
//{
//	short i;
//	for(i=0;(str[i]!='\0');++i)
//	{
//		UARTCharPut(UART0_BASE,str[i]);
//	}
//
//}

//
//extern char im[1024];
//extern enum state CurrState;
//extern void changeState(void);
//
// int n=0;
// int command=0;
//void UARTIntHandler(void)
//{
//	static int n=0;
//	static int command=0;
//
//    uint32_t ui32Status;
//	char ch;
//    // Get the interrrupt status.
//    ui32Status = UARTIntStatus(UART0_BASE, true);
//    // Clear the asserted interrupts.
//    UARTIntClear(UART0_BASE, ui32Status);
//    // Loop while there are characters in the receive FIFO.
//    while(UARTCharsAvail(UART0_BASE))
//    {
//        // Read the next character from the UART
//	    ch = UARTCharGet(UART0_BASE);
//
//
//	    UARTCharPut(UART0_BASE,ch);
//	    UARTCharPut(UART0_BASE,'-');
//	    im[0] = ch;
//		if(im[0] == 'e')
//		{
//			SendStringUART("Image Recognized");
//			UART_NEWLINE;
//
//			im[1024]='A';
//		}
//		switch(command)
//		{
//			case 0: if(n==0)
//					{
//						if(ch=='s')
//						{
//							command=1;
//
//							UARTCharPut(UART0_BASE,'x');
//
//						}
//						else
//						{
//							command=0;
//						}
//					}
//					else
//					{
//						//neverhere
//					}
//					break;
//
//			case 1:	im[n++]=ch;
//					UARTCharPut(UART0_BASE,'y');
//					if(n==1025)
//					{
//						command=0;
//						n=0;
//						CurrState = Processing;
//
////						changeState();
//						UARTCharPut(UART0_BASE,'z');
////						RecogImage = 1;
//
//					}
//					break;
//
//			case 2:	//neverhere
//					break;
//		}
//    }
//}
//
