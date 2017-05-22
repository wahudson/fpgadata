// 2017-05-20  William A. Hudson
//
// Testing:  yBuffStat  Buffer Statistics class.
//--------------------------------------------------------------------------

#include <iostream>	// std::cerr
#include <stdexcept>	// std::stdexcept

#include "utLib1.h"		// unit test library
#include "yBuffStat.h"

using namespace std;
 
//--------------------------------------------------------------------------
 
int main()
{

  CASE( "10", "constructor" );
    try {
	yBuffStat		bx;
	std::string		ss;
	ss = bx.text_debug();
	CHECK( 100, bx.get_sample_size() );
	CHECK( "SampleSize= 100  NumSets= 0  CntTrue= 0  CntCalls= 0\n"
	    "        MaxTrue= -1  MinTrue= 101",
	    ss.c_str()
	);
    }
    catch (...) {
	FAIL( "unexpected exception" );
    }

  CASE( "11", "constructor" );
    try {
	yBuffStat		bx  (21);
	CHECK( 21, bx.get_sample_size() );
	CHECK( "SampleSize= 21  NumSets= 0  CntTrue= 0  CntCalls= 0\n"
	    "        MaxTrue= -1  MinTrue= 22",
	    bx.text_debug().c_str()
	);
    }
    catch (...) {
	FAIL( "unexpected exception" );
    }

  CASE( "12", "basic" );
    try {
	yBuffStat		bx  ( 4 );
	bx.cnt_by_call( 1 );
	CHECK( 4, bx.get_sample_size() );
	CHECK(
	    "SampleSize= 4  NumSets= 0  CntTrue= 1  CntCalls= 1\n"
	    "        MaxTrue= -1  MinTrue= 5",
	    bx.text_debug().c_str()
	);
	bx.cnt_by_call( 0 );
	CHECK(
	    "SampleSize= 4  NumSets= 0  CntTrue= 1  CntCalls= 2\n"
	    "        MaxTrue= -1  MinTrue= 5",
	    bx.text_debug().c_str()
	);
	bx.cnt_by_call( 0 );
	bx.cnt_by_call( 1 );
	CHECK(
	    "SampleSize= 4  NumSets= 1  CntTrue= 0  CntCalls= 0\n"
	    "        MaxTrue= 2  MinTrue= 2",
	    bx.text_debug().c_str()
	);
    }
    catch (...) {
	FAIL( "unexpected exception" );
    }

  CASE( "13", "single set false" );
    try {
	yBuffStat		bx  ( 4 );
	bx.cnt_by_call( 0 );
	bx.cnt_by_call( 0 );
	bx.cnt_by_call( 0 );
	bx.cnt_by_call( 0 );
	CHECK(
	    "SampleSize= 4  NumSets= 1  CntTrue= 0  CntCalls= 0\n"
	    "        MaxTrue= 0  MinTrue= 0",
	    bx.text_debug().c_str()
	);
    }
    catch (...) {
	FAIL( "unexpected exception" );
    }

  CASE( "14", "single set true" );
    try {
	yBuffStat		bx  ( 4 );
	bx.cnt_by_call( 1 );
	bx.cnt_by_call( 1 );
	bx.cnt_by_call( 1 );
	bx.cnt_by_call( 1 );
	CHECK(
	    "SampleSize= 4  NumSets= 1  CntTrue= 0  CntCalls= 0\n"
	    "        MaxTrue= 4  MinTrue= 4",
	    bx.text_debug().c_str()
	);
    }
    catch (...) {
	FAIL( "unexpected exception" );
    }

  CASE( "15", "six sets" );
    try {
	yBuffStat		bx  ( 4 );
	for ( int ii=0;  ii<6;  ii++ )
	{
	    bx.cnt_by_call( 1 );
	    bx.cnt_by_call( 1 );
	    bx.cnt_by_call( 1 );
	    bx.cnt_by_call( 0 );
	}
	CHECK(
	    "SampleSize= 4  NumSets= 6  CntTrue= 0  CntCalls= 0\n"
	    "        MaxTrue= 3  MinTrue= 3",
	    bx.text_debug().c_str()
	);
    }
    catch (...) {
	FAIL( "unexpected exception" );
    }

  CASE( "16", "mixed" );
    try {
	yBuffStat		bx  ( 4 );

	bx.cnt_by_call( 1 );
	bx.cnt_by_call( 1 );
	bx.cnt_by_call( 1 );
	bx.cnt_by_call( 0 );

	bx.cnt_by_call( 0 );
	bx.cnt_by_call( 1 );
	bx.cnt_by_call( 1 );
	bx.cnt_by_call( 0 );

	bx.cnt_by_call( 0 );
	bx.cnt_by_call( 1 );
	bx.cnt_by_call( 0 );
	bx.cnt_by_call( 0 );

	CHECK(
	    "SampleSize= 4  NumSets= 3  CntTrue= 0  CntCalls= 0\n"
	    "        MaxTrue= 3  MinTrue= 1",
	    bx.text_debug().c_str()
	);
	CHECK(
	    "Stats by call:  SampleSize= 4  NumSets= 3\n"
	    "    MaxTrue=    3  75%\n"
	    "    MinTrue=    1  25%\n",
	    bx.text_stats_by_call().c_str()
	);

	bx.cnt_by_call( 0 );
	bx.cnt_by_call( 0 );
	bx.cnt_by_call( 0 );
	bx.cnt_by_call( 0 );
	bx.cnt_by_call( 0 );

	CHECK(
	    "SampleSize= 4  NumSets= 4  CntTrue= 0  CntCalls= 1\n"
	    "        MaxTrue= 3  MinTrue= 0",
	    bx.text_debug().c_str()
	);
    }
    catch (...) {
	FAIL( "unexpected exception" );
    }

  CASE( "17", "status on too small a sample" );
    try {
	yBuffStat		bx  (21);
	CHECK( 21, bx.get_sample_size() );
	CHECK( "SampleSize= 21  NumSets= 0  CntTrue= 0  CntCalls= 0\n"
	    "        MaxTrue= -1  MinTrue= 22",
	    bx.text_debug().c_str()
	);
	CHECK(
	    "Stats by call:  SampleSize= 21  NumSets= 0\n"
	    "    MaxTrue=   -1  -1%\n"
	    "    MinTrue=   -1  -1%\n",
	    bx.text_stats_by_call().c_str()
	);
    }
    catch (...) {
	FAIL( "unexpected exception" );
    }


  CASE( "99", "Done" );
}

