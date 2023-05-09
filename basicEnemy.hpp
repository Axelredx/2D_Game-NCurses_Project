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
	int life, money;
	basicenemy(WINDOW * win, int y, int x, int l, char e, int m){
		curwin=win;
		yLoc=y;
		xLoc=x;

		//Vita del nemico
		life=l;
		enemy=e;
		money=m;

		//Indica se si sta sparando un proiettile
		s=false;

		//Coordinate x e y del proiettile
		projx=0;
		projy=0;

		getmaxyx(curwin, yMax, xMax);
		dirlock=0;

		//setto rand
		srand(time(0));
	}
	void display();
	int playerfinder();
	void mvleft();
	void mvright();
	void mvdown();
	void* behaviour(void*);
	void shoot(int dir);
    bool isterrain(char t);
    void takedamage();
    void gravity();
};

class jumpingenemy: public basicenemy{
protected:
	bool j=false;
	int difficulty;
public:
	jumpingenemy(WINDOW * win, int y, int x, int l, char e, int m, int d) : basicenemy(win, y, x, l, e, m){
		j=false;
		difficulty=d;
	}
	void mvup();
	void mvleft();
	void mvright();
	int playerfinder();
	int bulletfinder();
    void jump(int dir);
	void* behaviour(void*);
    void takedamage();

};