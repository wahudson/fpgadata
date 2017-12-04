
#ifndef Error_P
#define Error_P

//--------------------------------------------------------------------------
// Error class
//--------------------------------------------------------------------------

class Error {
  private:
    static int			Error_cnt;
    static std::ostream		*cErr;

  public:	// Class Methods
    static void			Init_ostream( std::ostream* erx );
    static int			has_err();
    static std::ostream&	msg();
    static std::ostream&	msg( const char* text );

  public:
    static int		err();
    static void		err( const char* );
    static void		err( const char*,  const char* );
    static void		err( const char*,  const char*,  const char* );
    static void		err( const char*,  const char*,  const char*,  const char* );

};


#endif

