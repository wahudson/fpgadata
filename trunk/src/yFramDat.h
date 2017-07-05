// 2017-04-22  William A. Hudson

#ifndef yFramDat_P
#define yFramDat_P

//--------------------------------------------------------------------------
// Frame Data class
//--------------------------------------------------------------------------

class yFramDat {
  private:
    uint16_t		*data;		// pointer to array
    size_t		size;		// size of data array
    size_t		len;		// current length of data

  public:
    std::string		HeadLine;	// load/save headline

  public:
    yFramDat();
    yFramDat( size_t nsize );
   ~yFramDat();

    inline int		get_length()	// Get length of data array.
    {
	return len;
    }

    inline void		clear()		// Reset length to zero.
    {
	len = 0;
    }

    inline uint16_t*	data_pointer_begin()	// first element
    {
	return  data;
    }

    inline uint16_t*	data_pointer_end()	// element past the end
    {
	return  (data + len);
    }

    inline uint16_t*	get_dp_minus4()
    {
	return  ( (len > 4) ? (data + len - 4) : data );
    }

    void		show_debug();
    int			nlimit( unsigned int  ntran );
    bool		push_dat( uint16_t  value );

    void		load_hex( const char  *infile );
    void		save_hex( const char  *outfile );

    void		print_coeff16_tab();
    void		print_coeff16_csv();
    void		print_coeff_int16B_tab();
    void		print_coeff_int16B_csv();
    void		print_coeff_nibbleB_tab();
    void		print_coeff_nibbleB_csv();
    void		print_hex_dump();
    void		print_index_data();
    void		print_delta_data();
    void		print_flag_data();
    void		print_flag_hex();
};


#endif
