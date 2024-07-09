# Compiler and flags
CXX = g++
CXXFLAGS = -Iinclude

# Directories
SRC_DIR = src
INC_DIR = include
BIN_DIR = .

# Files
MAIN_SRC = main.cpp
TICTACTOE_SRC = $(SRC_DIR)/TicTacToe.cpp
MAIN_OBJ = main.o
TICTACTOE_OBJ = TicTacToe.o
EXECUTABLE = main

# Targets
all: $(EXECUTABLE)

$(EXECUTABLE): $(MAIN_OBJ) $(TICTACTOE_OBJ)
	$(CXX) $(MAIN_OBJ) $(TICTACTOE_OBJ) -o $(BIN_DIR)/$(EXECUTABLE)
	del -f $(MAIN_OBJ) $(TICTACTOE_OBJ)

$(MAIN_OBJ): $(MAIN_SRC)
	$(CXX) $(CXXFLAGS) -c $(MAIN_SRC) -o $(MAIN_OBJ)

$(TICTACTOE_OBJ): $(TICTACTOE_SRC) $(INC_DIR)/TicTacToe.hpp
	$(CXX) $(CXXFLAGS) -c $(TICTACTOE_SRC) -o $(TICTACTOE_OBJ)

clean:
	del -f *.o $(BIN_DIR)/$(EXECUTABLE)