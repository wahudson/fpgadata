# 2019-04-15  William A. Hudson
#
# Generate man pages.

# Outputs in $(MAN)/

SHELL      = /bin/sh
MAN        = ../man

man:	$(MAN)/man1 \
	$(MAN)/man1/coeff2polar.1 \
	$(MAN)/man1/coeff2polar.txt \
	$(MAN)/man1/coeff2stream.1 \
	$(MAN)/man1/coeff2stream.txt \
	$(MAN)/man1/countpix.1 \
	$(MAN)/man1/countpix.txt \
	$(MAN)/man1/csvrow.1 \
	$(MAN)/man1/csvrow.txt \
	$(MAN)/man1/simage.1 \
	$(MAN)/man1/simage.txt

clean:


clobber:
	rm -f  $(MAN)/man1/*

$(MAN)/man1:
	mkdir -p  $(MAN)/man1


$(MAN)/man1/%.1:		%
	pod2man -s 1 --center='fpgadata'  -n $<  $<  $@

$(MAN)/man1/%.txt:		%
	pod2text -i7 -s  $<  $@

