# Compiler flag
CC = g++

# delete
RM = del -f

# Paths
SRC_DIR = src
SFML_INCLUDE = SFML_src/include
SFML_LIB = SFML_src/lib
UTILS_DIR = Utils
BIN = bin

# files
MAIN = main.cpp
EXE = SuperTicTacToe

# Find all .cpp files in SRC_DIR and create corresponding .o files in BIN
SRC_FILES = $(wildcard $(SRC_DIR)/*.cpp)
UTILS_FILES = $(wildcard $(UTILS_DIR)/*.cpp)
OBJS = $(patsubst $(SRC_DIR)/%.cpp,$(BIN)/%.o,$(SRC_FILES)) \
	   $(patsubst $(UTILS_DIR)/%.cpp,$(BIN)/%.o,$(UTILS_FILES)) \
	   $(BIN)/SuperTicTacToe.o

all: compile link

compile: $(OBJS)

# Compile main.cpp separately
$(BIN)/SuperTicTacToe.o: $(MAIN)
	$(CC) -c $< -I$(SFML_INCLUDE) -o $@

# Compile .cpp in SRC_DIR
$(BIN)/%.o: $(SRC_DIR)/%.cpp
	$(CC) -c $< -I$(SFML_INCLUDE) -o $@

# Compile .cpp files in UTILS_DIR (dependency on colors.hpp)
$(BIN)/%.o: $(UTILS_DIR)/%.cpp $(UTILS_DIR)/colors.hpp
	$(CC) -c $< -I$(SFML_INCLUDE) -o $@

link:
	$(CC) $(OBJS) -o $(EXE) -L$(SFML_LIB) -lsfml-graphics -lsfml-window -lsfml-system

clean:
	if exist $(EXE).exe del $(EXE).exe
	for %%f in ($(BIN)\*.o) do del %%f