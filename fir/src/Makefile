# 2017-04-22  William A. Hudson
#
# Compile and run the main program.

# Outputs in $(BINDIR)/ and $(OJ)/

SHELL      = /bin/sh
BINDIR     = ../bin
OJ         = ../obj

		# all include files for main program dependency
INCS       = \
        Error.h \
        yOption.h \
        gLfsr.h

		# objects not including main()
OBJS       = \
	$(OJ)/Error.o \
	$(OJ)/yOption.o \
	$(OJ)/gLfsr.o

		# compiler flags
	# -std=c++11  needed for std::stoi
CXXFLAGS   = -Wall  -std=c++11


run	: compile
	$(BINDIR)/lfsr --TESTOP

mkdirs	: $(OJ)  $(BINDIR)

compile	: $(OJ)  $(BINDIR)  $(BINDIR)/lfsr

clean: 
	rm -f  $(OJ)/*

clobber:
	rm -f  $(BINDIR)/lfsr  $(OJ)/*

man:
	podchecker lfsr.pod


$(BINDIR):
	mkdir -p $(BINDIR)

$(OJ):
	mkdir -p $(OJ)


$(BINDIR)/lfsr:		$(OJ)/lfsr.o  $(OBJS)
	g++ -o $@       $(OJ)/lfsr.o  $(OBJS)


$(OJ)/lfsr.o:		lfsr.cpp  $(INCS)
	g++ $(CXXFLAGS) -o $@  -c lfsr.cpp

$(OJ)/gLfsr.o:		gLfsr.cpp
	g++ $(CXXFLAGS) -o $@  -c gLfsr.cpp

$(OJ)/Error.o:		Error.cpp  Error.h
	g++ $(CXXFLAGS) -o $@  -c Error.cpp

$(OJ)/yOption.o:	yOption.cpp  yOption.h  Error.h
	g++ $(CXXFLAGS) -o $@  -c yOption.cpp

