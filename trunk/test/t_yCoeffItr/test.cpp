// 2017-09-01  William A. Hudson
//
// Testing:  yCoeffItr  Coefficient Data Iterator
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
    //     Possibly make it part of eash CASE().
    ostringstream	Serr;
    Error::Init_ostream( &Serr );

    yFramDat		Fx  (10);
    yCoeffItr		Cx  ( &Fx );


  CASE( "10", "constructor" );
    try {
	yFramDat		fx  (10);
	yCoeffItr		cx  ( &fx );
	CHECK( 0, fx.get_length() );
	CHECK( -1, cx.PixNum );
	CHECK(  0, cx.PixErr );
	CHECK(  0, cx.PixMarkX );
	CHECK(  0, cx.PixMarkY );
    }
    catch (...) {
	FAIL( "unexpected exception" );
    }

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

  CASE( "15", "print_coeff_csv_head()" );
    try {
	ostringstream		ss;
	Cx.print_coeff_csv_head( ss );
	CHECK(
	    "index,Ym,Xm,c0,c1,c2,c3,c4,c5,c6,c7,c8,c9,c10,c11,c12,c13,c14,c15\n",
	    ss.str().c_str()
	);
    }
    catch (...) {
	FAIL( "unexpected exception" );
    }

//----------------------------------------
// Sample data

  CASE( "20", "Fx.load_hex() sample data" );
    try {
	Fx.load_hex( "ref/good.dat" );
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
	CHECK(    0, Cx.PixMarkX );
	CHECK(    0, Cx.PixMarkY );
	CHECK( "", Serr.str().c_str() );
    }
    catch (...) {
	FAIL( "unexpected exception" );
    }


/*
  CASE( "28", "show data" );
    try {
	yCoeffItr		cx  ( &Fx );
	CHECK( 128, Fx.get_length() );
	cx.print_coeff_tab();		// walks the whole Fx
    }
    catch (...) {
	FAIL( "unexpected exception" );
    }
*/

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

//----------------------------------------
// restart()  PixNum continues incrementing.

  CASE( "30", "restart()" );
    try {
	Cx.restart();
	CHECK(    0, Fx.get_length() );		// reset to zero
	CHECK(    0, Cx.has_error() );
	CHECK(    1, Cx.PixNum );		// unchanged
	CHECK(   10, Cx.PixCoef[0] );		// unchanged
	CHECK( -257, Cx.PixCoef[15] );		// unchanged
	CHECK(    0, Cx.PixMarkX );		// unchanged
	CHECK(    0, Cx.PixMarkY );		// unchanged
    }
    catch (...) {
	FAIL( "unexpected exception" );
    }

  CASE( "31", "Fx.load_hex()" );
    try {
	Fx.load_hex( "ref/good.dat" );
	CHECK( 128, Fx.get_length() );
//	Fx.print_flag_hex();
    }
    catch (...) {
	FAIL( "unexpected exception" );
    }

  CASE( "32", "next_pixel()" );
    try {
	Cx.next_pixel();
	CHECK(    0, Cx.has_error() );
	CHECK(    2, Cx.PixNum );		// continue
	CHECK(   15, Cx.PixCoef[0] );
	CHECK( 4096, Cx.PixCoef[15] );
	CHECK(    0, Cx.PixMarkX );
	CHECK(    1, Cx.PixMarkY );
    }
    catch (...) {
	FAIL( "unexpected exception" );
    }

  CASE( "33", "next_pixel()" );
    try {
	Cx.next_pixel();
	CHECK(    0, Cx.has_error() );
	CHECK(    3, Cx.PixNum );
	CHECK(   10, Cx.PixCoef[0] );
	CHECK( -257, Cx.PixCoef[15] );
	CHECK(    1, Cx.PixMarkX );
	CHECK(    0, Cx.PixMarkY );
    }
    catch (...) {
	FAIL( "unexpected exception" );
    }

