#include <iostream>
#include <ncurses.h>
#include <cstring>
#include <string>
#include <ctime>
#include "dataManager.hpp" //nel pacchetto sono anche inclusi box.hpp, market.hpp e player.hpp
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
                       class MAP map9, class MAP map10, int prev_seed, bool next_seed){
        if(next_seed==true){
            if(prev_seed==1)
                return 2;
            else if(prev_seed==2)
                return 3;
            else if(prev_seed==3)
                return 4;
            else if(prev_seed==4)
                return 5;
            else if(prev_seed==5)
                return 6;
            else if(prev_seed==6)
                return 7;
            else if(prev_seed==7)
                return 8;
            else if(prev_seed==8)
                return 9;
            else if(prev_seed==9)
                return 10;
            else 
                return 1;
        }else{
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
}

//restituisce puntatore mappa in base al seed
WINDOW* map_generator(class MAP map1, class MAP map2, class MAP map3, class MAP map4,
                       class MAP map5, class MAP map6, class MAP map7, class MAP map8,
                       class MAP map9, class MAP map10, int seed, bool nxt_lvl){
        if(nxt_lvl==true){
            if(seed==1)
                return map2.create_map();
            else if(seed==2)
                return map3.create_map();
            else if(seed==3)
                return map4.create_map();
            else if(seed==4)
                return map5.create_map();
            else if(seed==5)
                return map6.create_map();
            else if(seed==6)
                return map7.create_map();
            else if(seed==7)
                return map8.create_map();
            else if(seed==8)
                return map9.create_map();
            else if(seed==9)
                return map10.create_map();
            else 
                return map1.create_map();
        }else{
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
}

void game_flow(int y_scr, int x_scr, WINDOW* map, class BOX box,
                class MAP map1, class MAP map2, class MAP map3, class MAP map4,
                class MAP map5, class MAP map6, class MAP map7, class MAP map8,
                class MAP map9, class MAP map10, int seed){
    int player_x, player_y, money, life;

	//FOLLOWING: default values for creating player-class items
	player_x=4;
	player_y=15;
	money=0;
	life=3;

	ifstream savegame;
	string lel;
	savegame.open("savegame.txt");
	if(savegame.is_open())
	{
		getline(savegame, lel);
		player_y = stoi(lel);	//NOTE: stoi(<string>) converts a string to int

		getline(savegame, lel);
		player_x = stoi(lel);

		getline(savegame, lel);
		life = stoi(lel);

		getline(savegame, lel);
		money = stoi(lel);

		savegame.close();

	}

    player * p = new player(map, player_y, player_x, 'P', money, life);		
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
        
	}while(p->move()!=27 && p->life!=0 && p->playeroutput(1)!=116);

    //entrata nuova stanza
    if(p->playeroutput(1)==116){
        clear();
        refresh();
        int seed_generated=map_randomizer(map1,map2,map3,map4,map5,map6,
                                            map7,map8,map9,map10,seed,true);
        WINDOW* new_map = map_generator(map1,map2,map3,map4,map5,map6,
                                        map7,map8,map9,map10,seed_generated,true);
        game_flow(y_scr,x_scr,new_map,box,map1,map2,map3,map4,map5,
                    map6,map7,map8,map9,map10,seed_generated);
        endwin();
        return;
    }

    //morte
    if(p->life==0){
        clear();
        refresh();
        death_screen(box,y_scr,x_scr,map1,map2,map3,map4,map5,map6,map7,
                        map8,map9,map10,seed);
        endwin();
        return;
    }

    char v1[20], v2[20], v3[20], v4[20];
    strcpy(v1,"Menu");
    strcpy(v2,"Resume");
    strcpy(v3,"Market");
    strcpy(v4,"Save and exit");

    MENU menu(y_scr/2,x_scr/2,y_scr/4,x_scr/4,v1,v2,v3,v4);

    char v5[20], v6[20], v7[20], v8[20];
    strcpy(v5,"Market");
    strcpy(v6,"Health boost");
    strcpy(v7,"Jump boost");
    strcpy(v8,"Return to the game");

    MENU market(y_scr/2,x_scr/2,y_scr/4,x_scr/4,v5,v6,v7,v8);

    clear();
    refresh();

    int cx=menu.choice();
    if(cx==1){
        game_flow(y_scr,x_scr,map,box,map1,map2,map3,map4,map5,
                    map6,map7,map8,map9,map10,seed);
    }else if(cx==2){
        //accesso al market
       int mx=market.choice();
        if(mx==1)
            buyHealth(p);
        else if(mx==2)
            buyJumpboost(p);
        else{
            clear();
            refresh();
            WINDOW* n_map = map_generator(map1,map2,map3,map4,map5,map6,
                                            map7,map8,map9,map10,seed,false);
            game_flow(y_scr,x_scr,n_map,box,map1,map2,map3,map4,map5,
                        map6,map7,map8,map9,map10,seed);
            endwin();
            return;
        }
    }
    else if(cx==3){
        //salva partita
        //salva partita
    	int kek=save_data(p, seed, "savegame.txt" );
    	if(kek==1)
    	{
    		clear();
    		mvprintw(0, 0, "game saved");
    		refresh();
    		getch();
    	}else
    	{
    		clear();
    		mvprintw(0, 0, "game could not be saved, oopsie :) ");
    		refresh();
    	    getch();
    	}
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
        int seed_generated=map_randomizer(map1,map2,map3,map4,map5,map6,map7,map8,map9,map10,0,false);

        //controllo file pre-esistente
        ifstream savegame;
        savegame.open("savegame.txt");
        if(savegame.is_open()){
        	string kek;
        	for(int i=0; i<4; i++)
        	{
        		getline(savegame,kek);
        	}
        	kek="";
        	getline(savegame,kek);

        	seed_generated=stoi(kek);
        }
        savegame.close();

        WINDOW* map_used=map_generator(map1,map2,map3,map4,map5,map6,
                                        map7,map8,map9,map10,seed_generated,false);

        game_flow(y_scr,x_scr,map_used,pre_box,map1,map2,map3,map4,map5,map6,map7,
                    map8,map9,map10,seed_generated);
    }else{
    	clear();
    	mvprintw(0, 0, "Can't access yet! Press a key to start a new game");
    	getch(); 
        clear();
        refresh();       

        int seed_generated=map_randomizer(map1,map2,map3,map4,map5,map6,map7,map8,map9,map10,0,false);
        WINDOW* map_used=map_generator(map1,map2,map3,map4,map5,map6,
                                        map7,map8,map9,map10,seed_generated,false);

        game_flow(y_scr,x_scr,map_used,pre_box,map1,map2,map3,map4,map5,map6,map7,
                    map8,map9,map10,seed_generated);
    }
    endwin(); //deallocaz. memoria
    return 0;
}