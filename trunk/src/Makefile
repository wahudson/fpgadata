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
        yFramDat.h

		# objects not including main()
OBJS       = \
	$(OJ)/Error.o \
	$(OJ)/yOption.o \
	$(OJ)/yFramDat.o

		# compiler flags
	# -std=c++11  needed for std::stoi
CXXFLAGS   = -Wall  -std=c++11


run	: compile
	$(BINDIR)/fpgadata --csv --TESTOP

mkdirs	:
	mkdir -p $(BINDIR)
	mkdir -p $(OJ)

compile	: $(BINDIR)/fpgadata  $(OBJS)

clean: 
	rm -f  $(OJ)/*

clobber:
	rm -f  $(BINDIR)/fpgadata  $(OJ)/*

$(BINDIR)/fpgadata:	$(OJ)/fpgadata.o  $(OBJS)
	g++ -o $@       $(OJ)/fpgadata.o  $(OBJS)


$(OJ)/fpgadata.o:	fpgadata.cpp  $(INCS)
	g++ $(CXXFLAGS) -o $@  -c fpgadata.cpp

$(OJ)/yFramDat.o:	yFramDat.cpp  yFramDat.h
	g++ $(CXXFLAGS) -o $@  -c yFramDat.cpp

$(OJ)/Error.o:		Error.cpp  Error.h
	g++ $(CXXFLAGS) -o $@  -c Error.cpp

$(OJ)/yOption.o:	yOption.cpp  yOption.h  Error.h
	g++ $(CXXFLAGS) -o $@  -c yOption.cpp

