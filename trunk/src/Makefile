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
        yMan.h \
        yRpiGpio.h \
        yBuffStat.h \
        yFramDat.h \
        yCoeffItr.h

		# objects not including main()
OBJS       = \
	$(OJ)/Error.o \
	$(OJ)/yOption.o \
	$(OJ)/yMan.o \
	$(OJ)/yRpiGpio.o \
	$(OJ)/yBuffStat.o \
	$(OJ)/yFramDat.o \
	$(OJ)/yCoeffItr.o

		# compiler flags
	# -std=c++11  needed for std::stoi
CXXFLAGS   = -Wall  -std=c++11


run	: compile
##	$(BINDIR)/fpgadata --csv --TESTOP
	$(BINDIR)/rpixel --csv --TESTOP

mkdirs	: $(OJ)  $(BINDIR)

compile	: $(OJ)  $(BINDIR)  $(BINDIR)/fpgadata  $(BINDIR)/rpixel

clean: 
	rm -f  $(OJ)/*

clobber:
	rm -f  $(BINDIR)/fpgadata  $(BINDIR)/rpixel  $(OJ)/*

$(BINDIR):
	mkdir -p $(BINDIR)

$(OJ):
	mkdir -p $(OJ)


$(BINDIR)/fpgadata:	$(OJ)/fpgadata.o  $(OBJS)
	g++ -o $@       $(OJ)/fpgadata.o  $(OBJS)

$(BINDIR)/rpixel:	$(OJ)/rpixel.o  $(OBJS)
	g++ -o $@       $(OJ)/rpixel.o  $(OBJS)


$(OJ)/fpgadata.o:	fpgadata.cpp  $(INCS)
	g++ $(CXXFLAGS) -o $@  -c fpgadata.cpp

$(OJ)/rpixel.o:		rpixel.cpp  $(INCS)
	g++ $(CXXFLAGS) -o $@  -c rpixel.cpp

$(OJ)/yRpiGpio.o:	yRpiGpio.cpp  yRpiGpio.h
	g++ $(CXXFLAGS) -o $@  -c yRpiGpio.cpp

$(OJ)/yBuffStat.o:	yBuffStat.cpp  yBuffStat.h
	g++ $(CXXFLAGS) -o $@  -c yBuffStat.cpp

$(OJ)/yFramDat.o:	yFramDat.cpp  yFramDat.h
	g++ $(CXXFLAGS) -o $@  -c yFramDat.cpp

$(OJ)/yCoeffItr.o:	yCoeffItr.cpp  yCoeffItr.h
	g++ $(CXXFLAGS) -o $@  -c yCoeffItr.cpp

$(OJ)/yCoeffItr2.o:	yCoeffItr2.cpp  yCoeffItr2.h  yCoeffItr.h
	g++ $(CXXFLAGS) -o $@  -c yCoeffItr2.cpp

$(OJ)/Error.o:		Error.cpp  Error.h
	g++ $(CXXFLAGS) -o $@  -c Error.cpp

$(OJ)/yOption.o:	yOption.cpp  yOption.h  Error.h
	g++ $(CXXFLAGS) -o $@  -c yOption.cpp

$(OJ)/yMan.o:		yMan.cpp  yMan.h
	g++ $(CXXFLAGS) -o $@  -c yMan.cpp

