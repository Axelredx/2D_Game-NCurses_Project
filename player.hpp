#include <iostream>
#include<ncurses.h>
#include<unistd.h>

class player {
    protected:
        int xLoc, yLoc, xMax, yMax, originx, originy, projx, projy;
        bool s, dir, dirlock, j;
        char character;
        WINDOW * curwin;

    public:
        int money, life, jump_width, health_Price=80, jump_Price=50, Potion_Price=120, Artifact_Price=180;
        //Costruttore della classe
        player(WINDOW * win, int y=15, int x=4, char c='P', int m=100, int l=3){
        	curwin = win;
        	nodelay(curwin, TRUE);

        	yLoc=y;
        	xLoc = x;

        	//Coordinata y dello spawn del giocatore
        	originy=y;

        	//Coordinata x dello spawn del giocatore
        	originx=x;

        	getmaxyx(curwin, yMax, xMax);
        	keypad(curwin, true);
        	character=c;

        	//Vita del giocatore
        	life=l;

        	//Soldi del giocatore
        	money=m;

        	//Indica le y del proiettile
        	projy=y;

        	//Indica le x del proiettile
        	projx=x;

        	//Indica se un proiettile sta venendo disegnato
        	s=false;

        	//Indica l'ultima direzione in cui il giocatore è andato
        	dir=false;

        	//Blocca la direzione del proiettile
        	dirlock=false;

        	//Indica se il giocatore sta saltando
        	j=false;

        	//Stampa la vita del giocatore
        	mvwprintw(curwin, 0, 0,"HP: %d", life);

        	//Stampa i soldi del giocatore
        	mvwprintw(curwin, 0, xMax-10,"COINS: %d", money);
        }

        bool isterrain(char t);
        bool bulletterrain(char t);
        bool isenemy(char t);
        void mvup();
        void mvdown();
        void mvleft();
        void mvright();
        int move();
        void jump();
        int leftright();
        void* display(void * arg);
        void stairsup();
        void stairsdown();
        void lifeshow();
        void gravity();
        void shoot();
        int playeroutput(int input);
};