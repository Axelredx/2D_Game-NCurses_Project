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
	jumpingenemy(WINDOW * win, int y=20, int x=20, int l=3, char e='E', int m=300, int d=4) : basicenemy(win, y, x, l, e, m){	j=false;
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

//Prende in input tre basicenemy e ne rilascia uno casualmente
basicenemy* basic_enemy_randomizer (basicenemy* e1, basicenemy* e2, basicenemy* e3);

//Una possibilità su quattro esca jumping enemy, nel caso esca, rilascia in output e, 
//in caso cotrario rilascia NULL
jumpingenemy* jumping_enemy_randomizer (jumpingenemy* e);