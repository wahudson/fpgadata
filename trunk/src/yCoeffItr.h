// 2017-05-29  William A. Hudson

#ifndef yCoeffItr_P
#define yCoeffItr_P

//--------------------------------------------------------------------------
// Coefficient Data Iterator class
//--------------------------------------------------------------------------

class yCoeffItr {
  private:
    yFramDat		*Fdata;		// frame data object
    unsigned int	DatAddr;	// current address in Fdata[] array

				// Single Pixel data
//  int			NumCoef;	// number of coefficients
    int			PixCoef[16];	// array of coefficients
    int			PixNum;		// pixel number
    bool		PixErr;		// pixel has an error


  public:

  public:
    yCoeffItr( yFramDat *fdp );

    int			*next_pixel();
    bool		get_pixel_nibbles( int  *addr );
    void		print_coeff_tab();

    inline bool		get_error()
    {
	return PixErr;
    }

};


#endif

