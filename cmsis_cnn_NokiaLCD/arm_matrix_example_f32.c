

#include "arm_math.h"
#include "math_helper.h"

#include "weights.h"
#include "macros.h"
#include "myNokiaLcd.h"

#define max2(n1,n2)	(n1>n2 ? n1 : n2)
#define max4(n1,n2,n3,n4) max2(max2(n1,n2),max2(n3,n4))

void dispOut(void);
void startCNN(void);
void conv2D(void);
void reluConv(void);
void maxPool(void);
void flatten(void);
void fullyConnectedNet(void);
void softMax(void);
void findMaxIndex(void);
void reshapeInpMatrix(void);


volatile char im[1024];

char image[32][32];
float32_t temparr[25];
char tempimg[25];


volatile enum state CurrState = DataGet;

arm_status status;

float32_t conv1[28][28];
float32_t conv2[28][28];
float32_t conv3[28][28];

float32_t pool1[14][14];
float32_t pool2[14][14];
float32_t pool3[14][14];

float32_t fcInp[588];
float32_t fcOut[20];
float32_t classOut[5];

float32_t tim;
char timstr[10];

uint32_t ui32Period=0;


short maxIndex;

//float32_t tempfcwts[588];

int main()
{

	ClockSetup();

	UART0Setup();

	IntMasterEnable();

	displaymasterinit();

	SendStringUART("Recognition using CNN and CMSIS");
	UART_NEWLINE;
	SendStringUART("-------------------------------");
	UART_NEWLINE;
	UART_NEWLINE;
	UART_NEWLINE;

	CurrState = DataGet;

	while(1)
	{
		if(CurrState == Processing)
		{
			UART_NEWLINE;
			SendStringUART("--------------------------------------");
			UART_NEWLINE;
			SendStringUART("Image Received");
			UART_NEWLINE;

			SysTickPeriodSet(0xFFFFFF);
			HWREG(NVIC_ST_CURRENT)=0;
			SysTickEnable();

			startCNN();

			ui32Period=0xFFFFFF-SysTickValueGet();
			HWREG(NVIC_ST_CURRENT)=0;


			dispOut();

			CurrState = DataGet;
		}
	}

}


char lcdimage[1024];
void dispOut(void)
{


		SendStringUART("Image Detected ---->");
		SendStringUART(classnames[maxIndex]);
		SendStringUART("<----");
		UART_NEWLINE;
		UART_NEWLINE;

		SendStringUART("Ticks elapsed   ---->");
		SendintUART(ui32Period);
		UART_NEWLINE;
		SendStringUART("Clock Frequency ---->");
		SendintUART(16000000);
		UART_NEWLINE;
		SendStringUART("--------------------------------------");
		UART_NEWLINE;


		int k=0;

		int inpi;
		int inpj;

		for(inpi=0;inpi<=31;++inpi)
		{
			for(inpj=0;inpj<=31;++inpj)
			{
				image[inpi][inpj]= sampleImg[maxIndex][k];

				++k;
			}
		}

		k=0;
		for(inpi=0; inpi<32; ++inpi)
		{
			for(inpj=0; inpj<32; ++inpj)
			{
				lcdimage[k]=image[inpj][inpi];
				++k;
			}
		}
		LCDWriteBmp3x(lcdimage,22,10);


}






void ClockSetup(void)
{
	SysCtlClockSet(SYSCTL_SYSDIV_1 | SYSCTL_USE_OSC |   SYSCTL_OSC_MAIN | SYSCTL_XTAL_16MHZ);       // Clock Configuration

}

void UART0Setup(void)
{
	SysCtlPeripheralEnable( SYSCTL_PERIPH_UART0 );           // UART Configuration
	SysCtlPeripheralEnable( SYSCTL_PERIPH_GPIOA );

	GPIOPinConfigure( GPIO_PA0_U0RX );
	GPIOPinConfigure( GPIO_PA1_U0TX );
	GPIOPinTypeUART( GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1 );

	UARTConfigSetExpClk( UART0_BASE, SysCtlClockGet(), 115200,(UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE | UART_CONFIG_PAR_NONE));

	IntMasterEnable();                                      //enable processor interrupts
	IntEnable( INT_UART0 );                                 //enable the UART interrupt
	UARTIntEnable( UART0_BASE, UART_INT_RX | UART_INT_RT ); //only enable RX and TX interrupts

}
void SendStringUART(char str[])
{
	short i;
	for(i=0;(str[i]!='\0');++i)
	{
		UARTCharPut(UART0_BASE,str[i]);
	}

}

