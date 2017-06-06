// 2017-05-29  William A. Hudson

// Coefficient Data Iterator class.
//    Is a friend class of yFramDat.
//    Intended for extracting coefficients from the raw gpio data array.
//
//--------------------------------------------------------------------------

#include <iostream>
#include <iomanip>

using namespace std;

#include "Error.h"
#include "yFramDat.h"	// frame data
#include "yCoeffItr.h"


/*
* Constructor.
*/
yCoeffItr::yCoeffItr(
    yFramDat		*fdp
)
{
    Fdata   = fdp;
    DatAddr = 0;
    PixNum  = -1;
    PixErr  = 0;

    for ( int jj = 0;  jj < 16;  jj++ )	// each coefficient
    {
	PixCoef[jj] = 0;
    }
}


/*
* Get next pixel set of coefficients from Big-endian 4-bit nibbles.
*    Big-endian data.
*    Assume there are no NoData entries.
*    Return only complete pixel data sets.
*    Note coeff size to pack as a signed 16-bit value.
* call:
*    self.next_pixel()
* return:
*    ()  = pointer to coefficient arry, NULL at end of data
*/
int*
yCoeffItr::next_pixel()
{
    unsigned int	ii;
    int			coeff_err = -999999;

    ii = DatAddr;

    if ( (ii + (16*4)) > Fdata->len ) {
	return NULL;
    }
    //#!! redundant check

    for ( int jj = 0;  jj < 16;  jj++ )	// each coefficient
    {
	int		cnum;		// coeff number in data array
	int16_t		coeff   = 0;	// coeff value
	int		nib_err = 0;	// nibble error

	if ( (ii + 4) > Fdata->len ) {	// at limit
	    PixCoef[jj] = coeff_err;	// flag value
	    PixErr      = 1;
	    continue;
	}
	//#!! redundant check

	for ( int k = 0;  k < 4;  k++, ii++ )	// each nibble
	{
	    coeff = (coeff << 4) | (Fdata->data[ii] & 0xf);
	    cnum  = (Fdata->data[ii] >> 4) & 0xf;
	    if ( cnum != jj ) {
		nib_err = 1;
	    }
	}

	if ( nib_err ) {
	    if ( ! PixErr ) {
		Error::err( "misaligned coeff nibble at:" );
		cerr << "    index= " << ii << endl;
	    }
	    PixErr = 1;
	    PixCoef[jj] = coeff_err;	// flag value
	}
	else {
	    PixCoef[jj] = coeff;
	}
    }

    PixNum++;
    DatAddr = ii;
    return  PixCoef;	// array
}


/*
* Print coefficients, tabular format.
*    #!! Perhaps a little strange to put this in the iterator.
* call:
*    print_coeff_tab()
*/
void
yCoeffItr::print_coeff_tab()
{
    int			*cp;	// coefficient pointer

    cout << " index     c0     c1     c2     c3     c4     c5     c6     c7"
                  "     c8     c9    c10    c11    c12    c13    c14    c15" << endl;
    cout << "------ ------ ------ ------ ------ ------ ------ ------ ------"
                  " ------ ------ ------ ------ ------ ------ ------ ------" << endl;
    cout <<dec;
    cout.fill(' ');

    while ( (cp = this->next_pixel()) )
    {
	cout <<setw(6) << PixNum;
	if ( this->get_error() ) {
	    cout << "!";
	}
	else {
	    cout << " ";
	}

	for ( int j = 0;  j < 16;  j++ )
	{
	    cout << " " <<setw(6) << cp[j];
	}
	cout << endl;
    }
    cout << dec;
}

