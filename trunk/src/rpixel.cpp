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
// .... ...x .... .... .... .... .... ....  i  MarkX scan mark
// .... ..y. .... .... .... .... .... ....  i  MarkY scan mark
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
// #define MARKY_G	0x02000000	// MarkY scan mark
// #define MARKX_G	0x01000000	// MarkX scan mark
#define READAK_G	0x00000040	// ReadAck fifo read aknowledge
#define GOPIXEL_G	0x00000020	// GoPixel start one coefficient
#define NRESET_G	0x00000080	// nReset fifo state
#define TRIGOUT_G	0x00000100	// TrigOut trigger event

#define DATA_POS	16		// position of data LSB
#define DATA_MASK	0x000000ff	// data width mask, after shift right
#define FULL_MASK	0x00000fff	// flags plus data, after shift right

// Scan marks MARKY_G, MARKX_G are included in FULL_MASK, and are not
// used directly.  Here for documentation.

// Currently we intend the FPGA filter to be a free running data stream.
// Outputs nReset and GoPixel can be used to help identify state of the
// transfer.


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
    const char*		stream;
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
    int			stream_n;		// number of pixels
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
    stream      = "";
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
    stream_n    = 0;		// default must be no streaming
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
	else if ( is( "--stream="    )) { stream     = this->val(); }
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
    string	stream_s  ( stream );
    string	repeat_s  ( repeat );

    if ( npix_s.length() ) {
	npix_n = stoi( npix_s );
    }

    if ( stream_s.length() ) {
	stream_n = stoi( stream_s );
    }

    if ( repeat_s.length() ) {
	repeat_n = stoi( repeat_s );
    }

    if ( stream_n && ( csv || tab || tab2 ) ) {
	Error::err( "--stream only outputs CSV format" );
    }
    // --stream not intended with other outputs, but allow for debug.

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
    cout << "--stream      = " << stream       << endl;
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
    cout << "stream_n      = " << stream_n     << endl;
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
    "    --stream=N          stream N pixels at a time to CSV output\n"
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
    "    --help              show this usage\n"
    "    -v, --verbose       verbose output\n"
    "    --debug             debug output\n"
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
    int			rv;
    struct timespec	tpA;
    struct timespec	tpB;
    int			n_trans;	// loop number of transfers

    try {
	yOptLong		Opx  ( argc, argv );	// constructor

	Opx.parse_options();

	if ( Opx.TESTOP ) {
	    Opx.print_option_flags();
	    return ( Error::err() ? 1 : 0 );
	}

	yFramDat		Fdx  ( 10 );	// constructor
//	yBuffStat		Bsx  ( 64 );	// SampleSize

	unsigned		ilevel;		// GPIO read value
	int			overflow;	// OVFLOW_G
	int			flush_cnt;	// flush fifo cycles
	int			sample_cnt;	// total read samples
	int			NoData_cnt;	// total NoData samples
	int			trans_cnt;	// total valid transfers
	int			coeff_cnt;	// total coefficients read

	int			stream_ii;	// stream burst pixel count
	yCoeffItr		stream_itr  ( &Fdx );

	if ( Error::err() )  return 1;

	if ( Opx.stream_n ) {
	    stream_itr.print_coeff_csv_head();
	}

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
	n_trans = Opx.npix_n * 16 * 4;		// 16 coeff x 4 nibbles
	if ( ! Opx.stream_n ) {
	    n_trans = Fdx.nlimit( n_trans );	// limit to array size
	}
	cerr << "    n_trans= " << n_trans << endl;
	// Count valid transfers so pixel identification is not required.

	for ( int jj=1;  jj<=Opx.repeat_n;  jj++ )	// time repeats
	{
	    Fdx.clear();
//	    Bsx.reset();
	    overflow = 0;
	    sample_cnt = 0;
	    NoData_cnt = 0;
	    trans_cnt  = 0;
	    coeff_cnt  = 0;
	    stream_ii  = 0;
	    stream_itr.restart();	// restart Fcx data pointer

	    // Init outputs
	    *gpio_clr = READAK_G | TRIGOUT_G | GOPIXEL_G;

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
		cerr << "Warning:  nReset:  fifo not empty (NoData=0)" << endl;
		// Warning, not fatal.
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

	    unsigned int	coef_num = 0;	// masked in-place
	    unsigned int	coef_old = 0xffffffff & COEFF_G;
		// Arrange for first 0 coefficient to signal GoPixel and
		// be counted in coeff_cnt.

	    rv = clock_gettime( CLKID, &tpA );

	    while ( trans_cnt < n_trans )
	    {
		ilevel = *gpio_read;	// Read GPIO level
//		cin >>hex >> ilevel;	// Read test data on stdin
		sample_cnt++;

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

//		Bsx.cnt_by_call( ilevel & NODATA_G );

		if ( ilevel & NODATA_G ) {	// fifo empty
		    NoData_cnt++;
		    continue;
		}

		if ( ilevel & OVFLOW_G ) {	// fifo overflow
		    overflow++;
		}

		trans_cnt++;

		coef_num = ilevel & COEFF_G;

		if ( coef_num != coef_old ) {	// signal new coeff
		    if ( coef_num == 0 ) {	// signal new pixel
			*gpio_set = GOPIXEL_G;

			if ( Opx.stream_n && ((++stream_ii) >= Opx.stream_n) ) {
//			    cout << "stream_ii=" << stream_ii << endl;
			    stream_ii = 0;
			    stream_itr.print_coeff_csv_body();
			    stream_itr.restart();	// restart Fcx pointer
			}
			// Stream old data before saving start of new pixel.
			// Note first set is short one pixel, not important.
		    }
		    *gpio_set = TRIGOUT_G;
		    *gpio_set = TRIGOUT_G;
		    *gpio_set = TRIGOUT_G;
		    *gpio_set = TRIGOUT_G;
		    *gpio_set = TRIGOUT_G;

		    coeff_cnt++;
		    coef_old  = coef_num;
		    *gpio_clr = TRIGOUT_G | GOPIXEL_G;
		}
		// Folded signals for more uniform timing.

		Fdx.push_dat( (ilevel >> DATA_POS) & FULL_MASK );
	    }

	    rv = clock_gettime( CLKID, &tpB );

	    if ( rv ) { cerr << "Error:  clock_gettime() failed" << endl; }

	    if ( Opx.stream_n ) {		// remainder of burst
//		cout << "stream remainder" << endl;
		stream_itr.print_coeff_csv_body();
		stream_itr.restart();
	    }

	    int64_t	delta_ns =
		((tpB.tv_sec  - tpA.tv_sec) * ((int64_t) 1000000000)) +
		 (tpB.tv_nsec - tpA.tv_nsec);
		// Note 4 seconds overflows a 32-bit int.
		// Use careful promotion to 64-bit integer to avoid overflow.

	    float		NoData_coeff = -1.0;
	    int			ns_coeff     = -1;
	    int			ns_sample    = -1;
	    if ( coeff_cnt ) {
		NoData_coeff = (float) NoData_cnt / coeff_cnt;
		ns_coeff     =         ( delta_ns / coeff_cnt );
	    }
	    if ( sample_cnt ) {
		ns_sample    =         ( delta_ns / sample_cnt );
	    }

	    cerr << "  FlushFifo_cy= " << flush_cnt <<endl;
//	    cerr << "  NoData " << Bsx.text_stats_by_call();
	    cerr << "    OverFlow=   " << overflow   <<endl;
	    cerr << "    sample_cnt= " << sample_cnt <<endl;
	    cerr << "    NoData_cnt= " << NoData_cnt <<endl;
	    cerr << "    coeff_cnt=  " << coeff_cnt  <<endl;

	    cerr << "    NoData per Coeff = "
		 <<setw(8) <<fixed <<setprecision(2) << NoData_coeff <<endl;

	    cerr << "    Coeff Rate       = "
		 <<setw(5) << ns_coeff << " ns/coeff" <<endl;

	    cerr << "    delta_ns[" <<setw(2) << jj << "]= "
		 <<setw(10) << delta_ns  << " ns,  "
		 <<setw(4)  << ns_sample << " ns/sample"
		 <<endl;

//	    cout << "    A.tv_sec  = " << tpA.tv_sec  << endl;
//	    cout << "    A.tv_nsec = " << tpA.tv_nsec << endl;
//	    cout << "    B.tv_sec  = " << tpB.tv_sec  << endl;
//	    cout << "    B.tv_nsec = " << tpB.tv_nsec << endl;
	}

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

	if ( overflow ) {
//#!!	    Error::err( "Fifo overflow count= ", overflow );
	    cerr << "Error:  Fifo overflow count= " << overflow << endl;
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