void UARTIntHandler(void)
{
	static int n=0;
	static int command=0;

    uint32_t ui32Status;
	char ch;
    // Get the interrrupt status.
    ui32Status = UARTIntStatus(UART0_BASE, true);
    // Clear the asserted interrupts.
    UARTIntClear(UART0_BASE, ui32Status);
    // Loop while there are characters in the receive FIFO.
    while(UARTCharsAvail(UART0_BASE))
    {
        // Read the next character from the UART
	    ch = UARTCharGet(UART0_BASE);

		switch(command)
		{
			case 0: if(n==0)
					{
						if(ch=='s')
						{
							command=1;


						}
						else
						{
							command=0;
						}
					}
					else
					{
						//neverhere
					}
					break;

			case 1:	im[n++]=ch;

					if(n==1024)
					{
						command=0;
						n=0;
						CurrState = Processing;

					

					}
					break;

			case 2:	//neverhere
					break;
		}
    }
}

void startCNN(void)
{

	reshapeInpMatrix();

	conv2D();

	reluConv();

	maxPool();

	flatten();

	fullyConnectedNet();

	softMax();

	findMaxIndex();

}

void findMaxIndex(void)
{

	float32_t max=classOut[0];
	maxIndex = 0;

	int i;
	for(i=1; i<5; ++i)
	{
		if(max < classOut[i] )
		{
			max = classOut[i];
			maxIndex = i;
		}
	}

}
void fullyConnectedNet(void)
{

	status = cmsisMatMultiply(fc_wts,20,588,fcInp,588,1,fcOut);
	if( status != ARM_MATH_SUCCESS)
	{
		while(1);
	}

	int i=0;
	for(i=0; i<20; ++i)
	{
		fcOut[i] = fcOut[i] + fc_bias[i];

		if(fcOut[i] < 0)
			fcOut[i] = 0.0;
	}

}
void softMax(void)
{
	int i=0,j;
	float32_t tempsmwts[20];
	float32_t smsum;

	i=0;
	for(j=0; j<5; ++j)
	{
		for(i=0; i<20; ++i)
		{
			tempsmwts[i] = softmax_wts[i+j*20];
		}

		status = cmsisMatMultiply(fcOut,1,20,tempsmwts,20,1,&smsum);
		if( status != ARM_MATH_SUCCESS)
		{
			while(1);
		}

		classOut[j] = smsum + softmax_bias[j];

	}

//	for(i=0; i<5; ++i)
//	{
//		classOut[i] = classOut[i] + softmax_bias[i];
//	}

}
void flatten(void)
{
	int i, j;
	int k;

	k=0;
	for(i=0; i<14; ++i)
	{
		for(j=0; j<14; ++j)
		{
			fcInp[k] = pool1[i][j];
			++k;
		}
	}

	for(i=0; i<14; ++i)
	{
		for(j=0; j<14; ++j)
		{
			fcInp[k] = pool2[i][j];
			++k;
		}
	}

	for(i=0; i<14; ++i)
	{
		for(j=0; j<14; ++j)
		{
			fcInp[k] = pool3[i][j];
			++k;
		}
	}
}
void reluConv(void)
{
	int i, j;

	for(i=0; i<=27; ++i )
	{
		for(j=0; j<=27; ++j)
		{
			if(conv1[i][j]<0)
				conv1[i][j]=0.0;

			if(conv2[i][j]<0)
				conv2[i][j]=0.0;

			if(conv3[i][j]<0)
				conv3[i][j]=0.0;
		}
	}
}
void maxPool(void)
{
	int i, j;
	int pi, pj;

	pi=0;
	for(i=0; i<=27; i=i+2)
	{
		pj=0;
		for(j=0; j<=27; j=j+2)
		{
			pool1[pi][pj] = max4(conv1[i][j], conv1[i][j+1], conv1[i+1][j], conv1[i+1][j+1]);
			pool2[pi][pj] = max4(conv2[i][j], conv2[i][j+1], conv2[i+1][j], conv2[i+1][j+1]);
			pool3[pi][pj] = max4(conv3[i][j], conv3[i][j+1], conv3[i+1][j], conv3[i+1][j+1]);

			++pj;
		}
		++pi;
	}

}
void conv2D(void)
{
	int imi, imj;
	int i,j;
	int k;
	float32_t convSum = 0.0;

	for(imi=2; imi<=29; ++imi)
	{
		for(imj=2; imj<=29; ++imj)
		{
			k=0;
			for(i=-2; i<=2; ++i)
			{
				for(j=-2; j<=2; ++j)
				{
					temparr[k] = (float32_t)(image[imi+i][imj+j]) / 255;
					++k;
				}
			}

			convSum = 0.0;
			status = cmsisMatMultiply(wt1,1,25,temparr,25,1,&convSum);
			if( status != ARM_MATH_SUCCESS)
			{
				while(1);
			}

			conv1[imi-2][imj-2]=convSum + b1;

			convSum = 0.0;
			status = cmsisMatMultiply(wt2,1,25,temparr,25,1,&convSum);
			if( status != ARM_MATH_SUCCESS)
			{
				while(1);
			}

			conv2[imi-2][imj-2]=convSum + b2;

			convSum = 0.0;
			status = cmsisMatMultiply(wt3,1,25,temparr,25,1,&convSum);
			if( status != ARM_MATH_SUCCESS)
			{
				while(1);
			}

			conv3[imi-2][imj-2]=convSum + b3;
		}
	}

}


