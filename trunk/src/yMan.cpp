// 2017-10-26  William A. Hudson

// Manpage Display class.
//--------------------------------------------------------------------------

#include <sys/stat.h>

#include <unistd.h>
#include <iostream>
#include <sstream>	// std::ostringstream
#include <string>
#include <stdexcept>

#include <string.h>	// strerror()
#include <errno.h>	// errno

using namespace std;

#include "yMan.h"


/*
* Constructor.
*/
yMan::yMan()
{
}


/*
* Show man page for this executing program.
*     Manpage formatted from perl pod file found beside executing program.
*     Uses /proc/self/exe to find the program, and append ".pod" suffix.
* throw:
*     std::runtime_error	Error message.
*/
void
yMan::show_manpage(
    const char*		progname	// program name on manpage
)
{
    const size_t	bufsiz = 1023;		// an arbitrary limitation
    char		buff[ bufsiz + 1 ];	// readlink buffer
    ssize_t		rlen;			// readlink length

// Find this executing program file.
    rlen = readlink( "/proc/self/exe", buff, bufsiz );

    if ( rlen == -1 ) {
	int		errv = errno;
	std::string     ss ( "readlink( /proc/self/exe ) failed:  " );
	ss += strerror( errv );
	throw std::runtime_error ( ss );
    }

    if ( rlen >= (ssize_t) bufsiz ) {
	std::string     ss ( "symlink too long:  /proc/self/exe" );
	throw std::runtime_error ( ss );
    }

    buff[rlen] = '\0';

// Form the pod file name.
    string		podfile  ( buff );

    podfile.append( ".pod" );

    // cerr << "podfile= " << podfile << endl;

// Check pod file existance.
    struct stat		stbuf;
    if ( stat( podfile.c_str(), &stbuf ) == -1 ) {
	std::ostringstream	css;
	css << "pod file not found:  " << podfile << endl;
	css << "    It should be a symlink beside this executable." << endl;
	throw std::runtime_error ( css.str() );
    }

// Format the pod file for manpage display.
    string		cmd;
    cmd += "pod2man -s 1 -n ";
    cmd += progname;
    cmd += "  --center='User Contrib' ";
    cmd += podfile;
    cmd += " | nroff -man | less";

    // cerr << "cmd= " << cmd << endl;

    int			rv;
    rv = system( cmd.c_str() );

    if ( rv == -1 ) {
	std::string     ss ( "system( pod2man .. ) failed" );
	throw std::runtime_error ( ss );
    }
}

