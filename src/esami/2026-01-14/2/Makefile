CXX = g++
CXXFLAGS = -std=c++23 -O3 -Wall -Wextra -pedantic -I..
LIBRARY = ../mocc

all: main

main: main.o parameters.o uav.o network.o mocc.o time.o
	$(CXX) $(CXXFLAGS) -o main main.o parameters.o uav.o network.o mocc.o time.o

main.o: main.cpp
	$(CXX) $(CXXFLAGS) -c main.cpp

parameters.o: parameters.cpp parameters.h
	$(CXX) $(CXXFLAGS) -c parameters.cpp

uav.o: uav.cpp uav.h network.h
	$(CXX) $(CXXFLAGS) -c uav.cpp

network.o: network.cpp network.h uav.h
	$(CXX) $(CXXFLAGS) -c network.cpp

mocc.o: $(LIBRARY)/mocc.cpp
	$(CXX) $(CXXFLAGS) -c $(LIBRARY)/mocc.cpp

time.o: $(LIBRARY)/time.cpp
	$(CXX) $(CXXFLAGS) -c $(LIBRARY)/time.cpp

clean:
	rm -f *.o main
