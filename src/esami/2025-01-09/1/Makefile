CXX = g++
INCLUDES = -I../../../mocc
CXXFLAGS = -std=c++17 -O2 -Wall -Wextra -pedantic $(INCLUDES)
TARGET = main
SRC = main.cpp parser.cpp simulation.cpp io.cpp

all: $(TARGET)

test: $(TARGET)
	./$(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRC)

clean:
	rm -f $(TARGET) *.o

.PHONY: all clean test
