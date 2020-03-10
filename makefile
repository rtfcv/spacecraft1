ProjectName=spaceCraft1

#compiler settings
CXX=g++
#change -O3 or -Ofast to -O2 if something goes wrong
CXXFLAGS = -fopenmp -static -lstdc++ -Ofast -march=native -pipe

#include files below
CXXFLAGS+= -I.

#descrive target manually
#former depends on latter
targets1=task1_main.o task1.o plot.o
targets2=task2_main.o taks1.o task2.o plot.o

${ProjectName}: ${targets}
	g++ -static -o task1 ${targets1}
	g++ -static -o task2 ${targets2}

#rules for your targets
main.o:headeronly.h header.h

task1_main.o: task1.h plot.h

task1.o: task1.h

plot.o: plot.h

task2_main.o: task1.h task2.h plot.h

task2.o: task1.h task2.h
