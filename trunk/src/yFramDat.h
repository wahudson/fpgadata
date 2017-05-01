
#ifndef yFramDat_P
#define yFramDat_P


//--------------------------------------------------------------------------
// Frame Data class
//--------------------------------------------------------------------------
//!! Public access to *data pointer is dangerous should it get changed!
// Trying to get started for now.

class yFramDat {
  private:
  public:
//    unsigned char	*data;		// pointer to array
    uint16_t		*data;		// pointer to array
    size_t		size;		// size of data array
    size_t		len;		// current length of data

  public:
    yFramDat();
    yFramDat( size_t nsize );
   ~yFramDat();

    void		show_debug();
    int			get_length();

    inline void		clear()
    {
	len = 0;
    }

    int			nlimit( unsigned int  ntran );
    bool		push_dat( uint16_t  value );
    void		print_coeff16_tab();
    void		print_coeff16_csv();
    void		print_hex_dump();
    void		print_index_data();
    void		print_delta_data();
};


#endif
