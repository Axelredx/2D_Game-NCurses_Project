#include <iostream>
#include <ncurses.h>
#include <cstring>
#include <string>
#include "box.hpp"
using namespace std;

//inizializzaz. screen
void initialize(){
    initscr(); //inizialzza lo screen e la memoria
    refresh(); //refresha lo screen per renderlo compatibile con ciò che è in memoria
    noecho(); //impedisce all'user di typare
    curs_set(false); //nasconde cursore
}

//scheramata iniziale
void pregame(class BOX box, int y_scr, int x_scr){
    WINDOW* fin=box.create_box();
    mvwprintw(fin,y_scr/4,(x_scr/4)-3,"THE GAME");
    mvwprintw(fin,(y_scr/4)+1,(x_scr/4)-10,"press a key to start");
    refresh();
    wrefresh(fin);
    getch();
    clear();
}

int main(int argc, char** argv){
    initialize();
    int y, x;
    getmaxyx(stdscr,y,x);//grandezze screen

    BOX pre_box(y/2,x/2,y/4,x/4);
    pregame(pre_box,y,x);

    move(5,5);
    refresh();



    BOX main_box(30,120,0,0);//height,width,strt_y,start_x

    char v1[20], v2[20], v3[20], v4[20];
    strcpy(v1,"Menu");
    strcpy(v2,"Start a new game");
    strcpy(v3,"Market");
    strcpy(v4,"Esc");
    MENU menu(y/2,x/2,y/4,x/4,v1,v2,v3,v4);

    int cx=menu.choice();
    if(cx==3){
        endwin();
        return 0;
    }
    
    MAP map1(30,120,y/6,x/6,true,true,true,false,true,true,31,40,81,90), 
        map2(30,120,y/6,x/6,false,true,false,false,true,false,51,60,0,0), 
        map3(30,120,y/6,x/6,true,true,false,false,false,true,41,50,71,80),
        map4(30,120,y/6,x/6,true,true,true,true,false,false,31,40,61,70),
        map5(30,120,y/6,x/6,true,false,false,true,true,false,21,30,80,90),
        map6(30,120,y/6,x/6,false,true,false,false,false,true,81,90,71,80),
        map7(30,120,y/6,x/6,true,true,true,true,false,false,11,20,61,70),
        map8(30,120,y/6,x/6,true,false,false,false,false,true,41,50,71,80),
        map9(30,120,y/6,x/6,true,true,true,true,true,false,11,20,81,90),
        map10(30,120,y/6,x/6,false,true,true,false,true,true,41,50,61,70);

    map1.create_map();
    refresh();
    getch();
    clear();

    map2.create_map();
    refresh();
    getch();
    clear();

    map3.create_map();
    refresh();
    getch();
    clear();

    map4.create_map();
    refresh();
    getch();
    clear();

    map5.create_map();
    refresh();
    getch();
    clear();

    map6.create_map();
    refresh();
    getch();
    clear();

    map7.create_map();
    refresh();
    getch();
    clear();

    map8.create_map();
    refresh();
    getch();
    clear();

    map9.create_map();
    refresh();
    getch();
    clear();

    map10.create_map();
    refresh();
    getch();
    clear();

    main_box.create_box();

    getch();
    endwin(); //deallocaz. memoria
    return 0;
}