#! /usr/bin/tclsh
# 2018-02-12
# eight lockins frequency comb for FPGA lock-ins
# (Wilson lab, ECE Dept, Colorado State University)
# 

## Open Qsys master object.
#set masters [get_service_paths master]
#set master [lindex $masters 0]
#open_service master $master

set master "xx"

proc m_write { addr value } {
    upvar master mr

    puts "+ master_write_32 MR $addr $value"
#    master_write_32 $mr $addr $value
}

proc m_freq { addr phinc } {
    upvar master mr

    set freq [ freq_phi  $phinc ]

    puts "+ master_write_32 MR $addr $phinc;  f_Hz= $freq"
#    master_write_32 $mr $addr $phinc
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


set Ibase   [ phinc_Hz 250000 ]
set Idelta  [ phinc_Hz   1000 ]

set fbase   [ freq_phi $Ibase  ]
set fdelta  [ freq_phi $Idelta ]

puts "Comb:  Ibase= $Ibase ($fbase Hz)  Idelta= $Idelta ($fdelta Hz)"

## frequencies of the 8 lockins (20-bit phinc)

m_freq 0x00000000 [ expr { $Ibase - (3 * $Idelta) } ]
m_freq 0x00000010 [ expr { $Ibase - (2 * $Idelta) } ]
m_freq 0x00000020 [ expr { $Ibase - (1 * $Idelta) } ]
m_freq 0x00000030 [ expr { $Ibase + (0 * $Idelta) } ]
m_freq 0x00000040 [ expr { $Ibase + (1 * $Idelta) } ]
m_freq 0x00000050 [ expr { $Ibase + (2 * $Idelta) } ]
m_freq 0x00000060 [ expr { $Ibase + (3 * $Idelta) } ]
m_freq 0x00000070 [ expr { $Ibase + (4 * $Idelta) } ]

## phase offsets of the 8 lockins (20-bit phinc)

m_write 0x10000000 0
m_write 0x10000010 0
m_write 0x10000020 0
m_write 0x10000030 0
m_write 0x10000040 0
m_write 0x10000050 0
m_write 0x10000060 0
m_write 0x10000070 0


## post cic bit slice selection
# example:  when selected 0, MSB downto (MSB - 16) output bits from the
# cic filter is selected and fed to the lockin outputs
# when selected 1, MSB-1 downto (MSB - 16) - 1 output bits from the cic
# filter is selected and fed to the lockin outputs
# increasing this value performs the operation of division by powers of 2

m_write 0x20000000 6


## Multiplier on input to DAC:  Mult = A / (2^B)
# Numerator A (range 0 to 255)

    m_write 0x50000000 31

# Denominator B power of 2

    m_write 0x51000000 6


## lockin channel enable bits [7:0]
# which lockins are turned on or off (MSB => lockin 8, LSB => lockin 1)
# example:
#     255 decimal = 11111111 binary, all the 8 lockins are active.
#      15 decimal = 00001111 binary, lockins 4..1 are active
#      17 decimal = 00010001 binary, lockins 1 and 5 are active

m_write 0x52000000 255

