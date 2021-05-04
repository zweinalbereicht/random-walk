CPP=g++
CFLAGS= -Ofast
CPPFLAGS= -g -Wall
LDLIBS= -lgsl -lgslcblas

OBJ=main.o DiscreteWalker.o

main: $(OBJ)
	$(CPP) $(CFLAGS) -o main $(OBJ) $(LDLIBS) $(CPPFLAGS)

main.o: main.cpp DiscreteWalker.cpp
	$(CPP) -c main.cpp

DiscreteWalker.o: DiscreteWalker.h DiscreteWalker.cpp
	$(CPP) -c DiscreteWalker.cpp

clean:
	rm -f *.o
