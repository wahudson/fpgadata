#! /usr/bin/tclsh
# 2018-02-12
# 
# Tcl socket server.
# Example from:  http://tmml.sourceforge.net/doc/tcl/socket.html


## Open Qsys master object.
#set masters [get_service_paths master]
#set master [lindex $masters 0]
#open_service master $master
set master "xx"


proc m_write { addr value } {
    upvar master mr

    puts "+ master_write_32 MR $addr $value"
    # master_write_32 $mr $addr $value
}

proc m_ch_freqi { channel phinc } {
    upvar master mr

    set freq [ freq_phi  $phinc ]
    set addr "0x000000${channel}0"

    puts "+ master_write_32 MR $addr $phinc;  f_Hz= $freq"
#    master_write_32 $mr $addr $phinc
}


proc comb_center { iref } {
    set ibase iref
    set idelta  [ phinc_Hz   1000 ]

    m_freq 0 [ expr { $ibase - (3 * $idelta) } ]
    m_freq 1 [ expr { $ibase - (2 * $idelta) } ]
    m_freq 2 [ expr { $ibase - (1 * $idelta) } ]
    m_freq 3 [ expr { $ibase + (0 * $idelta) } ]
    m_freq 4 [ expr { $ibase + (1 * $idelta) } ]
    m_freq 5 [ expr { $ibase + (2 * $idelta) } ]
    m_freq 6 [ expr { $ibase + (3 * $idelta) } ]
    m_freq 7 [ expr { $ibase + (4 * $idelta) } ]
}


proc freq_phi { phi } {
    set F0  50000000.0
    set Len [ expr {1024.0 * 1024.0} ]
    set freq [ expr { int( ( $F0 / $Len ) * $phi ) } ]
    return  $freq
}

proc phinc_Hz { fHz } {
    set F0  50000000.0
    set Len [ expr {1024.0 * 1024.0} ]
    set phi [ expr { int( ( $Len * $fHz / $F0 ) + 0.5 } ) ]
    return  $phi
}


proc ServProc {sockch clientaddr clientport} {
    puts "Connection from:  $clientaddr"

    while { 1 } {

	gets  $sockch  line

	if { [eof $sockch] } {
	    break
	}

	set arg1  ""
	set arg2  ""
	scan $line "%s %s %s"  cmd arg1 arg2

	if {       [string equal $cmd "echo"       ] } {
	    puts "+ $line"

	} elseif { [string equal $cmd "m_write"    ] } {
	    puts "+ m_write"
	    m_write $arg1 $arg2

	} elseif { [string equal $cmd "m_ch_freqi" ] } {
	    puts "+ m_ch_freqi"
	    m_ch_freqi $arg1 $arg2

	} elseif { [string equal $cmd "m_mult_pow" ] } {
	    puts "+ m_mult_pow"
	    m_write 0x50000000 $arg1
	    m_write 0x51000000 $arg2

	} elseif { [string equal $cmd "m_enable"   ] } {
	    puts "+ m_enable"
	    m_write 0x52000000 $arg1

	} elseif { [string equal $cmd "exit"       ] } {
	    puts "+ exit"
	    exit

	} else {
	    puts "Error:  unknown command:  $line"
	}

	if { 1 } {
	    puts "+ send ok"
	    puts  $sockch "ok"
#	    puts  $sockch "ok2"
	    flush $sockch
	}

    }

    close $sockch
}

puts "Socket Server for  master_write_32"

## start the server
    set port 9900

    puts "open socket:  port=$port"

    socket -server ServProc $port
    vwait forever

    # Will listen for another connection.

