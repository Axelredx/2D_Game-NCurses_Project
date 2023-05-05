#include <iostream>
#include<ncurses.h>
#include<unistd.h>

class basicenemy{
protected:
	int yLoc, xLoc, yMax, xMax, projy, projx, dirlock;
	bool s;
	char enemy;
	WINDOW * curwin;
public:
	int life;
	basicenemy(WINDOW * win, int y, int x, int l, char e);
	void display();
	int playerfinder();
	void mvup();
	void mvdown();
	void mvleft();
	void mvright();
	void* behaviour(void*);
	void shoot(int dir);
    bool isterrain(char t);
    void takedamage();
};