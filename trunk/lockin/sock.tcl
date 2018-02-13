#! /usr/bin/tclsh
# 2018-02-12
# 
# Tcl socket server.
# Example from:  http://tmml.sourceforge.net/doc/tcl/socket.html


set master "xx"

proc m_write { addr value } {
    upvar master mr

    # master_write_32 $mr $addr $value
    puts "+ master_write_32 MR $addr $value"
}


proc ServProc {channel clientaddr clientport} {
    puts "Connection from:  $clientaddr"
#    puts "Connection:  $clientaddr registered"

    while { 1 } {
	if { 0 } {
	    puts  -nonewline $channel "> "
	    flush $channel
	}

	gets  $channel  line

	if { [eof $channel] } {
	    break
	}

	set addr  ""
	set value ""

#	puts  "line= $line"
	scan $line "%s %s %d"  cmd addr value

	if {       [string equal $cmd "mw"   ] } {
	    if { [string length $value] == 0 } {
		puts "Error:  missing value:  $line"
		continue
	    }
#	    puts  "do:  $cmd"
	    m_write "$addr" "$value"

	} elseif { [string equal $cmd "exit" ] } {
	    puts "+ exit"
	    exit

	} else {
	    puts "Error:  unknown command:  $line"
	    continue
	}

	if { 1 } {
	    puts "+ send ok"
	    puts  $channel "ok"
	    flush $channel
	}

    }

    close $channel
}

puts "Socket Server for  master_write_32"

## start the server
    set port 9900

    puts "open socket:  port=$port"

    socket -server ServProc $port
    vwait forever

    # Will listen for another connection.

