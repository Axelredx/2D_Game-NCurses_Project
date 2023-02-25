all:
	g++ -I/mingw64/include/ncurses -o main  main.cpp box.hpp box.cpp -lncurses -L/mingw64/bin -static