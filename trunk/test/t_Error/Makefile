# 2017-05-19  William A. Hudson
#
# Compile and run this test.
# Use OBJS, but not build them.  Outputs in ./ and tmp/

SHELL      = /bin/sh
OJ         = ../../obj
IC         = ../../src

		# all include files for test program dependency
INCS       = \
	../src/utLib1.h \
        $(IC)/Error.h

		# objects not including main()
OBJS       = \
	../obj/utLib1.o \
	$(OJ)/Error.o

		# compiler flags
CXXFLAGS   = -Wall -std=c++11  -I ../src


test:  tmp  test.exe
	./test.exe

tmp:
	mkdir tmp

clean:
	rm -f  test.exe
	rm -f  tmp/*

test.exe	: test.cpp  $(OBJS)  $(INCS)
	g++ $(CXXFLAGS) -I $(IC) -o $@  test.cpp  $(OBJS)

