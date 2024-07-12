all: compile link
	del -f *.o

compile:
	g++ -c main.cpp src/*.cpp -ISFML_src/include

link:
	g++ *.o -o main -LSFML_src/lib -lsfml-graphics -lsfml-window -lsfml-system