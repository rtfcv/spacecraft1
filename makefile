ProjectName=spaceCraft1

#compiler settings
CXX=g++

#change -O3 or -Ofast to -O2 if something goes wrong
CXXFLAGS += -fopenmp -static -lstdc++ -Ofast -march=native -pipe

#include files below
CXXFLAGS += -I. -I C:\msys64\mingw64\include\eigen3

#descrive target manually
#former depends on latter
targets1=task1_main.o task1.o task1_simulate.o save.o
targets2=task2_main.o task2.o task2_simulate.o task1.o task1_simulate.o save.o

${ProjectName}: ${targets1} ${targets2}
	g++ -static -o task1 ${targets1};
	g++ -static -o task2 ${targets2};

#rules for your targets

task1_main.o: task1.hpp save.hpp

task1.o: task1.hpp

task1_simulate.o: task1.hpp

save.o: save.hpp

task2_main.o: task1.hpp task2.hpp save.hpp

task2.o: task1.hpp task2.hpp save.hpp

task2_simulate.o: task1.hpp task2.hpp
