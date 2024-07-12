# Compiler flag
CC = g++

# delete
RM = del -f

# Paths
MAIN = main.cpp
SRC_DIR = src
EXE = main
SFML_INCLUDE = SFML_src/include
SFML_LIB = SFML_src/lib

all: compile link
	$(RM) *.o

compile:
	$(CC) -c $(MAIN) $(SRC_DIR)/*.cpp -I$(SFML_INCLUDE)

link:
	$(CC) *.o -o $(EXE) -L$(SFML_LIB) -lsfml-graphics -lsfml-window -lsfml-system

clean:
	$(RM) $(EXE).exe