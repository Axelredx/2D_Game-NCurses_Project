#include <iostream>
#include <ncurses.h>
#include <cstring>
#include <string>
#include <ctime>
#ifdef _WIN32
#include <pthread.h>
#endif

#ifdef _WIN32
#include <windows.h>
#endif

#include <fstream>
#include "gameEngine.hpp"
using namespace std;

int main(int argc, char** argv){
    initialize();
    int y_scr, x_scr;
    getmaxyx(stdscr,y_scr,x_scr);//screen measure

    BOX pre_box(y_scr/2,x_scr/2,y_scr/4,x_scr/4);
    //BOX main_box(30,120,0,0); height,width,start_y,start_x

    char v1[20], v2[20], v3[20], v4[20];
    strcpy(v1,"Menu");
    strcpy(v2,"Start a new game");
    strcpy(v3,"Continue");
    strcpy(v4,"Esc");

    MENU menu(y_scr/2,x_scr/2,y_scr/4,x_scr/4,v1,v2,v3,v4);
    // map(height,lenght,y_scr,x_scr,ladders,holes,twoHoles?,twoLadders?,
    //     cloud,day,x1_hole_start,x1_hole_finish,x2_hole_start,x2_hole_finish,map seed)
    MAP map1(30,120,y_scr/6,x_scr/6,true,true,true,false,true,true,31,40,81,90,1),
        map2(30,120,y_scr/6,x_scr/6,false,true,false,false,true,false,51,60,0,0,2),
        map3(30,120,y_scr/6,x_scr/6,true,true,false,false,false,true,41,50,71,80,3),
        map4(30,120,y_scr/6,x_scr/6,true,true,true,true,false,false,31,40,61,70,4),
        map5(30,120,y_scr/6,x_scr/6,true,false,false,true,true,false,21,30,81,90,5),
        map6(30,120,y_scr/6,x_scr/6,false,true,false,false,false,true,81,90,71,80,6),
        map7(30,120,y_scr/6,x_scr/6,true,true,true,true,false,false,11,20,61,70,7),
        map8(30,120,y_scr/6,x_scr/6,true,false,false,false,false,true,41,50,71,80,8),
        map9(30,120,y_scr/6,x_scr/6,true,true,true,true,true,false,11,20,81,90,9),
        map10(30,120,y_scr/6,x_scr/6,false,true,true,false,true,true,41,50,61,70,10);

    pregame(pre_box,y_scr,x_scr);

    int c=menu.choice();
    if(c==3){
        //exit
        endwin();
        return 0;
    }else if(c==2){
        //start game from a gamefile
        mvprintw(0, 0, "Press a key to start the Game from the Game-Save!");
    	getch();
        clear();
        int seed_generated=0;
        //check if savegame.txt exists
        ifstream savegame;
        savegame.open("savegame.txt");
        if(savegame.is_open()){
        	string kek, dump2;
        	for(int i=0; i<4; i++)
        	{
        		getline(savegame,kek);
        	}
        	kek="";
        	getline(savegame,kek, '#');

        	if(kek.compare("map")==0)
        	{
        		getline(savegame, kek, '\n');
        		seed_generated=stoi(kek);
        	}else
        	{
        		clear();
        		mvprintw((y_scr/2)-5, (x_scr/2)-2, "error in locating map number");
        		mvprintw((y_scr/2)-4, (x_scr/2)-2, "resorting to default value");
        		refresh();
        		getch();
        		getline(savegame, dump2);
        	}
        }
        savegame.close();

        WINDOW* map_used=map_generator(map1,map2,map3,map4,map5,map6,
                                        map7,map8,map9,map10,seed_generated,false);

        game_flow(y_scr,x_scr,map_used,pre_box,map1,map2,map3,map4,map5,map6,map7,
                    map8,map9,map10,seed_generated,false);
    }else{
        //new game
    	clear();
        refresh();
        remove("savegame.txt");
        int seed_generated=map_randomizer(map1,map2,map3,map4,map5,map6,map7,
                                               map8,map9,map10,1,false);
        WINDOW* map_used=map_generator(map1,map2,map3,map4,map5,map6,
                                        map7,map8,map9,map10,seed_generated,false);

        game_flow(y_scr,x_scr,map_used,pre_box,map1,map2,map3,map4,map5,map6,map7,
                    map8,map9,map10,seed_generated,false);
    }
    endwin(); //memory deallocation
    return 0;
}