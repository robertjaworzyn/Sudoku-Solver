sudoku: main.o sudoku.o
	g++ -std=c++11 -g main.o sudoku.o -o sudoku

main.o: main.cpp sudoku.h
	g++ -std=c++11 -Wall -g -c main.cpp

sudoku.o: sudoku.cpp sudoku.h
	g++ -std=c++11 -Wall -g -c sudoku.cpp

