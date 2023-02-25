#include <iostream>
#include <ncurses.h>
#include <cstring>
#include <string>
#include "box.hpp"
using namespace std;

void pregame(){
    move(15,52);//muove il cursore a posiz y,x
    printw("THE GAME\n"); //stampa stringa
    move(16,45);
    printw("press enter to start\n");
    getch();
    clear();
}


int main(int argc, char** argv){
    initscr(); //inizialzza lo screen e la memoria
    refresh(); //refresha lo screen per renderlo compatibile con ciò che è in memoria
    noecho();
    curs_set(0);

    pregame();

    move(5,5);
    refresh();

    int y, x;
    getmaxyx(stdscr,y,x);

    BOX main_box(30,120,0,0);
    char v1[20], v2[20], v3[20], v4[20];
    strcpy(v1,"Menu");
    strcpy(v2,"Start a new game");
    strcpy(v3,"Market");
    strcpy(v4,"Esc");
    MENU menu(y/2,x/2,y/4,x/4,v1,v2,v3,v4);

    int cx=menu.choice();
    
    refresh();

    getch();
    clear();

    main_box.create_box();

    getch();
    endwin(); //dealloca memoria dello screen
    return 0;
}