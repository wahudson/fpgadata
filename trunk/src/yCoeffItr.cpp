// 2017-05-29  William A. Hudson

// Coefficient Data Iterator class.
//    Intended for extracting coefficients from the raw gpio data array.
//
//--------------------------------------------------------------------------

#include <iostream>
#include <iomanip>

using namespace std;

#include "Error.h"
#include "yFramDat.h"	// frame data
#include "yCoeffItr.h"

		//#!! Might be better if this was centralized.
		// Scan mark bit positions in *DaPtr
#define X_MARK_BIT	8
#define Y_MARK_BIT	9


/*
* Constructor.
*/
yCoeffItr::yCoeffItr(
    yFramDat		*fdp
)
{
    Fdata   = fdp;
    DaPtr   = Fdata->data_pointer_begin();
    PixNum  = -1;
    PixErr  = 0;
    PixMarkX   = 0;
    PixMarkY   = 0;

    for ( int jj = 0;  jj < 16;  jj++ )	// each coefficient
    {
	PixCoef[jj] = 0;
    }
}


/*
* Restart Fdata array.
*    Restart collecting Fdata, and restart the iterator.  Is NOT a full reset.
*    Used in pixel streaming.
*/
void
yCoeffItr::restart()
{
    Fdata->clear();
    DaPtr = Fdata->data_pointer_begin();
}


/*
* Get next pixel set of coefficients from Big-endian 4-bit nibbles.
*    Assume there are no NoData entries.
*    Coefficients are signed 16-bit values packed from big-endian nibbles.
*    Coefficient numbers are checked on each array entry.  If an alignment
*    error occures, the remaining coefficients are flagged with value -99999,
*    and array entries are skipped to re-synchronize on the start of the
*    next pixel.
*    Each array entry is packed bits:
*        data[15:0] = (0, OverFlow, Ymark, Xmark, cnum[3:0], nibble[3:0])
* call:
*    self.next_pixel()
* return:
*    ()  = pointer to coefficient arry, NULL at end of data
*/
int*
yCoeffItr::next_pixel()
{
    uint16_t		*max_dp;	// DaPtr past end of source array
    int			nib_err = 0;	// nibble error

    const int		COEFF_ERR = -99999;

    max_dp = Fdata->data_pointer_end();
    // Allow array to grow between calls.

    // Look at only first coefficient, first nibble MSB, for scan mark.
    PixMarkX = ((*DaPtr) >> X_MARK_BIT) & 0x1;
    PixMarkY = ((*DaPtr) >> Y_MARK_BIT) & 0x1;

    PixErr = 0;

    int			jj;
    for ( jj = 0;  jj < 16;  jj++ )	// each coefficient
    {
	int		cnum;		// coeff number in data array
	int16_t		cvalue  = 0;	// coeff value

	if ( DaPtr+3 >= max_dp ) {	// at limit
	    return  NULL;
	}

	for ( int k = 0;  k < 4;  k++, DaPtr++ )	// each nibble
	{
	    cvalue = (cvalue << 4) | (*DaPtr & 0xf);
	    cnum  = (*DaPtr >> 4) & 0xf;
	    if ( cnum != jj ) {
		nib_err = 1;
	    }
	}

	if ( nib_err ) {
	    break;
	}
	PixCoef[jj] = cvalue;
    }

    PixNum++;

    if ( nib_err ) {
	if ( ! PixErr ) {		// report only first error
	    Error::msg( "misaligned coeff at pixel= " )
		<< PixNum << "  coeff= " << jj <<endl;
	}
	PixErr = 1;

	for ( ;  jj < 16;  jj++ )	// remaining coefficients
	{
	    PixCoef[jj] = COEFF_ERR;	// flag value
	}

	// find start of next pixel to resynchronize
	for ( ;  (DaPtr+3) < max_dp;  DaPtr++ )
	{
	    if ( *(DaPtr  ) & 0xf0 ) {	// non-zero coeff number
		continue;
	    }
	    if ( *(DaPtr+3) & 0xf0 ) {
		continue;
	    }
	    break;	// assume all 4 nibbles have a zero coeff number
	}
    }

    return  PixCoef;	// array
}


/*
* Print coefficients, tabular format.
*    Bad pixel entry marked with '!'.
*    #!! Perhaps a little strange to put this in the iterator.
* call:
*    print_coeff_tab()
*/
void
yCoeffItr::print_coeff_tab()
{
    int			*cp;	// coefficient pointer

    cout << " index Ym X"
	"m    c0     c1     c2     c3     c4     c5     c6     c7"
	"     c8     c9    c10    c11    c12    c13    c14    c15"
	 << endl;
    cout << "------  - -"
	" ------ ------ ------ ------ ------ ------ ------ ------"
	" ------ ------ ------ ------ ------ ------ ------ ------"
	 << endl;
    cout <<dec;
    cout.fill(' ');

    while ( (cp = this->next_pixel()) )
    {
	cout <<setw(6) << PixNum;
	if ( this->has_error() ) {
	    cout << "!";
	}
	else {
	    cout << " ";
	}

	cout << " " << PixMarkY;
	cout << " " << PixMarkX;

	for ( int j = 0;  j < 16;  j++ )
	{
	    cout << " " <<setw(6) << cp[j];
	}
	cout << endl;
    }
}


/*
* Print coefficients CSV header.
*    Default output to stdout, override with pass-by-reference for testing.
* call:
*    print_coeff_csv_head()		default stdout
*    print_coeff_csv_head( cout )	override ostream
*/
void
yCoeffItr::print_coeff_csv_head(
    ostream&		sout
)
{
    sout << "index,Ym,Xm,c0,c1,c2,c3,c4,c5,c6,c7,"
	    "c8,c9,c10,c11,c12,c13,c14,c15" << endl;
}


/*
* Print coefficients CSV body.
*    Bad pixel entry marked with '!'.
*    #!! Perhaps use a seperate column?
* call:
*    print_coeff_csv_body()		default stdout
*    print_coeff_csv_body( cout )	override ostream
*/
void
yCoeffItr::print_coeff_csv_body(
    ostream&		sout
)
{
    int			*cp;	// coefficient pointer

    sout <<dec;
    sout.fill(' ');

    while ( (cp = this->next_pixel()) )
    {
	sout << PixNum;
	if ( this->has_error() ) {
	    sout << "!";
	}

	sout << "," << PixMarkY;
	sout << "," << PixMarkX;

	for ( int j = 0;  j < 16;  j++ )
	{
	    sout << "," << cp[j];
	}
	sout << endl;
    }
}


/*
* Print coefficients, CSV format.
*    Bad pixel entry marked with '!'.
*    #!! Perhaps use a seperate column?
* call:
*    print_coeff_csv()		default stdout
*    print_coeff_csv( cout )	override ostream
*/
void
yCoeffItr::print_coeff_csv(
    ostream&		sout
)
{
    print_coeff_csv_head( sout );
    print_coeff_csv_body( sout );
}

