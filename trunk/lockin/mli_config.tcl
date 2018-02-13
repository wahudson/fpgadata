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

    # master_write_32 $mr $addr $value
    puts "master_write_32 MR $addr $value"
}

puts "hello world"

## frequencies of the 8 lockins

m_write 0x00000000 21691
m_write 0x00000010 21953
m_write 0x00000020 22215
m_write 0x00000030 22477
m_write 0x00000040 21429
m_write 0x00000050 21167
m_write 0x00000060 20905
m_write 0x00000070 20643

## phase offsets of the 8 lockins

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

m_write 0x20000000 0

# integer multiplier of the DAC output (range 0 to 255)

m_write 0x50000000 31

## bit slice selector (division by a factor of 2)
# Note:  the integer multiplier and bit slice selector need to be adjusted
# together to obtain the suitable amount of output dynamic range from the DAC

m_write 0x51000000 6


## lockin channel enable
# which lockins are turned on or off (MSB => lockin 8, LSB => lockin 1)
# example: putting in 255 decimal = 11111111 binary, means all the 8 lockins
# are active
# putting in 15 decimal = 00001111 binary, means lockins 1 to 4 out of the 8 lockins are active
# putting in 17 decimal = 00010001 binary, means lockins 1 and 5 are active

m_write 0x52000000 255

