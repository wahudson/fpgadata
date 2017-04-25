// Author:  William A. Hudson  2011-11-28
//
// Error class.
//--------------------------------------------------------------------------

#include <iostream>
#include "Error.h"

using namespace std;

// Init static Class Data:
int Error::Error_cnt = 0;

// call:
//    Error::err()		Get global error count.
//    Error::err( "text", .. )	Output error message, increpent error count.

// Class Methods:
int
Error::err()
{
    return Error_cnt;
}

void
Error::err( const char* m1 )
{
    Error_cnt++;
    cerr << "Error:  " << m1 << endl;
}

void
Error::err( const char* m1,  const char* m2 )
{
    Error_cnt++;
    cerr << "Error:  " << m1 << m2 << endl;
}

void
Error::err( const char* m1,  const char* m2,  const char* m3 )
{
    Error_cnt++;
    cerr << "Error:  " << m1 << m2 << m3 << endl;
}

void
Error::err( const char* m1,  const char* m2,  const char* m3,  const char* m4 )
{
    Error_cnt++;
    cerr << "Error:  " << m1 << m2 << m3 << m4 << endl;
}


// Instance Methods:
int
Error::msg( char* m1 )
{
    cerr << "Error msg:  " << m1 << endl;
    count = 1;
    return count;
}

