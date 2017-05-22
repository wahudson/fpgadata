// 2017-05-21  William A. Hudson

#ifndef yBuffStat_P
#define yBuffStat_P


//--------------------------------------------------------------------------
// Buffer Statistics class
//--------------------------------------------------------------------------

class yBuffStat {
  private:
  public:

    int			SampleSize;	// limit sample size
    int			NumSets;	// count number of sets

    int			CntTrue;	// number of true values so far
    int			CntCalls;	// number of calls so far

    int			MaxTrue;	// in SampleSize
    int			MinTrue;	// in SampleSize

    int			MaxCalls;	// in SampleSize
    int			MinCalls;	// in SampleSize

  public:
    yBuffStat();
    yBuffStat( int  size );

    inline int		get_sample_size()
    {
	return SampleSize;
    }

    void		reset();

    std::string		text_debug();
    void		show_debug();

    void		cnt_by_call( bool xv );
    std::string		text_stats_by_call();

};


#endif