void reshapeInpMatrix(void)
{
	int k=0;
	int inpi;
	int inpj;

	for(inpi=0;inpi<=31;++inpi)
	{
		for(inpj=0;inpj<=31;++inpj)
		{
			image[inpi][inpj]= im[k];
			++k;
		}
	}

}




arm_status cmsisMatMultiply(float32_t * AT_f32, uint32_t rowsAT, uint32_t columnsAT, float32_t * A_f32, uint32_t rowsA, uint32_t columnsA,float32_t * ATMA_f32)
{

  arm_matrix_instance_f32 A;      /* Matrix A Instance */
  arm_matrix_instance_f32 AT;     /* Matrix AT(A transpose) instance */
  arm_matrix_instance_f32 ATMA;   /* Matrix ATMA( AT multiply with A) instance */

//  uint32_t srcRows, srcColumns;  /* Temporary variables */
  arm_status status;

  /* Initialise A Matrix Instance with numRows, numCols and data array(A_f32) */

  arm_mat_init_f32(&A, rowsA, columnsA, (float32_t *)A_f32);


  /* Initialise Matrix Instance AT with numRows, numCols and data array(AT_f32) */

  arm_mat_init_f32(&AT, rowsAT, columnsAT, AT_f32);



  /* Initialise ATMA Matrix Instance with numRows, numCols and data array(ATMA_f32) */

  arm_mat_init_f32(&ATMA, rowsAT, columnsA, ATMA_f32);

  /* calculation of AT Multiply with A */
  status = arm_mat_mult_f32(&AT, &A, &ATMA);

  return status;

//  if( status != ARM_MATH_SUCCESS)
//  {
//    while(1);
//  }
//
//  while(1);                             /* main function does not return */
}

 /** \endlink */


void SendintUART(uint32_t num)
{
	char str[10],temp;
	int i=0,j;
	if(num == 0)
	{
		UARTCharPut(UART0_BASE,'0');
		return;
	}
	else
	{

		while(num>0)
		{
			str[i]=num%10 + 48;
			++i;
			num = num/10;
		}

		str[i]='\0';
		--i;
		j = i;
		i=0;
		while(i<j)
		{
			temp = str[i];
			str[i] = str[j];
			str[j] = temp;
			i++;
			j--;

		}
		SendStringUART(str);
	}

}
void FloatToString(float num,int dec, char str[])
{


	int len=0;
	int rem;
	char temp;
	int i_num,i=0,j;
	while(i<dec)
	{
		num =num* 10;
		++i;
	}
	i_num = (int)num;

	while(i_num>0)
	{
			rem = i_num%10;
			str[len] = rem + 48;
			++len;
			if(len==dec)
			{
					str[len]='.';
					++len;
			}
			i_num=i_num/10;
	}
	--len;
	j = len;
	i=0;
	while(i<j)
	{
		temp = str[i];
		str[i] = str[j];
		str[j] = temp;
		i++;
		j--;

	}
}
