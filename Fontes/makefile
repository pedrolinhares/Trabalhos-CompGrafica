All: main.o Malhas.o
	g++ -o malhas main.o Malhas.o -lglut

main.o: main.cpp Malhas.h
	g++ -c main.cpp Malhas.cpp

Malhas.o: Malhas.cpp Malhas.h
	g++ -c Malhas.cpp
