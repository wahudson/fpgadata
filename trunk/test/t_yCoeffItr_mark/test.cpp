// 2020-07-02  William A. Hudson
//
// Testing:  yCoeffItr  Coefficient Data Iterator - scan marks
//     Verify ability to capture single-nibble scan mark pulses.
//     Versions prior to 2020-07-02 fail this test.
//     10-19  Constructor
//     20-29  Sample data - ref/nibble_mark.dat - 1 marks in a sea of 0.
//     30-39  Generate single-nibble 0 scan marks in a sea of 1.
//     40-49  Generate scan marks toggle on each nibble
//--------------------------------------------------------------------------

#include <iostream>	// std::cerr
#include <sstream>	// std::ostringstream
#include <iomanip>
#include <stdexcept>	// std::stdexcept

using namespace std;

#include "utLib1.h"		// unit test library

#include "Error.h"
#include "yFramDat.h"
#include "yCoeffItr.h"

//--------------------------------------------------------------------------

int main()
{
    // Capture error messages.
    //     Note if Serr is not checked and cleared on each case, then an
    //     unexpected error message may get attributed to the next case.
    //     Possibly make it part of each CASE().
    ostringstream	Serr;
    Error::Init_ostream( &Serr );

    yFramDat		Fx  (10);
    yCoeffItr		Cx  ( &Fx );


  CASE( "11", "empty object" );
    try {
	CHECK( 0, Fx.get_length() );
	CHECK( -1, Cx.PixNum );
	CHECK(  0, Cx.PixErr );
	CHECK(  0, Cx.PixMarkX );
	CHECK(  0, Cx.PixMarkY );
    }
    catch (...) {
	FAIL( "unexpected exception" );
    }

  CASE( "12", "next_pixel() on empty object" );
    try {
	int		*rv = Cx.next_pixel();
	CHECK( 1, (rv == NULL) );
	CHECK(    0, Cx.has_error() );
	CHECK(   -1, Cx.PixNum );		// count from 0
	CHECK(    0, Cx.PixErr );
	CHECK(    0, Cx.PixCoef[0] );
	CHECK(    0, Cx.PixCoef[15] );
	CHECK(    0, Cx.PixMarkX );
	CHECK(    0, Cx.PixMarkY );
    }
    catch (...) {
	FAIL( "unexpected exception" );
    }


//--------------------------------------------------------------------------
//## Sample data - ref/nibble_mark.dat - 1 marks in a sea of 0.
//--------------------------------------------------------------------------
// Single-nibble scan marks are 1 in a sea of 0.

  CASE( "20", "Fx.load_hex() nibble_mark.dat" );
    try {
	Fx.load_hex( "ref/nibble_mark.dat" );
	CHECK( 128, Fx.get_length() );
//	Fx.print_flag_hex();
    }
    catch (...) {
	FAIL( "unexpected exception" );
    }

  CASE( "21", "next_pixel()" );
    try {
	int		*rv = Cx.next_pixel();
	CHECK( 0, (rv == NULL) );
	CHECK(    0, Cx.has_error() );
	CHECK(    0, Cx.PixNum );		// count from 0
	CHECK(   15, Cx.PixCoef[0] );
	CHECK( 4096, Cx.PixCoef[15] );
	CHECK(    0, Cx.PixMarkX );
	CHECK(    1, Cx.PixMarkY );
	CHECK(   15, rv[0] );
	CHECK( 4096, rv[15] );
	CHECK( "", Serr.str().c_str() );
    }
    catch (...) {
	FAIL( "unexpected exception" );
    }

  CASE( "22", "next_pixel()" );
    try {
	int		*rv = Cx.next_pixel();
	CHECK( 0, (rv == NULL) );
	CHECK(    0, Cx.has_error() );
	CHECK(    1, Cx.PixNum );
	CHECK(   10, Cx.PixCoef[0] );
	CHECK( -257, Cx.PixCoef[15] );
	CHECK(    1, Cx.PixMarkX );
	CHECK(    0, Cx.PixMarkY );
	CHECK( "", Serr.str().c_str() );
    }
    catch (...) {
	FAIL( "unexpected exception" );
    }

  CASE( "23", "next_pixel() at end of data" );
    try {
	int		*rv = Cx.next_pixel();
	CHECK( 1, (rv == NULL) );
	CHECK(    0, Cx.has_error() );
	CHECK(    1, Cx.PixNum );		// not increment
	CHECK(   10, Cx.PixCoef[0] );
	CHECK( -257, Cx.PixCoef[15] );
	CHECK(    1, Cx.PixMarkX );		// keeps last mark value
	CHECK(    0, Cx.PixMarkY );
	CHECK( "", Serr.str().c_str() );
    }
    catch (...) {
	FAIL( "unexpected exception" );
    }

  CASE( "29", "show data" );
    try {
	ostringstream		ss;
	yCoeffItr		cx  ( &Fx );
	cx.print_coeff_csv( ss );		// walks the whole Fx
	CHECK( 128, Fx.get_length() );
	CHECK(
"index,Ym,Xm,c0,c1,c2,c3,c4,c5,c6,c7,c8,c9,c10,c11,c12,c13,c14,c15\n"
"0,1,0,15,-32768,4096,-1,33,291,291,291,291,291,291,291,291,291,291,4096\n"
"1,0,1,10,-32768,4096,-1,33,291,291,291,291,291,291,291,291,291,291,-257\n",
	    ss.str().c_str()
	);
	CHECK( "", Serr.str().c_str() );
    }
    catch (...) {
	FAIL( "unexpected exception" );
    }

//--------------------------------------------------------------------------
//## Generate single-nibble 0 scan marks in a sea of 1.
//--------------------------------------------------------------------------

  CASE( "30", "generate data, all scan marks 11" );
    try {
	uint32_t		cof;
	Fx.clear();
	for ( int ii = 0;  ii <= 2;  ii++ ) {		// pixel
	    for ( int jj = 0;  jj <= 15;  jj++ ) {	// coeff number
		cof = jj << 4;
		Fx.push_dat( cof | 0x300 );
		Fx.push_dat( cof | 0x300 );
		Fx.push_dat( cof | 0x301 );
		Fx.push_dat( cof | 0x300 | ii );
		//                 0x300   MarkY=1, MarkX=1
	    }
	}
//	Fx.print_flag_hex();
	CHECK( 192, Fx.get_length() );
    }
    catch (...) {
	FAIL( "unexpected exception" );
    }

  CASE( "30b", "set single scan marks 0" );
    try {
	uint16_t		*dp;
	dp = Fx.data_pointer_begin();
	dp += 64 + (4 * 3);
	*dp &= 0xfdff;		// set MarkY=0
	dp += 64;
	*dp &= 0xfeff;		// set MarkX=0
//	Fx.print_flag_hex();
	CHECK( 192, Fx.get_length() );
    }
    catch (...) {
	FAIL( "unexpected exception" );
    }

  CASE( "31", "show data with 0 marks" );
    try {
	ostringstream		ss;
	yCoeffItr		cx  ( &Fx );
	cx.print_coeff_csv( ss );		// walks the whole Fx
	CHECK( 192, Fx.get_length() );
	CHECK(
	"index,Ym,Xm,c0,c1,c2,c3,c4,c5,c6,c7,c8,c9,c10,c11,c12,c13,c14,c15\n"
	"0,1,1,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16\n"
	"1,0,1,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17\n"
	"2,1,0,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18\n",
	// ^ ^ see 0 scan marks on pixel
	    ss.str().c_str()
	);
	CHECK( "", Serr.str().c_str() );
    }
    catch (...) {
	FAIL( "unexpected exception" );
    }

//--------------------------------------------------------------------------
//## Generate scan marks toggle on each nibble
//--------------------------------------------------------------------------
// If scan marks change multiple times in each pixel, then the output
// scan marks will toggle on each pixel.

  CASE( "40", "generate data, scan marks toggle on each nibble" );
    try {
	uint32_t		cof;
	Fx.clear();
	for ( int ii = 0;  ii <= 7;  ii++ ) {		// pixel
	    for ( int jj = 0;  jj <= 15;  jj++ ) {	// coeff number
		cof = jj << 4;
		Fx.push_dat( cof | 0x100 );
		Fx.push_dat( cof | 0x200 );
		Fx.push_dat( cof | 0x101 );
		Fx.push_dat( cof | 0x200 | ii );
		//                 0x300   MarkY=1, MarkX=1
	    }
	}
//	Fx.print_flag_hex();
	CHECK( 512, Fx.get_length() );
    }
    catch (...) {
	FAIL( "unexpected exception" );
    }

  CASE( "41", "show scan marks toggle on each pixel" );
    try {
	ostringstream		ss;
	yCoeffItr		cx  ( &Fx );
	cx.print_coeff_csv( ss );		// walks the whole Fx
	CHECK( 512, Fx.get_length() );
	CHECK(
	"index,Ym,Xm,c0,c1,c2,c3,c4,c5,c6,c7,c8,c9,c10,c11,c12,c13,c14,c15\n"
	"0,1,1,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16\n"
	"1,0,0,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17\n"
	"2,1,1,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18\n"
	"3,0,0,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19\n"
	"4,1,1,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20\n"
	"5,0,0,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21\n"
	"6,1,1,22,22,22,22,22,22,22,22,22,22,22,22,22,22,22,22\n"
	"7,0,0,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23\n",
	// ^ ^ see scan marks toggle
	    ss.str().c_str()
	);
	CHECK( "", Serr.str().c_str() );
    }
    catch (...) {
	FAIL( "unexpected exception" );
    }



  CASE( "99", "Done" );
    CHECK( "", Serr.str().c_str() );
    Serr.str( string () );
}

