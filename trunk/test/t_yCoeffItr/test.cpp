// 2017-09-01  William A. Hudson
//
// Testing:  yCoeffItr  Coefficient Data Iterator
//--------------------------------------------------------------------------

#include <iostream>	// std::cerr
#include <iomanip>
#include <stdexcept>	// std::stdexcept

#include "utLib1.h"		// unit test library

#include "yFramDat.h"
#include "yCoeffItr.h"

using namespace std;
 
//--------------------------------------------------------------------------
 
int main()
{

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
	yCoeffItr		cx  ( &Fx );
	CHECK( 128, Fx.get_length() );
	cx.print_coeff_csv();		// walks the whole Fx
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
    }
    catch (...) {
	FAIL( "unexpected exception" );
    }

  CASE( "53", "print_coeff_csv()" );
    try {
	yCoeffItr		cx  ( &Fx );
	cx.print_coeff_csv();
	CHECK(    0, cx.has_error() );	// only error on single pixel
	CHECK(    0, cx.PixErr );
    }
    catch (...) {
	FAIL( "unexpected exception" );
    }

  CASE( "99", "Done" );
}

