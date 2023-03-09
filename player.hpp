#include <iostream>
#include <thread>
#include<ncurses.h>
#include<unistd.h>



class player {
    protected:
        int xLoc, yLoc, xMax, yMax, dir, life, originx, originy;
        char character;
        WINDOW * curwin;

    public:
        player(WINDOW * win, int y, int x, char c);

        bool isterrain(char t);
        void mvup();
        void mvdown();
        void mvleft();
        void mvright();
        int move();
        void jump();
        int leftright();
        void display();
        void stairsup();
        void stairsdown();
};