// 2017-04-24  William A. Hudson

// Raspberry Pi GPIO base class.
//
//--------------------------------------------------------------------------

#include <iostream>
#include <iomanip>

#include <unistd.h>
#include <fcntl.h>	// open()
#include <sys/mman.h>	// mmap()
#include <sys/stat.h>	// stat()

using namespace std;

#include "yRpiGpio.h"


#define BLOCK_SIZE	(4*1024)

#define BCM2708_PERI_BASE	0x3f000000	// Rpi3, (0x20000000 Rpi1)
#define GPIO_BASE		(BCM2708_PERI_BASE + 0x00200000) // GPIO controller

// Register offsets from GPIO_BASE
#define GP_SET0		(0x001c / 4)
#define GP_CLR0		(0x0028 / 4)
#define GP_LEV0		(0x0034 / 4)
 

/*
* Constructor.
* Set up a memory region to access GPIO.
*    Access thru /dev/gpiomem, for normal users belonging to group 'gpio'.
*    If it did not exist, use a fake memory region for testing.
*/
yRpiGpio::yRpiGpio()
{
    int				mem_fd;
    void			*gpio_map;
    static volatile unsigned	fake_block[ BLOCK_SIZE ];
    char			devfile[] = "/dev/gpiomem";
    struct stat			statbuf;

  if ( stat( devfile, &statbuf ) == 0 ) {	// exists
    cerr << "Real GPIO" << endl;

    // open /dev/gpiomem
    if (( mem_fd = open( devfile, O_RDWR|O_SYNC ) ) < 0) {
	cerr << "can't open " << devfile << endl;
	exit( -1 );
    }
 
    // map GPIO into our memory
    gpio_map = mmap(
	NULL,			// Any adddress in our space will do
	BLOCK_SIZE,		// Map length
	PROT_READ|PROT_WRITE,	// Enable reading & writting to mapped memory
	MAP_SHARED,		// Shared with other processes
	mem_fd,			// File to map
	GPIO_BASE		// Offset to GPIO peripheral
    );
 
    close( mem_fd );	// No need to keep mem_fd open after mmap
 
    if ( gpio_map == MAP_FAILED ) {
	//#!! fix mixed io
	printf( "mmap error %p:  %m\n", gpio_map );	//errno also set!
	exit(-1);
    }
    else {
	cerr << "gpio_map= " << gpio_map << endl;
    }
 
    // Always use volatile pointer!
    GpioBase = (volatile unsigned *)gpio_map;
  }
  else {
    cerr << "Fake GPIO" << endl;
    GpioBase = fake_block;
  }

    cerr << "    GpioBase= " << (unsigned *)GpioBase << endl;
}


/*
* Get GPIO Base address.
*/
volatile unsigned*
yRpiGpio::get_GpioBase()
{
    return GpioBase;
}


/*
* Get GPIO read address.
*/
volatile unsigned*
yRpiGpio::get_read_addr()
{
    return GpioBase + GP_LEV0;
}

/*
* Get GPIO set bits address.
*/
volatile unsigned*
yRpiGpio::get_set_addr()
{
    return GpioBase + GP_SET0;
}

/*
* Get GPIO clear bits address.
*/
volatile unsigned*
yRpiGpio::get_clr_addr()
{
    return GpioBase + GP_CLR0;
}

