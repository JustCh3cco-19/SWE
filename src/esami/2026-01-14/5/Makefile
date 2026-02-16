CXX = g++
CXXFLAGS = -std=c++23 -O3 -Wall -Wextra -pedantic -I..
LIBRARY = ../mocc

all: main

main: main.o parameters.o server.o network.o customer.o supplier.o mocc.o time.o
	$(CXX) $(CXXFLAGS) -o main main.o parameters.o server.o network.o customer.o supplier.o mocc.o time.o

main.o: main.cpp
	$(CXX) $(CXXFLAGS) -c main.cpp

parameters.o: parameters.cpp parameters.h
	$(CXX) $(CXXFLAGS) -c parameters.cpp

server.o: server.cpp server.h
	$(CXX) $(CXXFLAGS) -c server.cpp

network.o: network.cpp network.h server.h parameters.h
	$(CXX) $(CXXFLAGS) -c network.cpp

customer.o: customer.cpp customer.h
	$(CXX) $(CXXFLAGS) -c customer.cpp

supplier.o: supplier.cpp supplier.h
	$(CXX) $(CXXFLAGS) -c supplier.cpp

mocc.o: $(LIBRARY)/mocc.cpp
	$(CXX) $(CXXFLAGS) -c $(LIBRARY)/mocc.cpp

time.o: $(LIBRARY)/time.cpp
	$(CXX) $(CXXFLAGS) -c $(LIBRARY)/time.cpp

clean:
	rm -f *.o main
