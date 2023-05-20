#include <iostream>
#include <cstring>
#include <ctime>
#include <ncurses.h>
using namespace std;

class BOX{
    protected:
    int height, width, start_y, start_x;
    public:
    int game_scr=0;
    BOX(int h, int w, int y,int x){
        height=h;
        width=w;
        start_y=y;
        start_x=x;
    }
    WINDOW* create_box();
    WINDOW* modify_box(char tag[]);
};

class MENU : public BOX{
    protected:
        char tag[20], tag2[20], tag3[20], tag4[20]; 
    public:
    MENU(int h, int w, int y, int x, char tag[], char tag2[], char tag3[], char tag4[]) : BOX(h, w, y, x){
        strcpy(this->tag,tag);
        strcpy(this->tag2,tag2);
        strcpy(this->tag3,tag3);
        strcpy(this->tag4,tag4);
    }
    int choice();
};

class MAP: public BOX{
    protected:
    bool ladder_on, holes_on, two_holes, two_ladders, cloud, day;
    int x1_hole_start, x1_hole_finish, x2_hole_start, x2_hole_finish;
    public:
    int map_seed;
    MAP(int h, int w, int y,int x, bool l_on, bool h_on, 
        bool h_2, bool l_2, bool c, bool d, int h_p1, int h_p2, int h_p3, int h_p4, int m_s):BOX(h, w, y, x){
        ladder_on=l_on;
        holes_on=h_on;
        two_holes=h_2;
        two_ladders=l_2;
        cloud=c;
        day=d;
        x1_hole_start=h_p1;
        x1_hole_finish=h_p2;
        x2_hole_start=h_p3;
        x2_hole_finish=h_p4;
        map_seed=m_s;
    }
    WINDOW* create_map();
};