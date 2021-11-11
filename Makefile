SHELL = /bin/sh
NAME = all
MAKEFILE = Makefile

ROOT_FLAG = `root-config --cflags --libs`


LIBRARIES  := $(LIBRARIES) -L$(ROOTSYS)/lib

INCLUDES := $(INCLUDES) -I. -I$(ROOTSYS)/include

#%.o : %.cc
#	g++ $(ROOT_FLAG) $(RAT_LIBS) $(INCLUDES) $(LIBRARIES) -c $*.cc

OBJS := likelihood.o likelihood_classify.o pdf_gen.o merge_PDFs.o

all: learn

learn: $(OBJS) learn.cc
	$(CXX) -g -o learn $(CXXFLAGS) $(LDFLAGS) learn.cc $(INCLUDES) $(OBJS) $(LIBRARIES) $(ROOT_FLAG)
	g++ energy.cc -o energy $(ROOT_FLAG)
	g++ energy2.cc -o energy2 $(ROOT_FLAG)
	g++ n100.cc -o n100 $(ROOT_FLAG)
	$(shell ./configure)

%.o : %.cc
	g++ $(ROOT_FLAG) $(INCLUDES) $(LIBRARIES) -c $*.cc
#################### CLEANING


clean:
	$(RM) env.sh
	$(RM) *.o *~ core 
	$(RM) learn
	$(RM) energy
	$(RM) energy2
	$(RM) n100