CXX = g++
INCLUDES = -I../../../mocc
CXXFLAGS = -std=c++17 -O3 -Wall -Wextra -pedantic $(INCLUDES)
TARGET = main
SRC = main.cpp parser.cpp simulation.cpp

all: $(TARGET)

test: $(TARGET)
	./$(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRC)

clean:
	rm -f $(TARGET) *.o

.PHONY: all clean test
