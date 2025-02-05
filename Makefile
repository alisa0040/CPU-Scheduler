TARGET = scheduler

CXX = g++

CXXFLAGS = -Wall -Wextra -std=c++17

SRC = $(wildcard src/*.cpp)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) $(SRC) -o $(TARGET)

clean:
	rm -f $(TARGET)

test: $(TARGET)
	bash test.sh

run: $(TARGET)
	./$(TARGET) -t 2 -f input.txt -o output.txt
