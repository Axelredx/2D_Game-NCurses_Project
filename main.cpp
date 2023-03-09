#include <iostream>
#include <ncurses.h>
#include <cstring>
#include <string>
#include <ctime>
#include "box.hpp"
#include "player.hpp"
using namespace std;
using namespace std::this_thread;

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

WINDOW* map_randomizer(class MAP map1, class MAP map2, class MAP map3, class MAP map4,
                       class MAP map5, class MAP map6, class MAP map7, class MAP map8,
                       class MAP map9, class MAP map10, bool used, int last_map){
        srand(time(0));
        int result=rand()%11;
        if(used==false){
            if(result==1)
                return map1.create_map();
            else if(result==2)
                return map2.create_map();
            else if(result==3)
                return map3.create_map();
            else if(result==4)
                return map4.create_map();
            else if(result==5)
                return map5.create_map();
            else if(result==6)
                return map6.create_map();
            else if(result==7)
                return map7.create_map();
            else if(result==8)
                return map8.create_map();
            else if(result==9)
                return map9.create_map();
            else 
                return map10.create_map();
        }else{
            if(last_map==1)
                return map2.create_map();
            else if(last_map==2)
                return map3.create_map();
            else if(last_map==3)
                return map4.create_map();
            else if(last_map==4)
                return map5.create_map();
            else if(last_map==5)
                return map6.create_map();
            else if(last_map==6)
                return map7.create_map();
            else if(last_map==7)
                return map8.create_map();
            else if(last_map==8)
                return map9.create_map();
            else if(last_map==9)
                return map10.create_map();
            else
                return map1.create_map();

        }
        
}

void game_flow(int y_scr, int x_scr,WINDOW* map){
    player * p = new player(map, 15, 4, 'P');		//(finestra, y da cui il personagio spawna, 
                                                    //x da cui il personaggio spawna, icona del personaggio)
	do{
		p->display();
		wrefresh(map);
	}while(p->move()!=27);

    char v1[20], v2[20], v3[20], v4[20];
    strcpy(v1,"Menu");
    strcpy(v2,"Market");
    strcpy(v3,"Esc");
    strcpy(v4," ");

    MENU menu(y_scr/2,x_scr/2,y_scr/4,x_scr/4,v1,v2,v3,v4);
    int cx=menu.choice();
    if(cx==2){
        endwin();
        return;
    }
}

int main(int argc, char** argv){
    initialize();
    int y_scr, x_scr;
    getmaxyx(stdscr,y_scr,x_scr);//grandezze screen

    BOX pre_box(y_scr/2,x_scr/2,y_scr/4,x_scr/4);
    BOX main_box(30,120,0,0);//height,width,start_y,start_x

    char v1[20], v2[20], v3[20], v4[20];
    strcpy(v1,"Menu");
    strcpy(v2,"Start a new game");
    strcpy(v3,"Market");
    strcpy(v4,"Esc");

    MENU menu(y_scr/2,x_scr/2,y_scr/4,x_scr/4,v1,v2,v3,v4);
    MAP map1(30,120,y_scr/6,x_scr/6,true,true,true,false,true,true,31,40,81,90), 
        map2(30,120,y_scr/6,x_scr/6,false,true,false,false,true,false,51,60,0,0), 
        map3(30,120,y_scr/6,x_scr/6,true,true,false,false,false,true,41,50,71,80),
        map4(30,120,y_scr/6,x_scr/6,true,true,true,true,false,false,31,40,61,70),
        map5(30,120,y_scr/6,x_scr/6,true,false,false,true,true,false,21,30,80,90),
        map6(30,120,y_scr/6,x_scr/6,false,true,false,false,false,true,81,90,71,80),
        map7(30,120,y_scr/6,x_scr/6,true,true,true,true,false,false,11,20,61,70),
        map8(30,120,y_scr/6,x_scr/6,true,false,false,false,false,true,41,50,71,80),
        map9(30,120,y_scr/6,x_scr/6,true,true,true,true,true,false,11,20,81,90),
        map10(30,120,y_scr/6,x_scr/6,false,true,true,false,true,true,41,50,61,70);

    pregame(pre_box,y_scr,x_scr);

    int c=menu.choice();
    if(c==3){
        endwin();
        return 0;
    }else if(c==1){
        WINDOW* map_used=map_randomizer(map1,map2,map3,map4,map5,map6,map7,map8,map9,map10,false,10);
        game_flow(y_scr,x_scr,map_used);
    }
    
    main_box.create_box();

    getch();
    endwin(); //deallocaz. memoria
    return 0;
}