#include <iostream>
#include <thread>
#include <ncurses.h>
#include "player.hpp"

using namespace std;
using namespace std::this_thread;

int main(int argc, char ** argv) {
	initscr();
	noecho();
	cbreak();

	int yMax=30, xMax=120;

	WINDOW * pwin = newwin(yMax, xMax, 0, 0);
	refresh();
	box(pwin, 0, 0);
	refresh();
	wrefresh(pwin);
	keypad(pwin, true);

	player * p = new player(pwin, yMax-3, 1, 'P');		//sintassi: (finestra, y da cui il personagio spawna, x da cui il personaggio spawna, icona del personaggio)
	do{
		p->display();
		wrefresh(pwin);
	}while(p->move()!=27);

	getch();
	endwin();
	return 0;
}