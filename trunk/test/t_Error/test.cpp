// 2017-12-01  William A. Hudson
//
// Testing:  Error class.
//--------------------------------------------------------------------------

#include <iostream>	// std::cerr
#include <sstream>	// std::ostringstream
#include <stdexcept>	// std::stdexcept

#include "utLib1.h"	// unit test library

#include "Error.h"

using namespace std;

ostringstream		xx;

int main()
{

  CASE( "10", "Error::has_err() no initial error" );
    try {
	CHECK( 0, Error::has_err() );
    }
    catch (...) {
	FAIL( "unexpected exception" );
    }

  CASE( "12", "Error::msg() message" );
    try {
	Error::msg() << "hello" <<endl;
	CHECK( 1, Error::has_err() );
    }
    catch (...) {
	FAIL( "unexpected exception" );
    }

//--------------------------------------
  CASE( "20", "Init_ostream()" );
    try {
	Error::Init_ostream( &xx );
	CHECK( 1, Error::has_err() );
    }
    catch (...) {
	FAIL( "unexpected exception" );
    }

  CASE( "21", "Error::msg() null message" );
    try {
	Error::msg();
	CHECK( 2, Error::has_err() );
	CHECK( "Error:  ", xx.str().c_str() );
	xx.str( string () );	// clear the ostringstream
    }
    catch (...) {
	FAIL( "unexpected exception" );
    }

  CASE( "22", "Error::msg() message" );
    try {
	Error::msg() << "good pi= " << 3.14 <<endl;
	CHECK( 3, Error::has_err() );
	CHECK( "Error:  good pi= 3.14\n", xx.str().c_str() );
	xx.str( string () );
    }
    catch (...) {
	FAIL( "unexpected exception" );
    }

  CASE( "23", "Error::msg() text argument" );
    try {
	Error::msg( "good pi= " ) << 3.14 <<endl;
	CHECK( 4, Error::has_err() );
	CHECK( "Error:  good pi= 3.14\n", xx.str().c_str() );
	xx.str( string () );
    }
    catch (...) {
	FAIL( "unexpected exception" );
    }


  CASE( "99", "Done" );
}

