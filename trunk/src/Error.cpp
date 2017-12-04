// Author:  William A. Hudson  2017-12-01
//
// Error class.
//     Provide a global error message stream and flag.
//--------------------------------------------------------------------------

#include <iostream>
#include "Error.h"


// Init static Class Data:
int		Error::Error_cnt = 0;
std::ostream*	Error::cErr      = &std::cerr;


/*
* Init error stream.  (class method)
*    Optional - default is cerr.
*    This allows substituting an ostringstream for testing.
* call:
*    Error::Init_ostream( &cerr )
*/
void
Error::Init_ostream( std::ostream* erx )
{
    cErr = erx;
}


/*
* Get error flag.  (class method)
*    Return true if error messages have been sent.
* call:
*    Error::has_err()
*/
int
Error::has_err()
{
    return  Error_cnt;
}


/*
* Send error message.  (class method)
*    Returns an error stream with initial message "Error:  ".
*    This allows appending further output and using io manipulators.
*    User is rsponsible for the terminating newline.
*    Option to pass cstring text as an argument.
* call:
*    Error::msg() << "text" << .. <<endl;
*    Error::msg( "text\n" );
*    Error::msg( "text" ) << .. <<endl;
*/
std::ostream&
Error::msg()
{
    Error_cnt++;
    *cErr << "Error:  ";
    return  *cErr;
}

std::ostream&
Error::msg( const char* text )
{
    Error::msg() << text;
    return  *cErr;
}


//#!! Obsolete methods:

using namespace std;

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