//----------------------------------------
// restart()  with bad coeff nibble.

  CASE( "40", "restart()" );
    try {
	Cx.restart();
	CHECK(    0, Fx.get_length() );		// reset to zero
	CHECK(    0, Cx.has_error() );
	CHECK(    3, Cx.PixNum );		// unchanged
	CHECK(   10, Cx.PixCoef[0] );		// unchanged
	CHECK( -257, Cx.PixCoef[15] );		// unchanged
	CHECK(    1, Cx.PixMarkX );		// unchanged
	CHECK(    0, Cx.PixMarkY );		// unchanged
    }
    catch (...) {
	FAIL( "unexpected exception" );
    }

  CASE( "41", "Fx.load_hex()" );
    try {
	Fx.load_hex( "ref/good.dat" );
	CHECK( 128, Fx.get_length() );
//	Cx.print_coeff_csv();
    }
    catch (...) {
	FAIL( "unexpected exception" );
    }

  CASE( "42", "Fx change data value" );
    try {
	uint16_t	*dp = Fx.data_pointer_begin();
	CHECK(  0x000f, dp[3] );
	dp[3] = 0x000e;

	CHECK(  0x0018, dp[68] );	// second pixel, coeff 1
	CHECK(  0x0010, dp[69] );
	CHECK(  0x0010, dp[70] );
	CHECK(  0x0010, dp[71] );
	dp[70] = 0x002f;
    }
    catch (...) {
	FAIL( "unexpected exception" );
    }


  CASE( "43", "next_pixel()" );
    try {
	Cx.next_pixel();
	CHECK(    0, Cx.has_error() );
	CHECK(    4, Cx.PixNum );		// continue
	CHECK(   14, Cx.PixCoef[0] );
	CHECK( 4096, Cx.PixCoef[15] );
	CHECK(    0, Cx.PixMarkX );
	CHECK(    1, Cx.PixMarkY );
	CHECK( "", Serr.str().c_str() );
    }
    catch (...) {
	FAIL( "unexpected exception" );
    }

  CASE( "44", "next_pixel()" );
    try {
	Cx.next_pixel();
	CHECK(     1, Cx.has_error() );
	CHECK(     5, Cx.PixNum );		// continue
	CHECK(    10, Cx.PixCoef[0] );
	CHECK(-99999, Cx.PixCoef[1] );		// error from dp[70]
	CHECK(  4096, Cx.PixCoef[2] );
	CHECK(  -257, Cx.PixCoef[15] );
	CHECK(     1, Cx.PixMarkX );
	CHECK(     0, Cx.PixMarkY );
	CHECK(
	    "Error:  misaligned coeff nibble at:\n"
	    "    index= 72\n",
	    Serr.str().c_str()
	);
	Serr.str( string () );
    }
    catch (...) {
	FAIL( "unexpected exception" );
    }

//----------------------------------------
// restart()  with missing coeff nibble.

  CASE( "50", "new object" );
    try {
	Cx = yCoeffItr  ( &Fx );		// new object
	Fx.load_hex( "ref/bad_coeff.dat" );
	CHECK(  131, Fx.get_length() );
	CHECK(    0, Cx.has_error() );
	CHECK(   -1, Cx.PixNum );		// unchanged
	CHECK(    0, Cx.PixCoef[0] );		// unchanged
	CHECK(    0, Cx.PixCoef[15] );		// unchanged
	CHECK(    0, Cx.PixMarkX );		// unchanged
	CHECK(    0, Cx.PixMarkY );		// unchanged
	CHECK( "", Serr.str().c_str() );
    }
    catch (...) {
	FAIL( "unexpected exception" );
    }

  CASE( "51", "next_pixel()" );
    try {
	Cx.next_pixel();
	CHECK(    1, Cx.has_error() );
	CHECK(    0, Cx.PixNum );
	CHECK(   15, Cx.PixCoef[0] );
	CHECK(-99999, Cx.PixCoef[15] );
	CHECK(    0, Cx.PixMarkX );
	CHECK(    1, Cx.PixMarkY );
	CHECK(
	    "Error:  misaligned coeff nibble at:\n"
	    "    index= 28\n",
	    Serr.str().c_str()
	);
	Serr.str( string () );
    }
    catch (...) {
	FAIL( "unexpected exception" );
    }

  CASE( "52", "next_pixel()" );
    try {
	Cx.next_pixel();
	CHECK(    1, Cx.has_error() );
	CHECK(    1, Cx.PixNum );
	CHECK(-99999, Cx.PixCoef[0] );
	CHECK(-99999, Cx.PixCoef[15] );
	CHECK(    0, Cx.PixMarkX );
	CHECK(    0, Cx.PixMarkY );
	CHECK(
	    "Error:  misaligned coeff nibble at:\n"
	    "    index= 68\n",
	    Serr.str().c_str()
	);
	Serr.str( string () );
    }
    catch (...) {
	FAIL( "unexpected exception" );
    }

  CASE( "53", "print_coeff_csv()" );
    try {
	ostringstream		ss;
	yCoeffItr		cx  ( &Fx );
	cx.print_coeff_csv( ss );
	CHECK(    0, cx.has_error() );	// only error on single pixel
	CHECK(    0, cx.PixErr );
	CHECK(
"index,Ym,Xm,c0,c1,c2,c3,c4,c5,c6,c7,c8,c9,c10,c11,c12,c13,c14,c15\n"
"0!,1,0,15,-32768,4096,-1,33,291,-99999,-99999,-99999,-99999,-99999,-99999,-99999,-99999,-99999,-99999\n"
"1!,0,0,-99999,-99999,-99999,-99999,-99999,-99999,-99999,-99999,-99999,-99999,-99999,-99999,-99999,-99999,-99999,-99999\n",
	    ss.str().c_str()
	);
	CHECK(
	    "Error:  misaligned coeff nibble at:\n"
	    "    index= 28\n"
	    "Error:  misaligned coeff nibble at:\n"
	    "    index= 68\n",
	    Serr.str().c_str()
	);
	Serr.str( string () );
    }
    catch (...) {
	FAIL( "unexpected exception" );
    }


  CASE( "99", "Done" );
    CHECK( "", Serr.str().c_str() );
    Serr.str( string () );
}

