#ifndef ICETEK_H
#define ICETEK_H

#include "scancode.h"
#include "aic23.h"
#include "i2c.h"



// emif  --------------------------------------------------------
/*
#define EMIF_GCTL       0x01800000
#define EMIF_CE1        0x01800004
#define EMIF_CE0        0x01800008
#define EMIF_CE2        0x01800010
#define EMIF_CE3        0x01800014
#define EMIF_SDRAMCTL   0x01800018
#define EMIF_SDRAMTIM   0x0180001C
#define EMIF_SDRAMEXT   0x01800020
#define EMIF_CCFG       0x01840000;
*/
// interrupt  --------------------------------------------------
/*
#define IMH (*(unsigned int *)0x19c0000)
#define IML (*(unsigned int *)0x19c0004)
*/
// timer  -------------------------------------------------------
/*
#define TIMER1CTL (*(unsigned int *)0x01980000)
#define TIMER1PRD (*(unsigned int *)0x01980004)
*/



// ICETEK-VC5509-A -----------------------------------------------
#define SPEED144MHz 0x2613
#define LBDS (*((unsigned int *)0x400001))
#define DIPS (*(unsigned int *)0x400002)



#endif

