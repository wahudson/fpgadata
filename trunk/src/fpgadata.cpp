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

// GPIO bit postions, in BCM register
//   28   24   20   16   12    8    4    0     bit number
// .... .... dddd dddd .... .... .... ....  i  DATA   bits
// .... ...m .... .... .... .... .... ....  i  metadata flag ???
// .... n... .... .... .... .... .... ....  i  NODATA flag (fifo empty)
// .... .... .... .... .... .... .r.. ....   o READAK fifo read aknowledge

// .... .... .... .... ..dd dddd dd.r ....  DATA   bits

//#define DATA_G	0x00ff0000	// DATA
#define NODATA_G	0x08000000	// NODATA flag, 1= fifo empty
#define READAK_G	0x00000040	// READAK fifo read aknowledge

#define DATA_POS	16		// position of data LSB
#define DATA_MASK	0x000000ff	// data width mask, after shift right


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
    bool		delta;

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
    delta       = 0;

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
	else if ( is( "--delta"      )) { delta      = 1; }

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

    if ( get_argc() > 0 ) {
	Error::err( "extra arguments:  ", next_arg() );
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
    cout << "--delta       = " << delta        << endl;
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
    "    FPGA data transfer on Raspberry Pi\n"
    "usage:  " << ProgName << " [options]\n"
    "  output forms:  (default is none)\n"
    "    --csv               CSV format\n"
    "    --tab               tabular format\n"
    "    --hex               hex data dump\n"
    "    --raw               raw hex data\n"
    "    --delta             delta data in decimal\n"
    "  options:\n"
    "    --npix=N            number of pixel to collect\n"
    "    --repeat=N          repeat data read loop N times\n"
//  " #  --gray=N,N,...      image file coefficient numbers\n"
//  " #  --prefix=NAME       file name prefix\n"
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
    int			n_trans;	// loop number of transfers

    try {
	yOptLong		Opx  ( argc, argv );	// constructor

	Opx.parse_options();

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
	n_trans = Fdx.nlimit( Opx.npix_n );
	cerr << "    n_trans= " << n_trans << endl;

	for ( int jj=1;  jj<=Opx.repeat_n;  jj++ )
	{
	    Fdx.clear();
	    rv = clock_gettime( CLKID, &tpA );

	    unsigned	ilevel;
//	    for ( int ii=n_trans;  ii>0;  ii-- )
	    while ( Fdx.get_length() < n_trans )
	    {
		ilevel = *gpio_read;	// Read GPIO level

		*gpio_set = READAK_G;
		*gpio_set = READAK_G;
		*gpio_set = READAK_G;
		*gpio_set = READAK_G;

		*gpio_clr = READAK_G;

		if ( ilevel & NODATA_G ) {	// fifo empty
		    continue;
		}
		Fdx.push_dat( (ilevel >> DATA_POS) & DATA_MASK );
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
		 <<setw(9) << delta_ns << "  "
		 <<setw(4) << (delta_ns / n_trans) << " ns/xfer"
		 <<endl;
	}

//	cout << "    A.tv_sec  = " << tpA.tv_sec  << endl;
//	cout << "    A.tv_nsec = " << tpA.tv_nsec << endl;
//	cout << "    B.tv_sec  = " << tpB.tv_sec  << endl;
//	cout << "    B.tv_nsec = " << tpB.tv_nsec << endl;

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

	if ( Opx.delta ) {
	    Fdx.print_delta_data();
	    cout << endl;
	}

    }
    catch (...) {
	cerr << "caught something" << endl;
    }

    return ( Error::err() ? 1 : 0 );
}

