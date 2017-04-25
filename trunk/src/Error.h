
#ifndef Error_P
#define Error_P


//--------------------------------------------------------------------------
// Error class
//--------------------------------------------------------------------------

class Error {
  private:
    static int		Error_cnt;
    int			count;
  public:
    static int		err();
    static void		err( const char* );
    static void		err( const char*,  const char* );
    static void		err( const char*,  const char*,  const char* );
    static void		err( const char*,  const char*,  const char*,  const char* );

    int			msg( char* );
};


#endif
