/*
 * mcbsp.h
 *
 *  Created on: 2017-4-20
 *      Author: Administrator
 */

#ifndef MCBSP_H_
#define MCBSP_H_

// McBSP1  ------------------------------------------------------
extern ioport unsigned int *SPCR21;
extern ioport unsigned int *PCR_1;

#define SPCR2_1 (*SPCR21)
#define PCR1 (*PCR_1)

#endif /* MCBSP_H_ */
