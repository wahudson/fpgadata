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
#include "yRpiGpio.h"
#include "yFramDat.h"

#define CLKID	CLOCK_MONOTONIC_RAW


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
    const char*		repeat;
    const char*		prefix;
    bool		csv;
    bool		tab;
    bool		hex;
    bool		raw;

    bool		verbose;
    bool		debug;
    bool		TESTOP;

  public:	// data values

    int			npix_n;			// number of pixels
    int			repeat_n;		// repeat loop

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
    repeat      = "";
    prefix      = "";
    csv         = 0;
    tab         = 0;
    hex         = 0;
    raw         = 0;

    verbose     = 0;
    debug       = 0;
    TESTOP      = 0;

    npix_n      = 64;
    repeat_n    = 1;
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
	else if ( is( "--repeat="    )) { repeat     = this->val(); }
	else if ( is( "--prefix="    )) { prefix     = this->val(); }
	else if ( is( "--csv"        )) { csv        = 1; }
	else if ( is( "--tab"        )) { tab        = 1; }
	else if ( is( "--hex"        )) { hex        = 1; }
	else if ( is( "--raw"        )) { raw        = 1; }

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

    string	npix_s    ( npix );
    string	repeat_s  ( repeat );

    if ( npix_s.length() ) {
	npix_n = stoi( npix_s );
    }

    if ( repeat_s.length() ) {
	repeat_n = stoi( repeat_s );
    }
}


/*
* Show option flags.
*/
void
yOptLong::print_option_flags()
{

    cout << "--npix        = " << npix         << endl;
    cout << "--repeat      = " << repeat       << endl;
    cout << "--prefix      = " << prefix       << endl;
    cout << "--csv         = " << csv          << endl;
    cout << "--tab         = " << tab          << endl;
    cout << "--hex         = " << hex          << endl;
    cout << "--raw         = " << raw          << endl;
    cout << "--verbose     = " << verbose      << endl;
    cout << "--debug       = " << debug        << endl;

    char*	arg;
    while ( ( arg = next_arg() ) )
    {
	cout << "arg:          = " << arg          << endl;
    }

    cout << "npix_n        = " << npix_n       << endl;
    cout << "repeat_n      = " << repeat_n     << endl;
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
    "  output forms:  (default is none)\n"
    "    --csv               CSV format\n"
    "    --tab               tabular format\n"
    "    --hex               hex data dump\n"
    "    --raw               raw hex data\n"
    "  options:\n"
    "    --npix=N            number of pixel to collect\n"
    "    --repeat=N          repeat data read loop N times\n"
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
    int			rv;
    struct timespec	tpA;
    struct timespec	tpB;

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

	yFramDat		Fdx  ( 10 );	// constructor

	if ( Error::err() )  return 1;

	yRpiGpio		Gpx;		// constructor

	volatile unsigned	*gpio_read = Gpx.get_read_addr();
	volatile unsigned	*gpio_set  = Gpx.get_set_addr();
	volatile unsigned	*gpio_clr  = Gpx.get_clr_addr();

	if ( Opx.debug ) {
	    cout << "    gpio_read= " << (unsigned *)gpio_read << endl;
	    cout << "    gpio_set=  " << (unsigned *)gpio_set  << endl;
	    cout << "    gpio_clr=  " << (unsigned *)gpio_clr  << endl;
	}


    // Main Loop
	for ( int jj=1;  jj<=Opx.repeat_n;  jj++ )
	{
	    Fdx.clear();
	    rv = clock_gettime( CLKID, &tpA );

	    unsigned	ilevel;
	    for ( int ii=Fdx.nlimit( Opx.npix_n );  ii>0;  ii-- )
	    {
		ilevel = *gpio_read;	// Read GPIO level
		*gpio_set = 0x00010;
		*gpio_clr = 0x00010;
		Fdx.push_dat( (ilevel >> 6) & 0x00ff );
	    }

	    rv = clock_gettime( CLKID, &tpB );

	    if ( rv ) { cerr << "Error:  clock_gettime() failed" << endl; }

	    long int	delta_s  = tpB.tv_sec  - tpA.tv_sec;
	    long int	delta_ns = tpB.tv_nsec - tpA.tv_nsec;
	    if ( delta_ns < 0 ) {
		delta_ns += 1000000000;
		delta_s  -= 1;
	    }

	    cerr << "    delta_ns[" <<setw(2) << jj << "]= "
		 <<setw(9) << delta_ns << endl;
	}

//	cout << "    A.tv_sec  = " << tpA.tv_sec  << endl;
//	cout << "    A.tv_nsec = " << tpA.tv_nsec << endl;
//	cout << "    B.tv_sec  = " << tpB.tv_sec  << endl;
//	cout << "    B.tv_nsec = " << tpB.tv_nsec << endl;

/*
	for ( int i = 0;  i<172;  i++ )
	{
	    Fdx.push_dat( 0 );
	    i++;
	    Fdx.push_dat( i+1 );
	}
*/

	if ( Opx.debug ) {
	    Fdx.show_debug();
	}

	if ( Opx.tab ) {
	    Fdx.print_coeff16_tab();
	    cout << endl;
	}

	if ( Opx.csv ) {
	    Fdx.print_coeff16_csv();
	    cout << endl;
	}

	if ( Opx.hex ) {
	    Fdx.print_hex_dump();
	    cout << endl;
	}

	if ( Opx.raw ) {
	    Fdx.print_index_data();
	    cout << endl;
	}

    }
    catch (...) {
	cerr << "caught something" << endl;
    }

//    cerr << "End" << endl;

    return ( Error::err() ? 1 : 0 );
}

