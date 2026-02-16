CXX = g++
CXXFLAGS = -std=c++23 -O3 -Wall -Wextra -pedantic -I..

LIBRARY = ../mocc
MOCC_SRCS = $(LIBRARY)/mocc.cpp $(LIBRARY)/time.cpp
MOCC_OBJS = mocc.o time.o

OBJS = main.o parameters.o uav.o network.o $(MOCC_OBJS)

all: main

main: $(OBJS)
	$(CXX) $(CXXFLAGS) -o main $(OBJS)

main.o: main.cpp network.h parameters.h
	$(CXX) $(CXXFLAGS) -c main.cpp -o main.o

parameters.o: parameters.cpp parameters.h
	$(CXX) $(CXXFLAGS) -c parameters.cpp -o parameters.o

uav.o: uav.cpp uav.h
	$(CXX) $(CXXFLAGS) -c uav.cpp -o uav.o

network.o: network.cpp network.h uav.h parameters.h
	$(CXX) $(CXXFLAGS) -c network.cpp -o network.o

mocc.o: $(LIBRARY)/mocc.cpp $(LIBRARY)/mocc.hpp
	$(CXX) $(CXXFLAGS) -c $(LIBRARY)/mocc.cpp -o mocc.o

time.o: $(LIBRARY)/time.cpp $(LIBRARY)/time.hpp
	$(CXX) $(CXXFLAGS) -c $(LIBRARY)/time.cpp -o time.o

clean:
	rm -f $(OBJS) main
