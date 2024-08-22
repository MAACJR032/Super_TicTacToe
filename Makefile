# Compiler flag
CC = g++

# delete
RM = del -f

# Paths
SRC_DIR = src
SFML_INCLUDE = SFML_src/include
SFML_LIB = SFML_src/lib
BIN = bin

# files
MAIN = main.cpp
EXE = main

# Find all .cpp files in SRC_DIR and create corresponding .o files in BIN
SRC_FILES = $(wildcard $(SRC_DIR)/*.cpp)
OBJS = $(patsubst $(SRC_DIR)/%.cpp,$(BIN)/%.o,$(SRC_FILES)) $(BIN)/main.o

all: compile link
# $(RM) *.o

compile: $(OBJS)
# $(CC) -c $(MAIN) $(SRC_DIR)/*.cpp -I$(SFML_INCLUDE) -o $(BIN)/

# Compile main.cpp separately
$(BIN)/main.o: $(MAIN)
	$(CC) -c $< -I$(SFML_INCLUDE) -o $@

# Compile all other .cpp files
$(BIN)/%.o: $(SRC_DIR)/%.cpp
	$(CC) -c $< -I$(SFML_INCLUDE) -o $@

link:
	$(CC) $(OBJS) -o $(EXE) -L$(SFML_LIB) -lsfml-graphics -lsfml-window -lsfml-system

clean:
	if exist $(EXE).exe del $(EXE).exe
	for %%f in ($(BIN)\*.o) do del %%f