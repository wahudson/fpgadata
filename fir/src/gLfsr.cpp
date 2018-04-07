// 2018-03-24  William A. Hudson

// Galois LFSR (Linear Feedback Shift Register) class
//
// See:  https://en.wikipedia.org/wiki/Linear-feedback_shift_register
//
//--------------------------------------------------------------------------

#include <iostream>
#include <iomanip>
#include <sstream>	// std::ostringstream

#include "gLfsr.h"

using namespace std;


/*
* Constructor.
*/
gLfsr::gLfsr()
{
    TapPoly   = 0x00110000;	// 20-bit
    StartSeed = 0x00000001;
    LfsR      = StartSeed;
    ShiftCnt  = 0;
}


/*
* Constructor.
*/
gLfsr::gLfsr( uint32_t  tap_poly )
{
    TapPoly   = tap_poly;
    StartSeed = 0x00000001;
    LfsR      = StartSeed;
    ShiftCnt  = 0;
}


/*
* Reset LfsR
* call:
*    self.reset()
*/
void
gLfsr::reset()
{
    LfsR      = StartSeed;
}


/*
* Advance state one step.
* call:
*    self.next_state()
*/
uint32_t
gLfsr::next_state()
{
    uint32_t	lsb;

    lsb    = LfsR & 0x1;
    LfsR >>= 1;

    if ( lsb ) {
	LfsR ^= TapPoly;
    }

    return  LfsR;
}

