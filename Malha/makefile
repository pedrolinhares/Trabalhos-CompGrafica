All: main.o Malhas.o
	g++ -o malhas main.o Malhas.o -lglut

main.o: main.cpp Todasmalhas.h
	g++ -c main.cpp Malhas.cpp

Malhas.o: Malhas.cpp Todasmalhas.h
	g++ -c Malhas.cpp
