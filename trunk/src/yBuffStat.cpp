// 2017-05-21  William A. Hudson

// Buffer Statistics base class.
//
//--------------------------------------------------------------------------

#include <iostream>
#include <iomanip>
#include <sstream>	// std::ostringstream

#include "Error.h"
#include "yBuffStat.h"

using namespace std;


/*
* Constructor.
*/
yBuffStat::yBuffStat()
{
    this->reset( 100 );
}


/*
* Constructor.
*/
yBuffStat::yBuffStat(
    int		size
)
{
    this->reset( size );
}


/*
* Reset object and set new SampleSize.
*    Min/Max default set outside of range.  This works, but not the best
*    indication of uninitialized.
* call:
*    self.reset( 100 )
*/
void
yBuffStat::reset(
    int		size
)
{
    SampleSize   = size;
    NumSets      = 0;
    CntTrue      = 0;
    CntCalls     = 0;
    MaxTrue      = -1;
    MinTrue      = size + 1;
    MaxCalls     = -1;
    MinCalls     = size + 1;
}


/*
* Get debug text.
*    Multi-line output.  No trailing new-line.
*/
std::string
yBuffStat::text_debug()
{
    std::ostringstream		css;             // constructor

    css << "SampleSize= " << SampleSize
	<< "  NumSets= "  << NumSets
	<< "  CntTrue= "  << CntTrue
	<< "  CntCalls= " << CntCalls
	<<endl;
    css << "        MaxTrue= "  << MaxTrue
	<< "  MinTrue= "  << MinTrue ;

    return css.str();
}


/*
* Show debug output.
*    Single-line output.
* call:
*    self.show_debug()
*/
void
yBuffStat::show_debug()
{
    cout<< "SampleSize= " << SampleSize
	<< "  NumSets= "  << NumSets
	<< "  CntTrue= "  << CntTrue
	<< "  CntCalls= " << CntCalls
	<< "  MaxTrue= "  << MaxTrue
	<< "  MinTrue= "  << MinTrue
	<< endl;
}


/*
* Count events by number of calls.
*    SampleSize is the number of calls in a sample.
* call:
*    self.cnt_by_call( xv )
*/
void
yBuffStat::cnt_by_call(
    bool	xv
)
{
    //#!! skip initial toggles to let buffer empty

    // accumulate sample
    CntCalls++;
    if ( xv ) {
	CntTrue++;
    }

    // log max and min
    if ( CntCalls >= SampleSize ) {
	if ( MaxTrue < CntTrue ) {
	     MaxTrue = CntTrue;
	}
	if ( MinTrue > CntTrue ) {
	     MinTrue = CntTrue;
	}

	NumSets++;
	CntTrue  = 0;
	CntCalls = 0;
    }
}


/*
* Text statistics by number of calls.
*    SampleSize is the number of calls in a sample.
*    Should be accumulated by cnt_by_call().
* call:
*    cout << bx.text_stats_by_call() << endl;
*/
std::string
yBuffStat::text_stats_by_call()
{
    std::ostringstream	css;             // constructor
    int			max_true = -1;
    int			min_true = -1;
    int			pct_max  = -1;
    int			pct_min  = -1;

    if ( NumSets > 1 ) {	// valid min/max
	max_true = MaxTrue;
	min_true = MinTrue;
	pct_max = 100 * MaxTrue / SampleSize;
	pct_min = 100 * MinTrue / SampleSize;
    }

    css << "Stats by call:  SampleSize= " << SampleSize
	<< "  NumSets= " << NumSets <<endl;

    css << "    MaxTrue= " <<setw(4) << max_true 
			   <<setw(4) << pct_max << "%" <<endl;

    css << "    MinTrue= " <<setw(4) << min_true
			   <<setw(4) << pct_min << "%" <<endl;

    return css.str();
}

