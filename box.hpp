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
    WINDOW* modify_box(char s[]);
};

class MENU : public BOX{
    protected:
        char v[20], v2[20], v3[20], v4[20]; 
    public:
    MENU(int h, int w, int y, int x, char v[], char a[], char b[], char d[]) : BOX(h, w, y, x){
        strcpy(this->v,v);
        strcpy(v2,a);
        strcpy(v3,b);
        strcpy(v4,d);
    }
    int choice();


};