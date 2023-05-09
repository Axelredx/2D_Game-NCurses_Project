#include "gameEngine.hpp"
typedef void * (*THREADFUNCPTR)(void *);

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

//schermata di morte
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
            else if (seed==10)
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
            else if(seed==10)
                return map10.create_map();
            }
}

void game_flow(int y_scr, int x_scr, WINDOW* map, class BOX box,
                class MAP map1, class MAP map2, class MAP map3, class MAP map4,
                class MAP map5, class MAP map6, class MAP map7, class MAP map8,
                class MAP map9, class MAP map10, int seed, bool new_lvl){
    srand(time(0));
    int player_x, player_y, money, life;

	//FOLLOWING: default values for creating player-class items
	player_x=4;
	player_y=15;
	money=100;
	life=3;
	int saltoH=10;
	/*
	 * ultima versione del salvataggio
	 * le righe hanno una piccola descrizione di cosa rappresenta il numero che segue nel file di salvataggio
	 * per selezionare solo il dato, ho implementato questo insieme di operazioni
	 * in caso in cui il dato non venisse ritrovato, ritorna un messaggio di errore e ripristina i valori predefiniti per quel dato
	 */

	
        ifstream savegame;
	    string lel, dump;
	    savegame.open("savegame.txt");

        if(savegame.is_open())
        {   
            getline(savegame, lel, '#');
            if(lel.compare("Y_loc")==0)
            {
                getline(savegame, lel,'\n');
                player_y = stoi(lel);	//NOTE: stoi(<string>) converts a string to int
            }else
            {
                clear();
                mvprintw((y_scr/2)-5, (x_scr/2)-2, "error in locating Y_loc in savedata");
                mvprintw((y_scr/2)-4, (x_scr/2)-2, "resorting to default value");
                refresh();
                getch();
                getline(savegame, dump);	//goes to next line without saving

            }

            getline(savegame, lel, '#');
            if(lel.compare("X_loc")==0)
            {
                getline(savegame, lel,'\n');
                player_x = stoi(lel);	//NOTE: stoi(<string>) converts a string to int
            }else
            {
                clear();
                mvprintw((y_scr/2)-5, (x_scr/2)-2, "error in locating X_loc in savedata");
                mvprintw((y_scr/2)-4, (x_scr/2)-2, "resorting to default value");
                refresh();
                getch();
                getline(savegame, dump);
            }

            getline(savegame, lel, '#');		//check for saving of player health
            if(lel.compare("life")==0)
            {
                getline(savegame, lel, '\n');
                life=stoi(lel);
            }else
            {
                clear();
                mvprintw((y_scr/2)-5, (x_scr/2)-2, "error in locating player health");
                mvprintw((y_scr/2)-4, (x_scr/2)-2, "resorting to default value");
                refresh();
                getch();
                getline(savegame, dump);
            }


            getline(savegame, lel, '#');		//check for saving of player money
            if(lel.compare("credits")==0)
            {
                getline(savegame, lel, '\n');
                money=stoi(lel);
            }

            getline(savegame, lel, '#');		//check for jumpHeight
            if(lel.compare("jumpH")==0)
            {
                getline(savegame, lel, '\n');
                saltoH=stoi(lel);
            }



            savegame.close();

	    }
    
    //previene il riallocamento errato del player all'avanzamento del livello se presente il 
    //saveFile
    if(new_lvl==true){
        player_x=4;
	    player_y=22;
    }

    player * p = new player(map, player_y, player_x, 'P', money, life);
        //(finestra, y da cui il personagio spawna,
        //x da cui il personaggio spawna, icona del personaggio)

    p->salto=saltoH;

//sintassi: (finestra, y dello spawn del nemico, x dello spawn del nemico, vita del nemico, icona del nemico (lasciala 'e'), soldi rilasciati alla morte)
	basicenemy * e1 = new basicenemy(map, 15, 20, 1, 'e', 100);

	basicenemy * e2 = new basicenemy(map, 15, 25, 1, 'e', 100);

	basicenemy * e3 = new basicenemy(map, 15, 30, 3, 'e', 300);

	//sintassi: (finestra, y dello spawn del nemico, x dello spawn del nemico, vita del nemico, icona del nemico (lasciala 'e'),
	//soldi rilasciati alla morte, difficoltà del nemico !PIU IL NUMERO E' BASSO PIU E' DIFFICILE! (non usare numeri negativi)
	//sconsiglio di scendere sotto a 3)
	jumpingenemy * e4 = new jumpingenemy (map, 15, 35, 3, 'e', 600, 4);

	//Inizializzazione del thread giocatore e nemici
	pthread_t playerthread, enemythread1, enemythread2, enemythread3, enemythread4;
	do{
		//Creazione del thread
		pthread_create(&playerthread, NULL, (THREADFUNCPTR) &player::display, p);
		//Aspetta che il thread finisca di elaborare
		pthread_join(playerthread, NULL);
        //refresh mappa
		refresh();
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
                    map6,map7,map8,map9,map10,seed_generated,true);
        endwin();
        return;
    }

    //death of player
    if(p->life==0){
        clear();
        refresh();
        death_screen(box,y_scr,x_scr,map1,map2,map3,map4,map5,map6,map7,
                        map8,map9,map10,seed);
        remove("savegame.txt");
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
                clear();
                refresh();
                int kek=save_data(p, seed, "savegame.txt" );
                if(kek==1)
                {
                	clear();
                	mvprintw(0, 0, "loading");
                    mvprintw(1, 0, "press a key to continue");
                	refresh();
                	getch();
                	clear();
                	refresh();
                }else
                {
                    clear();
                    mvprintw(0, 0, "error in load screen ");
                    mvprintw(1, 0, "press a key to continue");
                    refresh();
                    getch();
                    clear();
                    refresh();
                }
                WINDOW* n_map = map_generator(map1,map2,map3,map4,map5,map6,
                                                map7,map8,map9,map10,seed,false);
                game_flow(y_scr,x_scr,n_map,box,map1,map2,map3,map4,map5,
                            map6,map7,map8,map9,map10,seed,false);
                endwin();
                return;
        }else if(cx==2){
            //accesso al market
           int mx=market.choice();
            if(mx==1){
                buyHealth(p);
                clear();
                refresh();
                int kek=save_data(p, seed, "savegame.txt" );
                if(kek==1)
                {
                	clear();
                	mvprintw(0, 0, "loading");
                    mvprintw(1, 0, "press a key to continue");
                	refresh();
                	getch();
                	clear();
                	refresh();
                }else
                {
                	clear();
                	mvprintw(0, 0, "error in load screen ");
                    mvprintw(1, 0, "press a key to continue");
                	refresh();
                	getch();
                	clear();
                	refresh();
                }
                WINDOW* n_map = map_generator(map1,map2,map3,map4,map5,map6,
                                                map7,map8,map9,map10,seed,false);
                game_flow(y_scr,x_scr,n_map,box,map1,map2,map3,map4,map5,
                            map6,map7,map8,map9,map10,seed,false);
                endwin();
                return;
            }else if(mx==2){
                buyJumpboost(p);
                clear();
                refresh();
                int kek=save_data(p, seed, "savegame.txt" );
                if(kek==1)
                {
                	clear();
                    mvprintw(0, 0, "loading");
                    mvprintw(1, 0, "press a key to continue");
                    refresh();
                    getch();
                    clear();
                    refresh();
                }else
                {
                	clear();
                	mvprintw(0, 0, "error in load screen ");
                    mvprintw(1, 0, "press a key to continue");
                	refresh();
                	getch();
                	clear();
                	refresh();
                }
                WINDOW* n_map = map_generator(map1,map2,map3,map4,map5,map6,
                                                map7,map8,map9,map10,seed,false);
                game_flow(y_scr,x_scr,n_map,box,map1,map2,map3,map4,map5,
                            map6,map7,map8,map9,map10,seed,false);
                endwin();
                return;
            }else{
                clear();
                refresh();
                /*
                 * ottenimento dati del giocatore al momento dell'invocazione del resume
                 *
                 */

                //int py, px, lf, mn;
                int kek=save_data(p, seed, "savegame.txt" );
                if(kek==1)
                    	{
                    		clear();
                    		mvprintw(0, 0, "loading");
                            mvprintw(1, 0, "press a key to continue");
                    		refresh();
                    		getch();
                    		clear();
                    		refresh();
                    	}else
                    	{
                    		clear();
                    		mvprintw(0, 0, "error in load screen ");
                            mvprintw(1, 0, "press a key to continue");
                    		refresh();
                    	    getch();
                    	    clear();
                    	    refresh();
                    	}
                WINDOW* n_map = map_generator(map1,map2,map3,map4,map5,map6,
                                                map7,map8,map9,map10,seed,false);
                game_flow(y_scr,x_scr,n_map,box,map1,map2,map3,map4,map5,
                            map6,map7,map8,map9,map10,seed,false);
                endwin();
                return;
            }
        }
    else if(cx==3){
        //salva partita
    	int kek=save_data(p, seed, "savegame.txt" );
    	if(kek==1)
    	{
    		clear();
    		mvprintw(0, 0, "game saved");
            mvprintw(1, 0, "press a key to exit");
    		refresh();
    		getch();
    	}else
    	{
    		clear();
    		mvprintw(0, 0, "game could not be saved, oopsie :) ");
            mvprintw(1, 0, "press a key to exit");
    		refresh();
    	    getch();
    	}
        endwin();
        return;
    }
}