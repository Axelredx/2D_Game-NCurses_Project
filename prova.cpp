#include <iostream>
#include <cstring>
#include <ncurses.h>
using namespace std;

int main(int argc, char **argv){
    initscr();
    noecho();
    curs_set(0);

    
    /*        for(int j=0;j<height;j++){
            if(j>=23){
                if(i<31 && i>40){
                    mvwprintw(fin,j,i,"#");
                    refresh();
                }
                if(i<81 && i>90){
                    mvwprintw(fin,j,i,"#");
                    refresh();
                }
            }
        }
    
    int y, x;
    getmaxyx(stdscr,y,x);
    int width=x/2, height=y/2;
    int start_y=y/4, start_x=x/4;
    WINDOW* fin= newwin(y/2,x/2,y/4,x/4);
    for(int i=0;i<(width);i++){
        mvwprintw(fin,10,i,"#");
    }*/

    WINDOW* fin=newwin(30,120,0,0);
    for(int i=0;i<120;i++){
        mvwprintw(fin,23,i,"#");
    }
    refresh();
    box(fin,0,0);
    wrefresh(fin);


/*
    //prova di menu
    mvwprintw(fin,0,15,"Menu");
    mvwprintw(fin,1,1,"Start a new game");
    mvwprintw(fin,4,1,"Market");
    mvwprintw(fin,7,1,"Esc");


    char c;
    while(c=wgetch(fin)){
        if(c=='1'){
                wattron(fin, A_STANDOUT);
                mvwprintw(fin,1,1,"Start a new game"); 
                wattroff(fin, A_STANDOUT);
                mvwprintw(fin,7,1,"Esc"); 
                mvwprintw(fin,4,1,"Market");
        }
        else if(c=='2'){
                wattron(fin, A_STANDOUT);
                mvwprintw(fin,4,1,"Market"); 
                wattroff(fin, A_STANDOUT);
                mvwprintw(fin,7,1,"Esc"); 
                mvwprintw(fin,1,1,"Start a new game");
        }
        else if(c=='3'){
                wattron(fin, A_STANDOUT);
                mvwprintw(fin,7,1,"Esc"); 
                wattroff(fin, A_STANDOUT);
                mvwprintw(fin,1,1,"Start a new game");
                mvwprintw(fin,4,1,"Market");
        }
        else{
            mvwprintw(fin,1,1,"Start a new game");
            mvwprintw(fin,4,1,"Market");
            mvwprintw(fin,7,1,"Esc");
        }                   

    }

    //mappa
    /*int platformWidth = 50;
    int platformHeight = 20;
    int platformStartX = 5;
    int platformStartY = 5;
    int platformEndX = platformStartX + platformWidth;
    int platformEndY = platformStartY + platformHeight;
    
    // Draw the platform map
    for (int y = platformStartY; y < platformEndY; y++)
    {
        for (int x = platformStartX; x < platformEndX; x++)
        {
            if (y == platformStartY || y == platformEndY - 1 || x == platformStartX || x == platformEndX - 1)
            {
                mvwprintw(fin, y, x, "#");
            }
            else
            {
                mvwprintw(fin, y, x, " ");
            }
        }
    }*/

    /*for(int i=0;i<width;i++){
        for(int j=0;j<height;j++){           
                mvwprintw(fin, j, i, "#");
        }
    }*/
    
    /*WINDOW* fin2=newwin(30,120,0,0);
    box(fin2,0,0);
    /*for(int i=0;i<120;i++){
        for()
        wprintw(fin2,"°");
    }
    wrefresh(fin2);*/



    refresh();
    getch();
    endwin();
    return 0;
}