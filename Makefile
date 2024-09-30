CXX = g++
CXXFLAGS = -std=c++11 -I/usr/include -I/usr/local/include
LDFLAGS = -lsfml-graphics -lsfml-window -lsfml-system

SRC = src
BIN = bin
OBJ = obj

SOURCES = $(wildcard $(SRC)/*.cpp)
OBJECTS = $(SOURCES:$(SRC)/%.cpp=$(OBJ)/%.o)
EXECUTABLE = $(BIN)/SnakeGame

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	mkdir -p $(BIN)
	$(CXX) $(OBJECTS) -o $@ $(LDFLAGS)

$(OBJ)/%.o: $(SRC)/%.cpp
	mkdir -p $(OBJ)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf $(BIN) $(OBJ)

.PHONY: all clean
