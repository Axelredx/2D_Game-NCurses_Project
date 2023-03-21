#include <iostream>
#include <ncurses.h>
#include <cstring>
#include <string>
#include <ctime>
#include "box.hpp"
#include "player.hpp"
using namespace std;
typedef void * (*THREADFUNCPTR)(void *);

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

void death_screen(class BOX box, int y_scr, int x_scr, class MAP map1, class MAP map2, class MAP map3, class MAP map4,
                       class MAP map5, class MAP map6, class MAP map7, class MAP map8,
                       class MAP map9, class MAP map10, int seed){
    WINDOW* fin=box.create_box();
    mvwprintw(fin,y_scr/4,(x_scr/4)-3,"YOU DIED");
    mvwprintw(fin,(y_scr/4)+1,(x_scr/4)-10," press a key to exit");
    refresh();
    wrefresh(fin);
    getch();
    clear();
    return;
}

//genera un seed
int map_randomizer(class MAP map1, class MAP map2, class MAP map3, class MAP map4,
                       class MAP map5, class MAP map6, class MAP map7, class MAP map8,
                       class MAP map9, class MAP map10){
        srand(time(0));
        int result=rand()%11;
        if(result==1)
            return map1.map_seed;
        else if(result==2)
            return map2.map_seed;
        else if(result==3)
            return map3.map_seed;
        else if(result==4)
            return map4.map_seed;
        else if(result==5)
            return map5.map_seed;
        else if(result==6)
            return map6.map_seed;
        else if(result==7)
            return map7.map_seed;
        else if(result==8)
            return map8.map_seed;
        else if(result==9)
            return map9.map_seed;
        else 
            return map10.map_seed;    
}

//restituisce puntatore mappa in base al seed
WINDOW* map_generatior(class MAP map1, class MAP map2, class MAP map3, class MAP map4,
                       class MAP map5, class MAP map6, class MAP map7, class MAP map8,
                       class MAP map9, class MAP map10, int seed){
        if(seed==1)
            return map1.create_map();
        else if(seed==2)
            return map2.create_map();
        else if(seed==3)
            return map3.create_map();
        else if(seed==4)
            return map4.create_map();
        else if(seed==5)
            return map5.create_map();
        else if(seed==6)
            return map6.create_map();
        else if(seed==7)
            return map7.create_map();
        else if(seed==8)
            return map8.create_map();
        else if(seed==9)
            return map9.create_map();
        else 
            return map10.create_map();
}

void game_flow(int y_scr, int x_scr, WINDOW* map, bool next_lvl, class BOX box,
                class MAP map1, class MAP map2, class MAP map3, class MAP map4,
                class MAP map5, class MAP map6, class MAP map7, class MAP map8,
                class MAP map9, class MAP map10, int seed){

    player * p = new player(map, 15, 4, 'P');		
        //(finestra, y da cui il personagio spawna, 
        //x da cui il personaggio spawna, icona del personaggio)

    //Inizializzazione del thread giocatore
	pthread_t playerthread;
	do{
		//Creazione del thread
		pthread_create(&playerthread, NULL, (THREADFUNCPTR) &player::display, p);
		//Aspetta che il thread finisca di elaborare
		pthread_join(playerthread, NULL);
        //refresh mappa
		wrefresh(map);
        //aggiungere parametro x capire se player ha raggiunto fine lvl,
        // allora passare al prossimo
        
	}while(p->move()!=27 && p->life!=0); 

    //morte
    if(p->life==0){
        clear();
        refresh();
        death_screen(box,y_scr,x_scr,map1,map2,map3,map4,map5,map6,map7,
                        map8,map9,map10,seed);
        endwin();
        return;
    }

    int prova;
	//Guardare il file "player.cpp" per sapere l'utilizzo di questa funzione
	//POTREBBE ESSERE MOLTO UTILE SORPATUTTO PER LUCA
	prova=p->playeroutput(5);

    char v1[20], v2[20], v3[20], v4[20];
    strcpy(v1,"Menu");
    strcpy(v2,"Resume");
    strcpy(v3,"Market");
    strcpy(v4,"Save and exit");

    MENU menu(y_scr/2,x_scr/2,y_scr/4,x_scr/4,v1,v2,v3,v4);

    int cx=menu.choice();
    if(cx==1){
        game_flow(y_scr,x_scr,map,true,box,map1,map2,map3,map4,map5,
                    map6,map7,map8,map9,map10,seed);
    }else if(cx==2){
        //accesso al market
    }
    else if(cx==3){
        //salva partita
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
    MAP map1(30,120,y_scr/6,x_scr/6,true,true,true,false,true,true,31,40,81,90,1), 
        map2(30,120,y_scr/6,x_scr/6,false,true,false,false,true,false,51,60,0,0,2), 
        map3(30,120,y_scr/6,x_scr/6,true,true,false,false,false,true,41,50,71,80,3),
        map4(30,120,y_scr/6,x_scr/6,true,true,true,true,false,false,31,40,61,70,4),
        map5(30,120,y_scr/6,x_scr/6,true,false,false,true,true,false,21,30,80,90,5),
        map6(30,120,y_scr/6,x_scr/6,false,true,false,false,false,true,81,90,71,80,6),
        map7(30,120,y_scr/6,x_scr/6,true,true,true,true,false,false,11,20,61,70,7),
        map8(30,120,y_scr/6,x_scr/6,true,false,false,false,false,true,41,50,71,80,8),
        map9(30,120,y_scr/6,x_scr/6,true,true,true,true,true,false,11,20,81,90,9),
        map10(30,120,y_scr/6,x_scr/6,false,true,true,false,true,true,41,50,61,70,10);

    pregame(pre_box,y_scr,x_scr);

    int c=menu.choice();
    if(c==3){
        endwin();
        return 0;
    }else if(c==1){
        int seed_generated=map_randomizer(map1,map2,map3,map4,map5,map6,map7,map8,map9,map10);

        WINDOW* map_used=map_generatior(map1,map2,map3,map4,map5,map6,
                                        map7,map8,map9,map10,seed_generated);

        game_flow(y_scr,x_scr,map_used,true,pre_box,map1,map2,map3,map4,map5,map6,map7,
                    map8,map9,map10,seed_generated);
    }else{
        main_box.create_box();
    }
    endwin(); //deallocaz. memoria
    return 0;
}