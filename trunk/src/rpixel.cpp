// 2017-04-22  William A. Hudson
//
// Get FPGA Data.
//--------------------------------------------------------------------------

#include <iostream>
#include <iomanip>
#include <string>
#include <stdlib.h>
#include <stdexcept>	// std::stdexcept

using namespace std;

#include "Error.h"
#include "yOption.h"
#include "yRpiGpio.h"
#include "yFramDat.h"
#include "yCoeffItr.h"
#include "yBuffStat.h"

#define CLKID	CLOCK_MONOTONIC_RAW

// GPIO bit postions, in BCM register
//   28   24   20   16   12    8    4    0     bit number
// .... .... dddd dddd .... .... .... ....  i  DATA   bits
// .... ...m .... .... .... .... .... ....  i  MetaRead flag
// .... .f.. .... .... .... .... .... ....  i  OVFLOW flag (fifo write_full)
// .... n... .... .... .... .... .... ....  i  NODATA flag (fifo empty)
// .... .... .... .... .... .... .r.. ....   o ReadAck fifo read aknowledge
// .... .... .... .... .... .... ..g. ....   o GoPixel start one coefficient
// .... .... .... .... .... .... R... ....   o nReset  reset fifo state
// .... .... .... .... .... ...T .... ....   o TrigOut trigger event

//#define DATA_G	0x00ff0000	// DATA
#define COEFF_G		0x00f00000	// Coefficient nibble in data
#define NODATA_G	0x08000000	// NODATA flag, 1= fifo empty
#define OVFLOW_G	0x04000000	// OVFLOW flag, 1= fifo write_full
#define METAREAD_G	0x01000000	// MetaRead flag, 1= repeated read
#define READAK_G	0x00000040	// ReadAck fifo read aknowledge
#define GOPIXEL_G	0x00000020	// GoPixel start one coefficient
#define NRESET_G	0x00000080	// nReset fifo state
#define TRIGOUT_G	0x00000100	// TrigOut trigger event

#define DATA_POS	16		// position of data LSB
#define DATA_MASK	0x000000ff	// data width mask, after shift right
#define FULL_MASK	0x00000fff	// flags plus data, after shift right

// Currently we intend the FPGA filter to be a free running data stream.
// Outputs nReset and GoPixel can be used to help identify state of the
// transfer.

