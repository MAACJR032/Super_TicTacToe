ifdef OS
	RM = del -f
else
	RM = rm -f
endif

all: compile link
	$(RM) *.o

compile:
	g++ -c main.cpp src/*.cpp -ISFML_src/include

link:
	g++ *.o -o main -LSFML_src/lib -lsfml-graphics -lsfml-window -lsfml-system