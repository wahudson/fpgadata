// 2017-05-29  William A. Hudson

#ifndef yCoeffItr_P
#define yCoeffItr_P

//--------------------------------------------------------------------------
// Coefficient Data Iterator base class
//--------------------------------------------------------------------------

class yCoeffItr {
  protected:
    yFramDat		*Fdata;		// frame data object
    uint16_t		*DaPtr;		// current pointer in Fdata[] array

  public:
				// Single Pixel data
//  int			NumCoef;	// number of coefficients
    int			PixCoef[16];	// array of coefficients
    int			PixNum;		// pixel number
    bool		PixErr;		// pixel has an error

    bool		PixMarkX;	// X scan mark
    bool		PixMarkY;	// Y scan mark

  public:
    yCoeffItr( yFramDat *fdp );

    virtual void	restart();
    virtual int		*next_pixel();
    virtual void	print_coeff_tab();

    virtual void	print_coeff_csv_head( ostream& sout = cout );
    virtual void	print_coeff_csv_body( ostream& sout = cout );
    virtual void	print_coeff_csv(      ostream& sout = cout );

    inline bool		has_error()
    {
	return PixErr;
    }

};


#endif

