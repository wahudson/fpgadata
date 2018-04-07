// 2018-03-24  William A. Hudson
//
// LFSR (Linear Feedback Shift Register) exercise program.
//
//--------------------------------------------------------------------------

#include <iostream>
#include <iomanip>
#include <string>
#include <stdlib.h>

using namespace std;

#include "gLfsr.h"

#include "Error.h"
#include "yOption.h"


//--------------------------------------------------------------------------
// Option Handling
//--------------------------------------------------------------------------

class yOptLong : public yOption {

//  public:	// inherited
//    char*		ProgName;
//    int		get_argc();
//    char*		next_arg();
//    bool		next();
//    bool		is( const char* opt );
//    char*		val();
//    char*		current_option();

  public:	// option values

    const char*		num;
    const char*		obit;
    const char*		poly;
    const char*		seed;

    bool		verbose;
    bool		debug;
    bool		TESTOP;

  public:	// data values

    int			num_n;
    int			obit_n;
    uint32_t		poly_n;
    uint32_t		seed_n;

  public:
    yOptLong( int argc,  char* argv[] );	// constructor

    void		parse_options();
    void		print_option_flags();
    void		print_usage();

};


/*
* Constructor.  Init options with default values.
*    Pass in the main() argc and argv parameters.
* call:
*    yOptLong	Opx  ( argc, argv );
*    yOptLong	Opx = yOptLong::yOptLong( argc, argv );
*/
yOptLong::yOptLong( int argc,  char* argv[] )
    : yOption( argc, argv )
{
    num         = "";
    obit        = "";
    poly        = "";
    seed        = "";

    verbose     = 0;
    debug       = 0;
    TESTOP      = 0;

    num_n       = 16;
    obit_n      = 8;
    poly_n      = 0x14;		// 5-bit, taps 5,3
    seed_n      = 1;
}


/*
* Parse options.
*/
void
yOptLong::parse_options()
{
    while ( this->next() )
    {
	if      ( is( "--num="       )) { num        = this->val(); }
	else if ( is( "--obit="      )) { obit       = this->val(); }
	else if ( is( "--poly="      )) { poly       = this->val(); }
	else if ( is( "--seed="      )) { seed       = this->val(); }

	else if ( is( "--verbose"    )) { verbose    = 1; }
	else if ( is( "-v"           )) { verbose    = 1; }
	else if ( is( "--debug"      )) { debug      = 1; }
	else if ( is( "--TESTOP"     )) { TESTOP     = 1; }
	else if ( is( "--help"       )) { this->print_usage();  exit( 0 ); }
	else if ( is( "-"            )) {                break; }
	else if ( is( "--"           )) { this->next();  break; }
	else {
	    Error::msg( "unknown option:  " ) << this->current_option() <<endl;
	}
    }

    string	num_s   ( num );
    string	obit_s  ( obit );
    string	poly_s  ( poly );
    string	seed_s  ( seed );

    if ( num_s.length() ) {
	num_n = stoi( num_s );
    }

    if ( obit_s.length() ) {
	obit_n = stoi( obit_s );
    }

    if ( poly_s.length() ) {
	poly_n = stoul( poly_s, NULL, 0 );
    }

    if ( seed_s.length() ) {
	seed_n = stoul( seed_s, NULL, 0 );
    }

    if ( this->get_argc() > 0 ) {
	Error::msg( "no argument required" ) <<endl;
    }
}


/*
* Show option flags.
*/
void
yOptLong::print_option_flags()
{

    cout << "--num         = " << num          << endl;
    cout << "--obit        = " << obit         << endl;
    cout << "--poly        = " << poly         << endl;
    cout << "--seed        = " << seed         << endl;
    cout << "--verbose     = " << verbose      << endl;
    cout << "--debug       = " << debug        << endl;

    char*	arg;
    while ( ( arg = next_arg() ) )
    {
	cout << "arg:          = " << arg          << endl;
    }

    cout << "--num_n       = " << num_n        << endl;
    cout << "--obit_n      = " << obit_n       << endl;
    cout << "--poly_n      = " << poly_n       << endl;
    cout << "--seed_n      = " << seed_n       << endl;
}


/*
* Show usage.
*/
void
yOptLong::print_usage()
{
    cout <<
    "    LFSR (Linear Feedback Shift Register) exercise program\n"
    "usage:  " << ProgName << " [options..]\n"
    "  options:\n"
    "    --num=N             number of steps output\n"
    "    --obit=N            output number of LSB bits\n"
    "    --poly=P            tap polynomial bit pattern, hex\n"
    "    --seed=P            seed\n"
    "    --help              show this usage\n"
//  "    -v, --verbose       verbose output\n"
//  "    --debug             debug output\n"
    "  (options with GNU= only)\n"
    ;

// Hidden options:
//       --TESTOP       test mode show all options
}


//--------------------------------------------------------------------------
// Main program
//--------------------------------------------------------------------------

int
main( int	argc,
      char	*argv[]
) {

    try {
	yOptLong		Opx  ( argc, argv );	// constructor

	Opx.parse_options();

	if ( Opx.TESTOP ) {
	    Opx.print_option_flags();
	    return ( Error::has_err() ? 1 : 0 );
	}

	uint32_t		mask = (0x1 << Opx.obit_n) - 1;

	if ( Error::has_err() )  return 1;

	gLfsr			Lx  ( Opx.poly_n );	// constructor

	for ( int i=0;  i<Opx.num_n;  i++ )
	{
	    uint32_t		reg;

	    reg = Lx.next_state();

	    cout << setw(2) << (reg & mask) << endl;
	}

    }
    catch ( std::exception& e ) {
	Error::msg( "exception caught:  " ) << e.what() <<endl;
    }
    catch (...) {
	Error::msg( "unexpected exception\n" );
    }

    return ( Error::has_err() ? 1 : 0 );
}

