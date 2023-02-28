#include <iostream>
#include <cstring>
#include <ncurses.h>
using namespace std;

class BOX{
    protected:
    int height, width, start_y, start_x;
    public:
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
    bool ladder_on, holes_on, two_holes;
    int x1_hole, x2_hole, x3_hole, x4_hole;
    public:
    MAP(int h, int w, int y,int x, bool l_on, bool h_on, bool h_2, int h_p1, int h_p2, int h_p3, int h_p4):BOX(h, w, y, x){
        ladder_on=l_on;
        holes_on=h_on;
        two_holes=h_2;
        x1_hole=h_p1;
        x2_hole=h_p2;
        x3_hole=h_p3;
        x4_hole=h_p4;
    }
    WINDOW* create_map();
};