// #!! GoPixel now indicates start of a coefficient.  Use to help debug
// fifo 'rdempty' (NoData) timing problems.  Re-using a gpio pin.


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
    bool		tab2;
    bool		hex;
    bool		raw;
    bool		delta;
    bool		flag;

    const char*		load;
    const char*		save;

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
    tab2        = 0;
    hex         = 0;
    raw         = 0;
    delta       = 0;
    flag        = 0;

    load        = NULL;
    save        = NULL;

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
	else if ( is( "--tab2"       )) { tab2       = 1; }
	else if ( is( "--hex"        )) { hex        = 1; }
	else if ( is( "--raw"        )) { raw        = 1; }
	else if ( is( "--delta"      )) { delta      = 1; }
	else if ( is( "--flag"       )) { flag       = 1; }

	else if ( is( "--load="      )) { load       = this->val(); }
	else if ( is( "--save="      )) { save       = this->val(); }

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
    if ( load == NULL ) { load = "-"; }
    if ( save == NULL ) { save = "-"; }

    cout << "--npix        = " << npix         << endl;
    cout << "--repeat      = " << repeat       << endl;
    cout << "--prefix      = " << prefix       << endl;
    cout << "--csv         = " << csv          << endl;
    cout << "--tab         = " << tab          << endl;
    cout << "--tab2        = " << tab2         << endl;
    cout << "--hex         = " << hex          << endl;
    cout << "--raw         = " << raw          << endl;
    cout << "--delta       = " << delta        << endl;
    cout << "--flag        = " << flag         << endl;
    cout << "--load        = " << load         << endl;
    cout << "--save        = " << save         << endl;
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
    "    --tab2              tabular format, no check\n"
    "    --hex               hex data dump\n"
    "    --raw               raw hex data\n"
    "    --delta             delta data in decimal\n"
    "    --flag              octal flags with 8-bit data in decimal\n"
    "  raw data:  one sample per line, with headline\n"
    "    --load=FILE         load hex words from file\n"
    "    --save=FILE         save hex words to   file\n"
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
	yBuffStat		Bsx  ( 64 );	// SampleSize

	unsigned		ilevel;		// GPIO read value
	int			overflow;	// OVFLOW_G
	int			flush_cnt;	// flush fifo cycles

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
	n_trans = Fdx.nlimit( Opx.npix_n * 16 * 4 );	// 16 coeff x 4 nibbles
	cerr << "    n_trans= " << n_trans << endl;

	for ( int jj=1;  jj<=Opx.repeat_n;  jj++ )	// time repeats
	{
	    Fdx.clear();
	    Bsx.reset();
	    overflow = 0;

	    // Flush fifo
	    *gpio_clr = NRESET_G;
	    for ( flush_cnt=0;  flush_cnt<10000;  flush_cnt++ )
	    {
		ilevel = *gpio_read;	// Read GPIO level
		*gpio_set = READAK_G;
		*gpio_set = READAK_G;
		*gpio_set = READAK_G;
		*gpio_set = READAK_G;
		*gpio_set = READAK_G;

		*gpio_clr = READAK_G;
		// if ( ilevel & NODATA_G ) { break; }
		// The fifo 'rdempty' signal (NoData) seems to be true even
		// though fifo is full.
	    }
	    *gpio_set = NRESET_G;
	    if ( ! (ilevel & NODATA_G) ) {	// fifo not empty
		cerr << "Error:  nReset:  fifo not empty (NoData=0)" << endl;
	    }

	    // Find first coeff
	    while ( 1 )
	    {
		ilevel = *gpio_read;	// Read GPIO level
		if ( ((ilevel & NODATA_G) == 0)   &&
		     ((ilevel & COEFF_G)  == 0x0) ) {
		    break;	// no read acknowledge
		}

		*gpio_set = READAK_G;
		*gpio_set = READAK_G;
		*gpio_set = READAK_G;
		*gpio_set = READAK_G;
		*gpio_set = READAK_G;

		*gpio_clr = READAK_G;
	    }

	    unsigned int	coef_num = 0;
	    unsigned int	coef_old = 0;

	    rv = clock_gettime( CLKID, &tpA );

	    while ( Fdx.get_length() < n_trans )
	    {
	        for ( int kk=0;  kk<(16*4); )	// each coefficient nibble
		{
		    ilevel = *gpio_read;	// Read GPIO level
//		    cin >>hex >> ilevel;	// Read test data on stdin

		    *gpio_set = READAK_G;
		    *gpio_set = READAK_G;
		    *gpio_set = READAK_G;
		    *gpio_set = READAK_G;
		    *gpio_set = READAK_G;

		    *gpio_clr = READAK_G;
		    *gpio_clr = READAK_G;
		    *gpio_clr = READAK_G;
		    *gpio_clr = READAK_G;
		    *gpio_clr = READAK_G;

		    Bsx.cnt_by_call( ilevel & NODATA_G );

		    if ( ilevel & OVFLOW_G ) {	// fifo overflow
			overflow++;
		    }

		    coef_num = ilevel & COEFF_G;
		    if ( coef_num != coef_old ) {	// signal new coeff
			*gpio_set = GOPIXEL_G;
			*gpio_set = GOPIXEL_G;
			*gpio_set = GOPIXEL_G;
			*gpio_set = GOPIXEL_G;
			*gpio_set = GOPIXEL_G;

			coef_old  = coef_num;
			*gpio_clr = GOPIXEL_G;
		    }

		    if ( ilevel & NODATA_G ) {	// fifo empty
//			continue;
		    }

		    Fdx.push_dat( (ilevel >> DATA_POS) & FULL_MASK );
		    kk++;
		}
	    }

	    rv = clock_gettime( CLKID, &tpB );

	    if ( rv ) { cerr << "Error:  clock_gettime() failed" << endl; }

	    long int	delta_s  = tpB.tv_sec  - tpA.tv_sec;
	    long int	delta_ns = tpB.tv_nsec - tpA.tv_nsec;
	    if ( delta_ns < 0 ) {
		delta_ns += 1000000000;
		delta_s  -= 1;
	    }

	    cerr << "  FlushFifo_cy= " << flush_cnt <<endl;
	    cerr << "  NoData " << Bsx.text_stats_by_call();
	    cerr << "    OverFlow= " << overflow <<endl;

	    cerr << "    delta_ns[" <<setw(2) << jj << "]= "
		 <<setw(9) << delta_ns << "  "
		 <<setw(4) << (delta_ns / n_trans) << " ns/xfer"
		 <<endl;
	}

//	cout << "    A.tv_sec  = " << tpA.tv_sec  << endl;
//	cout << "    A.tv_nsec = " << tpA.tv_nsec << endl;
//	cout << "    B.tv_sec  = " << tpB.tv_sec  << endl;
//	cout << "    B.tv_nsec = " << tpB.tv_nsec << endl;

	if ( Opx.load ) {
	    Fdx.load_hex( Opx.load );
	}

	if ( Opx.save ) {
	    Fdx.save_hex( Opx.save );
	}

	if ( Opx.debug ) {
	    Fdx.show_debug();
	}

	if ( Opx.tab ) {
	    yCoeffItr		dit  ( &Fdx );
	    dit.print_coeff_tab();
	    cout << endl;
	}

	if ( Opx.csv ) {
	    yCoeffItr		dit  ( &Fdx );
	    dit.print_coeff_csv();
	    cout << endl;
	}

	if ( Opx.tab2 ) {	// old method
	    Fdx.print_coeff_nibbleB_tab();
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

	if ( Opx.flag ) {
	    Fdx.print_flag_hex();
	    cout << endl;
	}

    }
    catch ( std::exception& e ) {
        Error::err( "exception:  ", e.what() );
    }
    catch (...) {
        Error::err( "unexpected exception" );
    }

    return ( Error::err() ? 1 : 0 );
}

