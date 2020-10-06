


void adcInit(void);

unsigned int captureADC(unsigned char chNo);
void InitADCInt(unsigned isrPtr);
void ADCHandler (void) __irq ;
#define		CH0		0
#define		CH1		1
#define		CH2		2
#define		CH3		3


#define ADC_DONE	0x80000000
#define ADC_OVERRUN	0x40000000
#define ADC_ADINT	0x00010000

