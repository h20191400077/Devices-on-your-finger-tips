
#include <LPC214X.H>
#include "adc.h"

unsigned int ADC0Value[8],ADC0IntDone = 0;

void adcInit(void)
{
  PINSEL1 = 0x15400000;
  AD0CR   = 0x00210000;    // Setup A/D: 10-bit AIN0 @ 3MHz  
	
	PINSEL0 = 0x00000000;																									//P0.0 to P0.15 will be made as GPIO
	IODIR0=0x4fffffff;																										//P0.0 to P0.15 will be made as Output
	
}						  

unsigned int captureADC(unsigned char chNo)
{
  unsigned int val;
    
  AD0CR  = 0x00210C00 | (0x01 << chNo);     // Setup A/D: 10-bit AIN0 @ 3MHz 
  AD0CR  |= 0x01000000;    // Start A/D Conversion
    
  do
  {
 
     val = AD0GDR ;				// Read A/D Data Register 
  }		 
  while ((val & 0x80000000) == 0);

  AD0CR &= 0x00FFFFFF; 

  val 		= 	((val >> 6) & 0x3FF);

  return val;
}

/*
void InitADCInt(unsigned isrPtr)
{
  AD0INTEN = 0x102;	
  VICVectCntl1 	= 0x00000032;  						//select a priority slot for a given interrupt  
  VICVectAddr1 	= (unsigned long)isrPtr;		//pass the address of the IRQ into the VIC slot 
  VICIntEnable 	|= 1<<18;						//enable interrupt2
}

void ADCHandler (void) __irq 
{
   unsigned long regVal;
   unsigned char *ptr;
  //  IENABLE;			// handles nested interrupt 

    regVal = AD0STAT;		// Read ADC will clear the interrupt 
    putStrS1("\n\rRegVal= ");
	putIntS1(regVal);
	
	 if (regVal & 0x0000FF00 )
    {
	regVal = (regVal & 0x0000FF00) >> 0x08;
//				/ if overrun, just read ADDR to clear /
//				/ regVal variable has been reused. /
	  
	switch ( regVal )
	{
	    case 0x01:
		regVal = AD0DR0;
		break;
	    case 0x02:
		regVal = AD0DR1;
		break;
	    case 0x04:
		regVal = AD0DR2;
		break;
	    case 0x08:
		regVal = AD0DR3;
		break;
	    case 0x10:
		regVal = AD0DR4;
		break;
	    case 0x20:
		regVal = AD0DR5;
		break;
	    case 0x40:
		regVal = AD0DR6;
		break;
	    case 0x80:
		regVal = AD0DR7;
		break;
	    default:
		break;
	}
	putStrS1("\n\rOVERRUN");
//	AD0CR &= 0xF8FFFFFF;	// stop ADC now 
	ADC0IntDone = 1;   
	return;	
    }
    
    if ( regVal & ADC_ADINT )
    {
	switch (regVal & 0xFF )	// check DONE bit 
	{
	    case 0x01:
		ADC0Value[0] = ( AD0DR0 >> 6 ) & 0x3FF;
		break;
	    case 0x02:
		ADC0Value[1] = ( AD0DR1 >> 6 ) & 0x3FF;
		break;
	    case 0x04:
		ADC0Value[2] = ( AD0DR2 >> 6 ) & 0x3FF;
		break;
	    case 0x08:
		ADC0Value[3] = ( AD0DR3 >> 6 ) & 0x3FF;
		break;
	    case 0x10:
		ADC0Value[4] = ( AD0DR4 >> 6 ) & 0x3FF;
		break;
	    case 0x20:
		ADC0Value[5] = ( AD0DR5 >> 6 ) & 0x3FF;
		break;
	    case 0x40:
		ADC0Value[6] = ( AD0DR6 >> 6 ) & 0x3FF;
		break;
	    case 0x80:
		ADC0Value[7] = ( AD0DR7 >> 6 ) & 0x3FF;
		break;		
	    default:
		break;
	}
	val=ADC0Value[1];
	ptr=hex2bcd(ADC0Value[1]);
    putStrS1("\n\rADCINT= ");
    putStrS1(ptr);
	//AD0CR &= 0xF8FFFFFF;	// stop ADC now  
//	ADC0IntDone = 1;
    }
  	 
  //  IDISABLE;
    VICVectAddr = 0;		// Acknowledge Interrupt 
	AD0CR  |= 0x01000000;    // Start A/D Conversion 
}
*/
