
#ifndef yRpiGpio_P
#define yRpiGpio_P

//--------------------------------------------------------------------------
// Rpi GPIO class
//--------------------------------------------------------------------------

class yRpiGpio {
  private:
    volatile unsigned	*GpioBase;	// IO base address

  public:
    yRpiGpio();

    volatile unsigned*	get_GpioBase();

    volatile unsigned*	get_read_addr();
    volatile unsigned*	get_set_addr();
    volatile unsigned*	get_clr_addr();
};


#endif

