SHELL = /bin/sh
NAME = all
MAKEFILE = Makefile

ROOT_FLAG = `root-config --cflags --libs`


LIBRARIES  := $(LIBRARIES) -L$(ROOTSYS)/lib

INCLUDES := $(INCLUDES) -I. -I$(ROOTSYS)/include

#%.o : %.cc
#	g++ $(ROOT_FLAG) $(RAT_LIBS) $(INCLUDES) $(LIBRARIES) -c $*.cc

OBJS := likelihood.o likelihood_classify.o pdf_gen.o merge_PDFs.o

all: lance

lance: $(OBJS) lance.cc
	$(CXX) -g -o lance $(CXXFLAGS) $(LDFLAGS) lance.cc $(INCLUDES) $(OBJS) $(LIBRARIES) $(ROOT_FLAG)

%.o : %.cc
	g++ $(ROOT_FLAG) $(INCLUDES) $(LIBRARIES) -c $*.cc
#################### CLEANING


clean:
	$(RM) *.o *~ core 
	$(RM) lance
