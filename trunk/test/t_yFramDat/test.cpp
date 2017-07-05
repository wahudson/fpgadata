// 2017-06-25  William A. Hudson
//
// Testing:  yFramDat  Frame Data class.
//--------------------------------------------------------------------------

#include <iostream>	// std::cerr
#include <iomanip>
#include <stdexcept>	// std::stdexcept

#include "utLib1.h"	// unit test library

#include "yFramDat.h"

using namespace std;


int main()
{

  CASE( "10", "constructor" );
    try {
	yFramDat		fx  (10);
	CHECK( 0, fx.get_length() );
    }
    catch (...) {
	FAIL( "unexpected exception" );
    }

  CASE( "12", "push_dat" );
    try {
	yFramDat		fx  (10);
	fx.push_dat( 0x0000 );
	fx.push_dat( 0xffff );
	CHECK( 2, fx.get_length() );
    }
    catch (...) {
	FAIL( "unexpected exception" );
    }

//--------------------------------------

  CASE( "20", "save_hex() cannot write" );
    try {
	yFramDat		fx  (10);
	fx.save_hex( "/xyzzy.dat" );
	FAIL( "no throw" );
    }
    catch ( runtime_error& e ) {
	CHECK( "cannot write file:  /xyzzy.dat",
	    e.what()
	);
    }
    catch (...) {
	FAIL( "unexpected exception" );
    }

  CASE( "21", "save_hex()" );
    try {
	yFramDat		fx  (10);
	fx.push_dat( 0x0000 );
	fx.push_dat( 0xffff );
	fx.save_hex( "tmp/out.dat" );
	CHECK( 2, fx.get_length() );
    }
    catch (...) {
	FAIL( "unexpected exception" );
    }

//--------------------------------------

  CASE( "30", "load_hex() no file" );
    try {
	yFramDat		fx  (10);
	fx.load_hex( "ref/missing.dat" );
	FAIL( "no throw" );
    }
    catch ( runtime_error& e ) {
	CHECK( "cannot read file:  ref/missing.dat",
	    e.what()
	);
    }
    catch (...) {
	FAIL( "unexpected exception" );
    }

  CASE( "31", "load_hex() good" );
    try {
	yFramDat		fx  (10);
	fx.push_dat( 0xaaaa );
	fx.push_dat( 0xffff );
	CHECK( 2, fx.get_length() );
	fx.load_hex( "ref/in.dat" ); CHECK( 16, fx.get_length() );
    }
    catch (...) {
	FAIL( "unexpected exception" );
    }

  CASE( "99", "Done" );
}

