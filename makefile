################################################################################
#
# adder_example Makefile
#
# Created by TEJ
# 
#
################################################################################

# intel compiler for serial version:
#CXX = icpc

# intel compiler for parallel version:
#CXX = mpicxx

# GNU compiler serial
CXX = g++

# GNU compiler parallel
#CXX = mpic++

# Linker flags:
LDFLAGS = -L -L/usr/lib -lm
 # -L is directory with libraries, there exists a file libm.sl etc.

# Compiler flags
#CPPFLAGS = -I/usr/include/mpi -Wall -O0 -g -fopenmp
CPPFLAGS = -Wall -O3 -march=native -mtune=native #-ftree-parallelize-loops=4 
  # -Wall all warnings on
  # -O3 Optimization level 3 ( -O0 needed for debugging purposes )
  # ad -g to compile for debugging purposes. Debug code using valgrind
  # -fopenmp enable openMP features
  # -march=native and -mtune=native perform processor-specific optimization

################################################################################

SOURCE  = adder_example.cpp gates.cpp logic.cpp

OBJECTS = ${SOURCE:.cpp=.o}                           

################################################################################

ADDER_O = gates.o logic.o adder_example.o\


################################################################################

.c.o: ${SOURCE}
	${CXX} -c ${CPPFLAGS} $<                             

adder: ${ADDER_O}
	${CXX} -o $@ ${ADDER_O} ${LDFLAGS}


all: adder

clean:                                                
	rm -f *.o

