/*
 * adc.h
 *
 *  Created on: 2017-3-29
 *      Author: Administrator
 */

#ifndef ADC_H_
#define ADC_H_

#include "C5509.h"
//#include "peripherals.h"
//#include "func.h"
#include "ICETEK-VC5509-EDU.h"
//#include "scancode.h"

// AD  ----------------------------------------------------------

#define ADCCTL	 	(*ADCCTL1)
#define ADCDATA 	(*ADCDATA1)
#define ADCCLKDIV 	(*ADCCLKDIV1)
#define ADCCLKCTL 	(*ADCCLKCTL1)

void InitADC();
void waitadc( unsigned int cycles );
void EnableAPLL( );
unsigned int * AdcOnce(int);
extern unsigned int nADC0[256],nADC1[256];



#endif /* ADC_H_ */
