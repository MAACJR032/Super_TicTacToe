# Compiler flag
CC = g++

# Compiler flags
CXXFLAGS = -std=c++17 -Wall -Wextra -Wno-error=implicit-fallthrough \
            -I$(SFML_INCLUDE) \
            -I$(INCLUDE_DIR) \
            -I$(INCLUDE_DIR)/types \
            -I$(SRC_DIR) \
            -I$(UTILS_DIR) \
	    -I$(SFML_BIN)

# Delete
RM = del /f

# Paths
SRC_DIR = src
# para o windowns compilar no actions github
ifeq ($(OS),Windows_NT)
    SFML_INCLUDE = "C:/Program Files (x86)/SFML/include"
    SFML_LIB = "C:/Program Files (x86)/SFML/lib"
	SFML_BIN = "C:/Program Files (x86)/SFML/bin/"
else
    SFML_INCLUDE = SFML_src/include
    SFML_LIB = SFML_src/lib
	SFML_BIN = SFML_src/bin
endif
INCLUDE_DIR = include

UTILS_DIR = src/Utils
BIN_INT = bin-int
BIN_DIR = bin

# Files
MAIN = main.cpp
EXE = SuperTicTacToe

# Find all .cpp files in SRC_DIR and create corresponding .o files in BIN_INT
SRC_FILES = $(wildcard $(SRC_DIR)/*.cpp)
UTILS_FILES = $(wildcard $(UTILS_DIR)/*/*.cpp) $(wildcard $(UTILS_DIR)/*.cpp) # Include subdirectories
OBJS = $(patsubst $(SRC_DIR)/%.cpp,$(BIN_INT)/%.o,$(SRC_FILES)) \
       $(patsubst $(UTILS_DIR)/%.cpp,$(BIN_INT)/%.o,$(UTILS_FILES)) \
       $(BIN_INT)/SuperTicTacToe.o

all: $(BIN_DIR)/$(EXE)

$(BIN_DIR)/$(EXE): $(OBJS)
	$(CC) $(CXXFLAGS) $(OBJS) -o $@ -L$(SFML_LIB) -lsfml-graphics -lsfml-window -lsfml-system

# Create necessary directories
$(BIN_INT):
	mkdir $(BIN_INT) 
	mkdir $(BIN_INT)/Path 
	mkdir $(BIN_INT)/Text 
	mkdir bin

# Compile main.cpp separately
$(BIN_INT)/SuperTicTacToe.o: $(MAIN) | $(BIN_INT)
	$(CC) $(CXXFLAGS) -c $< -o $@

# Compile .cpp files in SRC_DIR
$(BIN_INT)/%.o: $(SRC_DIR)/%.cpp | $(BIN_INT)
	$(CC) $(CXXFLAGS) -c $< -o $@

# Compile .cpp files in UTILS_DIR and its subdirectories
$(BIN_INT)/%.o: $(UTILS_DIR)/%.cpp | $(BIN_INT)
	$(CC) $(CXXFLAGS) -c $< -o $@

# Clean up
clean:
# linux
ifeq (Linux,$(shell uname -s))
	rm -rf bin-int/*.o bin-int/Path/*.o bin-int/Text/*.o bin/*
else 
# windows
	if exist $(BIN_DIR)\$(EXE).exe $(RM) $(BIN_DIR)\$(EXE).exe
	for %%f in ($(BIN_INT)\*.o) do $(RM) %%f
	for /r $(BIN_INT) %%f in (*.o) do $(RM) "%%f"
endif
