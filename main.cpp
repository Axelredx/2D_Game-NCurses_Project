#include <iostream>
#include <ncurses.h>
#include <cstring>
#include <string>
#include "box.hpp"
using namespace std;

//schermata iniziale
void pregame(){
    initscr(); //inizialzza lo screen e la memoria
    refresh(); //refresha lo screen per renderlo compatibile con ciò che è in memoria
    noecho(); //impedisce all'user di typare
    curs_set(false); //nasconde cursore
    move(15,52);//muove il cursore a posiz y,x
    printw("THE GAME\n"); //stampa stringa
    move(16,45);
    printw("press enter to start\n");
    getch();
    clear();
}


int main(int argc, char** argv){
    pregame();

    move(5,5);
    refresh();

    int y, x;
    getmaxyx(stdscr,y,x);//grandezze screen

    BOX main_box(30,120,0,0);//height,width,strt_y,start_x

    char v1[20], v2[20], v3[20], v4[20];
    strcpy(v1,"Menu");
    strcpy(v2,"Start a new game");
    strcpy(v3,"Market");
    strcpy(v4,"Esc");
    MENU menu(y/2,x/2,y/4,x/4,v1,v2,v3,v4);

    int cx=menu.choice();
    
    MAP map1(30,120,0,0,false,true,true,31,40,81,90);

    map1.create_map();

    refresh();

    getch();
    clear();

    main_box.create_box();

    getch();
    endwin(); //deallocaz. memoria
    return 0;
}