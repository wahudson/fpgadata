// 2018-03-24  William A. Hudson

#ifndef gLfsr_P
#define gLfsr_P


//--------------------------------------------------------------------------
// Galois LFSR (Linear Feedback Shift Register) class
//--------------------------------------------------------------------------

class gLfsr {
  private:

    uint32_t		TapPoly;	// tap polynomial, sets length
    uint32_t		LfsR;		// shift register
    uint32_t		StartSeed;	// initial seed

  public:

    int			ShiftCnt;	// number of shifts


  public:
    gLfsr();
    gLfsr( uint32_t  tap_poly );

    inline uint32_t		get_StartSeed()
    {
	return StartSeed;
    }

    void		reset();
    uint32_t		next_state();

};


#endif

