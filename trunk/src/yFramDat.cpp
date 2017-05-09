// 2017-04-22  William A. Hudson

// Frame Data base class.
//
//--------------------------------------------------------------------------

#include <iostream>
#include <iomanip>

using namespace std;

#include "Error.h"
#include "yFramDat.h"


/*
* Constructor.
*/
yFramDat::yFramDat()
{
    data = NULL;
    size = 0;
    len  = 0;
}


/*
* Constructor.
* call:
*    yFramDat	fdat  ( size );
*    yFramDat	fdat = yFramDat::yFramDat( size );
*/
yFramDat::yFramDat( size_t nsize )
{
// Note:  C++ cannot new() an arbitrary sized array.
// warning: ISO C++ does not support variable-length array types [-Wvla]
//    data = new( unsigned char [nsize] );

    const int	sz = 2 * 1024 * 1024;

    len  = 0;
    size = 0;
    data = new( uint16_t [sz+1] );

    if ( nsize > sz ) {
	Error::err( "yFramDat() nsize too large\n" );
    }

    if ( data ) {
	data[sz+1] = '\0';
	size = sz;
    }
}


/*
* Destructor.
*/
yFramDat::~yFramDat()
{
    delete( data );
}


/*
* Show debug output.
* call:
*    self.show_debug()
*/
void
yFramDat::show_debug()
{
    cout<< "size= "    << size
	<< "  len= "   << len
	<< "  data=* " << (void *) data
	<< endl;
}


/*
* Check data array limit, reduce as necessary. 
* Use in  "for ( i=self.nlimit( n_trans ); ..)"
* call:
*    self.nlimit( n_trans )
* return:
*    ()  = limited value
*/
int
yFramDat::nlimit(
    unsigned int	ntran
)
{
    if ( ntran <= size ) {
	return( ntran );
    }
    else {
	return( size );
	cerr << "Error:  yFramDat::nlimit() size exceeded" << endl;
    }
}


/*
* Push raw data onto array.
*    Data is 16-bit words.
* call:
*    self.push_dat( value )
* return:
*    ()  : status, 1= success, 0= fail full array
*/
bool
yFramDat::push_dat(
    uint16_t	value
)
{
    if ( len < size ) {
	data[ len++ ] = value;
	return( 1 );
    }
    else {
	return( 0 );
    }
}


/*
* Print data as 16x 16-bit coefficients, tabular format.
* call:
*    self.print_coeff16_tab()
*/
void
yFramDat::print_coeff16_tab()
{
    unsigned int	coeff;

    cout << " index    c0    c1    c2    c3    c4    c5    c6    c7"
                  "    c8    c9   c10   c11   c12   c13   c14   c15" << endl;
    cout << "------ ----- ----- ----- ----- ----- ----- ----- -----"
                  " ----- ----- ----- ----- ----- ----- ----- -----" << endl;
    cout <<dec;
    cout.fill(' ');
    for ( unsigned int i = 0;  i < len;  )
    {
	cout <<setw(6) << i / 32;

	for ( int j = 0;  j < 16;  j++ )
	{
	    if ( i >= len ) { break; }

	    coeff = data[i++] & 0xff;
	    coeff = coeff << 8;
	    coeff = coeff | (data[i++] & 0xff);

	    cout << " " <<setw(5) << coeff;
	}
	cout << endl;
    }
    cout << dec;
}


/*
* Print data as 16x 16-bit coefficients, CSV format.
* call:
*    self.print_coeff16_csv()
*/
void
yFramDat::print_coeff16_csv()
{
    unsigned int	coeff;

    cout << "index,c0,c1,c2,c3,c4,c5,c6,c7,"
                  "c8,c9,c10,c11,c12,c13,c14,c15" << endl;
    cout <<dec;
    cout.fill(' ');
    for ( unsigned int i = 0;  i < len;  )
    {
	cout << i / 32;

	for ( int j = 0;  j < 16;  j++ )
	{
	    if ( i >= len ) { break; }

	    coeff = data[i++] & 0xff;
	    coeff = coeff << 8;
	    coeff = coeff | (data[i++] & 0xff);

	    cout << "," << coeff;
	}
	cout << endl;
    }
    cout << dec;
}


