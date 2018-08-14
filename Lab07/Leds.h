/* 
 * File:   Leds.h
 * Author: Jose Luis Santiago jlsantia@ucsc.edu
 *
 * Created on August 1, 2018, 1:30 PM
 */

#ifndef LEDS_H
#define	LEDS_H

#include "BOARD.h"
#include <xc.h>

#define LEDS_INIT() {LATE = 0; TRISE = 0;}
    
#define LEDS_GET() LATE

#define LEDS_SET(x) LATE = x    


#endif	/* LEDS_H */

