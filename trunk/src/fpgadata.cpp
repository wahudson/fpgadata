// 2017-04-22  William A. Hudson
//
// Get FPGA Data.
//--------------------------------------------------------------------------

#include <iostream>
#include <iomanip>
#include <string>
#include <stdlib.h>

using namespace std;

#include "Error.h"
#include "yOption.h"
#include "yFramDat.h"


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

    const char*		npix;
    const char*		prefix;
    bool		csv;
    bool		tab;
    bool		hex;

    bool		verbose;
    bool		debug;
    bool		TESTOP;

  public:	// data values

    int			npix_n;			// number of pixels

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
    npix        = "";
    prefix      = "";
    csv         = 0;
    tab         = 0;
    hex         = 0;

    verbose     = 0;
    debug       = 0;
    TESTOP      = 0;

    npix_n      = 64;
}


/*
* Parse options.
*/
void
yOptLong::parse_options()
{
    while ( this->next() )
    {
	if      ( is( "--npix="      )) { npix       = this->val(); }
	else if ( is( "--prefix="    )) { prefix     = this->val(); }
	else if ( is( "--csv"        )) { csv        = 1; }
	else if ( is( "--tab"        )) { tab        = 1; }
	else if ( is( "--hex"        )) { hex        = 1; }

	else if ( is( "--verbose"    )) { verbose    = 1; }
	else if ( is( "-v"           )) { verbose    = 1; }
	else if ( is( "--debug"      )) { debug      = 1; }
	else if ( is( "--TESTOP"     )) { TESTOP     = 1; }
	else if ( is( "--help"       )) { this->print_usage();  exit( 0 ); }
	else if ( is( "-"            )) {                break; }
	else if ( is( "--"           )) { this->next();  break; }
	else {
	    Error::err( "unknown option:  ", this->current_option() );
	}
    }

    if ( ! ( csv || tab || hex ) ) {
	tab = 1;
    }

    string	npix_s  ( npix );

    if ( npix_s.length() ) {
	npix_n = stoi( npix_s );
    }
}


/*
* Show option flags.
*/
void
yOptLong::print_option_flags()
{

    cout << "--npix        = " << npix         << endl;
    cout << "--prefix      = " << prefix       << endl;
    cout << "--csv         = " << csv          << endl;
    cout << "--tab         = " << tab          << endl;
    cout << "--hex         = " << hex          << endl;
    cout << "--verbose     = " << verbose      << endl;
    cout << "--debug       = " << debug        << endl;

    char*	arg;
    while ( ( arg = next_arg() ) )
    {
	cout << "arg:          = " << arg          << endl;
    }

    cout << "npix_n        = " << npix_n       << endl;
}


/*
* Show usage.
*/
void
yOptLong::print_usage()
{
    cout <<
    "    List USB device attributes.\n"
    "usage:  " << ProgName << " [options]\n"
    "  output forms:\n"
    "    --csv               CSV format\n"
    "    --tab               tabular format\n"
    "    --hex               hex data dump\n"
    "  options:\n"
    "    --npix=N            number of pixel to collect\n"
    " #  --gray=N,N,...      image file coefficient numbers\n"
    " #  --prefix=NAME       file name prefix\n"
    "    --help              show this usage\n"
    "    -v, --verbose       verbose output\n"
    "    --debug             debug output\n"
    "  (options with GNU= only)\n"
    ;

// Hidden options:
//       --TESTOP       test mode show all options
}


//--------------------------------------------------------------------------
// yMain object class
//--------------------------------------------------------------------------

class yMain {
  private:

  public:
    yOptLong		*opx;

  public:
    yMain();					// constructor
    yMain( yOptLong *optx );			// constructor
};


/*
* Constructor.
*/
yMain::yMain()
{
}


/*
* Constructor.
*    Pass in reference to option object.
*    !! Probably refactor this class to build the option object.
*/
yMain::yMain( yOptLong *optx )
{
    opx          = optx;

}


//--------------------------------------------------------------------------
// Main program
//--------------------------------------------------------------------------

int
main( int	argc,
      char	*argv[]
) {
    try {
//	cerr << "Try" << endl;

	yOptLong		Opx  ( argc, argv );	// constructor

	try {
	    Opx.parse_options();
	}
	catch (...) {
	    Error::err( "in option parsing" );
	    return 1;
	}

	yMain			Mnx  ( &Opx );	// constructor

	if ( Opx.TESTOP ) {
	    Opx.print_option_flags();
	    return ( Error::err() ? 1 : 0 );
	}

	if ( Error::err() )  return 1;

	yFramDat		Fdx  ( 10 );	// constructor

	for ( int i = 0;  i<172;  i++ )
	{
	    Fdx.push_dat( 0 );
	    i++;
	    Fdx.push_dat( i+1 );
	}

	if ( Opx.debug ) {
	    Fdx.show_debug();
	}

	if ( Opx.tab ) {
	    Fdx.print_coeff16_tab();
	}

	if ( Opx.csv ) {
	    cout << endl;
	    Fdx.print_coeff16_csv();
	}

	if ( Opx.hex ) {
	    cout << endl;
	    Fdx.print_hex_dump();
	}

    }
    catch (...) {
	cerr << "caught something" << endl;
    }

//    cerr << "End" << endl;

    return ( Error::err() ? 1 : 0 );
}

