CXX = g++
CXXFLAGS = -std=c++23 -O3 -Wall -Wextra -pedantic -I..

LIBRARY = ../mocc
MOCC_SRCS = $(LIBRARY)/mocc.cpp $(LIBRARY)/time.cpp
MOCC_OBJS = mocc.o time.o

OBJS = main.o parameters.o server.o customer.o supplier.o ecommercesystem.o $(MOCC_OBJS)

all: main

main: $(OBJS)
	$(CXX) $(CXXFLAGS) -o main $(OBJS)

main.o: main.cpp parameters.h ecommercesystem.h customer.h supplier.h
	$(CXX) $(CXXFLAGS) -c main.cpp -o main.o

parameters.o: parameters.cpp parameters.h
	$(CXX) $(CXXFLAGS) -c parameters.cpp -o parameters.o

server.o: server.cpp server.h
	$(CXX) $(CXXFLAGS) -c server.cpp -o server.o

customer.o: customer.cpp customer.h ecommercesystem.h
	$(CXX) $(CXXFLAGS) -c customer.cpp -o customer.o

supplier.o: supplier.cpp supplier.h ecommercesystem.h
	$(CXX) $(CXXFLAGS) -c supplier.cpp -o supplier.o

ecommercesystem.o: ecommercesystem.cpp ecommercesystem.h server.h
	$(CXX) $(CXXFLAGS) -c ecommercesystem.cpp -o ecommercesystem.o

mocc.o: $(LIBRARY)/mocc.cpp $(LIBRARY)/mocc.hpp
	$(CXX) $(CXXFLAGS) -c $(LIBRARY)/mocc.cpp -o mocc.o

time.o: $(LIBRARY)/time.cpp $(LIBRARY)/time.hpp
	$(CXX) $(CXXFLAGS) -c $(LIBRARY)/time.cpp -o time.o

clean:
	rm -f $(OBJS) main