/*
* Print data as 16x int16_t coefficients, tabular format.
*     Big-endian data.
*/
void
yFramDat::print_coeff_int16B_tab()
{
    int16_t	coeff;

    cout << " index     c0     c1     c2     c3     c4     c5     c6     c7"
                  "     c8     c9    c10    c11    c12    c13    c14    c15" << endl;
    cout << "------ ------ ------ ------ ------ ------ ------ ------ ------"
                  " ------ ------ ------ ------ ------ ------ ------ ------" << endl;
    cout <<dec;
    cout.fill(' ');
    for ( unsigned int i = 0;  i < len;  )
    {
	cout <<setw(6) << i / 32;

	for ( int j = 0;  j < 16;  j++ )
	{
	    if ( i >= len ) { break; }

	    coeff = data[i++] & 0xff;
	    coeff = coeff << 8;
	    coeff = coeff | (data[i++] & 0xff);

	    cout << " " <<setw(6) << coeff;
	}
	cout << endl;
    }
    cout << dec;
}


/*
* Print data as 16x int16_t coefficients, CSV format.
*     Big-endian data.
*/
void
yFramDat::print_coeff_int16B_csv()
{
    int16_t	coeff;

    cout << "index,c0,c1,c2,c3,c4,c5,c6,c7,"
                  "c8,c9,c10,c11,c12,c13,c14,c15" << endl;
    cout <<dec;
    cout.fill(' ');
    for ( unsigned int i = 0;  i < len;  )
    {
	cout << i / 32;

	for ( int j = 0;  j < 16;  j++ )
	{
	    if ( i >= len ) { break; }

	    coeff = data[i++] & 0xff;
	    coeff = coeff << 8;
	    coeff = coeff | (data[i++] & 0xff);

	    cout << "," << coeff;
	}
	cout << endl;
    }
    cout << dec;
}


/*
* Print data as a hex dump.
*    Output in big-endian, address ascending to the right.
*    Data is 16-bit words, in hex format.
* call:
*    self.print_hex_dump()
*/
void
yFramDat::print_hex_dump()
{
    cout << " index     0     1     2     3     4     5     6     7" << endl;
    cout << " (hex)     8     9     a     b     c     d     e     f" << endl;
    cout <<hex;
    cout.fill('0');
    for ( unsigned int i = 0;  i < len;  )
    {
	cout <<setw(6) << i;

	for ( int j = 0;  j < 8;  j++, i++ )
	{
	    if ( i < len ) {
		cout << "  " <<setw(4) << (unsigned int) data[i];
		// cast from uint16_t
	    }
	    else {
		break;
	    }
	}
	cout << endl;
    }
    cout <<dec;
}


/*
* Print raw data as 16-bit words, with index.
*    Data is 16-bit words, in hex.
* call:
*    self.print_index_data()
*/
void
yFramDat::print_index_data()
{
    cout << " index   hex" << endl;
    cout <<dec;
    cout.fill('0');
    for ( unsigned int i = 0;  i < len;  i++  )
    {
	cout <<dec <<setw(6) << i << "  ";
	cout <<hex <<setw(4) << (unsigned int) data[i] << endl;
	// cast from uint16_t
    }
    cout <<dec;
}


/*
* Print data as 16-bit words in decimal, with index and delta.
*    Data is 16-bit words, in decimal.
*    Delta in decimal (current - previous).
*    Intended for use with a counter.
* call:
*    self.print_delta_data()
*/
void
yFramDat::print_delta_data()
{
    int			dd;
    int			dlast = 0;

    cout << " index   data  delta" << endl;
    cout <<dec;
    cout.fill(' ');

    for ( unsigned int i = 0;  i < len;  i++  )
    {
	dd = data[i];		// convert from uint16_t

	cout <<setw(6) << i            << "  "
	     <<setw(5) << dd           << "  "
	     <<setw(5) << (dd - dlast)
	     <<endl;
	dlast = dd;
    }
    cout <<dec;
}


/*
* Print data as 8-bit words with flag bits, index, and delta.
*    Flag bits in octal.
*    Data is 8-bit words, in decimal.
*    Delta in decimal (current - previous).
* call:
*    self.print_flag_data()
*/
void
yFramDat::print_flag_data()
{
    uint32_t		dd;
    uint32_t		ff;
    int			dlast = 0;

    cout << " index flag   data  delta" << endl;

    for ( unsigned int i = 0;  i < len;  i++  )
    {
	dd =   data[i] & 0x00ff;
	ff = ( data[i] & 0x0f00 ) >> 8;

	cout <<setw(6) <<dec <<setfill(' ') << i  << "  "
	     <<setw(3) <<oct <<setfill('0') << ff << "  "
	     <<setw(5) <<dec <<setfill(' ') << dd << "  "
	     <<setw(5) <<dec <<setfill(' ') << ((int) dd - dlast)
	     <<endl;

	dlast = dd;
    }
    cout <<dec;
    cout.fill(' ');
}

