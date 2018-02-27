#! /usr/bin/tclsh
# 2018-02-12
# 
# Tcl socket server.
# Example from:  http://tmml.sourceforge.net/doc/tcl/socket.html

proc ServProc {channel clientaddr clientport} {
    puts "Connection from:  $clientaddr"

    while { 1 } {
	if { 0 } {
	    puts  -nonewline $channel "> "
	    flush $channel
	}

	puts "receive line"
	gets  $channel  line

	if { [eof $channel] } {
	    break
	}

	set addr  ""
	set value ""

#	puts  "line= $line"
	scan $line "%s %s %s"  cmd addr value

	if {       [string equal $cmd "exit" ] } {
	    puts "+ exit"
	    exit

	} else {
	    puts "+ $line"
	}

	if { 1 } {
	    puts "send ok"
	    puts  $channel "ok >"
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

