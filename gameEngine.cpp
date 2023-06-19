#include "gameEngine.hpp"
typedef void * (*THREADFUNCPTR)(void *);
//player game score
int game_scr = 0;

ofstream LOGFILE;

void initialize(){
    initscr(); //initialization of screen and memory
    refresh(); //refresh screen to be compatible with what is in memory
    noecho(); //prevents writing on screen
    curs_set(false); //cursor hider

    LOGFILE.open("LOGFILE.txt");
    LOGFILE << "INITIALIZING" << endl;
}

void pregame(class BOX box, int y_scr, int x_scr){
	LOGFILE << "PREGAME PHASE BEGINNING" << endl;
    WINDOW* fin=box.create_box();
    mvwprintw(fin,y_scr/4,(x_scr/4)-3,"THE GAME");
    mvwprintw(fin,(y_scr/4)+1,(x_scr/4)-10,"press a key to start");
    refresh();
    wrefresh(fin);
    getch();
    clear();
    LOGFILE << "PREGAME PHASE: COMPLETE" << endl;
}

void death_screen(class BOX box, int y_scr, int x_scr, class MAP map1, class MAP map2, class MAP map3, class MAP map4,
                       class MAP map5, class MAP map6, class MAP map7, class MAP map8,
                       class MAP map9, class MAP map10, int seed){
	LOGFILE << "DEATHSCREEN PROCESS BEGINNING" << endl;
    WINDOW* fin=box.create_box();
    mvwprintw(fin,y_scr/4,(x_scr/4)-4,"YOU DIED");
    mvwprintw(fin,(y_scr/4)+1,(x_scr/4)-6,"Your SCORE: %d", game_scr);
    mvwprintw(fin,(y_scr/4)+2,(x_scr/4)-10," press a key to exit");
    refresh();
    wrefresh(fin);
    usleep(3000);
    getch();
    clear();
    LOGFILE << "DEATHSCREEN PROCESS ENDED WITHOUT PROBLEMS" << endl;
    return;
}

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
            int result=rand()%10;
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
            else if(seed==10)
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
                class MAP map9, class MAP map10, int seed, bool new_lvl, bool last_lvl, bool first_lvl ){
	LOGFILE << "NEW ISTANCE OF GAMEFLOW BEGINNING" << endl;
    srand(time(0));
    int player_x, player_y, money, life, jump_w=10, mapSeed = 0;

	//FOLLOWING: default values for creating player-class items
	player_x=4;
	player_y=15;
	money=100;
	life=3;
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

            getline(savegame, lel, '#');		//check for seed of Map
            if(lel.compare("map")==0)
            {
                getline(savegame, lel, '\n');
                mapSeed=stoi(lel);
            }

            getline(savegame, lel, '#');		//check for saving the score
            if(lel.compare("score")==0)
            {
                getline(savegame, lel, '\n');
                game_scr=stoi(lel);
            }


            savegame.close();
	    }

        LOGFILE << "player data succesfully retrieved" << endl;

    //set position of player if there was savefile and proceed in a new level
    if(new_lvl==true){
        player_x = 4;
	    player_y = 22;
    }

    if(last_lvl == true){
    	player_x = 114;
    	player_y = 22;
    }

    player * p = new player(map, player_y, player_x, 'P', money, life);
        //(finestra, y da cui il personagio spawna,
        //x da cui il personaggio spawna, icona del personaggio)

    p->jump_width = jump_w;
    //sintassi: (finestra, y dello spawn del nemico, x dello spawn del nemico,
    //              vita del nemico, icona del nemico (lasciala 'e'), soldi rilasciati alla morte)
	basicenemy * e1 = new basicenemy(map, 15, 73, 1, 'e', 50);

	basicenemy * e2 = new basicenemy(map, 15, 73, 1, 'e', 50); //'j'

	basicenemy * e3 = new basicenemy(map, 15, 73, 3, 'e', 80);//'<'

	//check per vedere se il nemico è già stato avvistato in passato

	//sintassi: (finestra, y dello spawn del nemico, x dello spawn del nemico, vita del nemico,
    //              icona del nemico , soldi rilasciati alla morte, difficoltà del nemico)
    //PIU IL NUMERO E' BASSO PIU E' DIFFICILE! (non usare numeri negativi;
    //sconsiglio di scendere sotto a 3)
	jumpingenemy * e4 = new jumpingenemy (map, 15, 73, 3, 'e', 100, 4);//'E'

	//player and enemy initialization
	pthread_t playerthread, enemythread;
	basicenemy* b_e;
	jumpingenemy* j_e=jumping_enemy_randomizer(e4);

	basicenemy* enemyEntity;	//ottiene la classe padre dei nemici per salvataggi

	LOGFILE << "call to obtain_data for creation of an enemy entity (currentyl jumped)" << endl;
	/*if(obtain_data(2, seed) > 0 && obtain_data(1, seed) != -6)	//controlla se esistono dati riguardanti il nemico del livello
	{
		if(obtain_data(4, seed) == (int)'E')				//se il nemico è un Jumping Enemy
		{
			enemyEntity = new jumpingenemy (map, 15, obtain_data(1, seed) , obtain_data(2, seed), 'E', 100, 4);
		}else
		{
			enemyEntity = new basicenemy (map, 15, obtain_data(1, seed) , obtain_data(2, seed), obtain_data(4, seed), obtain_data(3, seed));
		}
		LOGFILE << "call ended without complications, data retrieved from savefile" << endl ;
	}		//se non sono presenti dati riguardanti il nemico, passa alla creazione da zero
	else{*/
		 if(j_e==NULL){
			 b_e=basic_enemy_randomizer(e1,e2,e3);
			 enemyEntity= b_e;
		 }else
			 enemyEntity= j_e;

		 LOGFILE << "call yielded negative result, loading enemy with basic creation" << endl;
	//}
    //prevents infinite money
    int count_money=0;
    //counter if enemy is dead


    bool dead_enemy=false;
    if(enemyEntity->enemyOutput(2) <=0)
    	dead_enemy=true;

    int sus;

    LOGFILE << "preparing to save data for new instance of gameFlow:-->" ;	//salva per aggiornare i dati all'entrata nel nuovo livello
    sus=save_data(p, seed, game_scr, "savegame.txt", enemyEntity);
    LOGFILE << "	automatic savegame complete. Enemy type: " << (char)obtain_data(4, seed) << endl ;

    if(sus!=-1){
    	LOGFILE <<"process ended without any error with status = " << sus << endl;;
    }else{
    	LOGFILE << "process ended with error, code = " << sus << endl;
    }

	do{
        //brak if life below 0 or if player is prepared to go to next lvl or previous
        if(p->life<=0 || p->playeroutput(1)>116 || (p->playeroutput(1)<4 && !first_lvl))
            break;

		//Player thread creation
		pthread_create(&playerthread, NULL, (THREADFUNCPTR) &player::display, p);
		//elabouring thread
		pthread_join(playerthread, NULL);

        //Enemy thread creation
        if(j_e==NULL){
            pthread_create(&enemythread, NULL, (THREADFUNCPTR) &basicenemy::behaviour, b_e);
            pthread_join(enemythread, NULL);
            //reward killing basic enemy
            if(b_e->life==0 && count_money==0){
                dead_enemy=true;
                game_scr+=40;
                p->money=p->money+b_e->money;
                count_money++;
            }
        }else{
            pthread_create(&enemythread, NULL, (THREADFUNCPTR) &jumpingenemy::behaviour, j_e);
            pthread_join(enemythread, NULL);
            //reward killing jumping enemy
            if(j_e->life==0 && count_money==0){
                dead_enemy=true;
                game_scr+=60;
                p->money=p->money+j_e->money;
                count_money++;
            }
        }

        mvwprintw(map, 0, (x_scr/4)+5, "SCORE: %d", game_scr);

		refresh();
		wrefresh(map);

        //prevents having conflicts between savings
        //remove("savegame.txt");

        //exit if you press "Esc"
	}while(p->move()!=27);

	/*int sadness = save_data(p, seed, game_scr, "savegame.txt","b_e", b_e);
	LOGFILE << "end of action savegame result = " << sadness << endl;
*/
    //entrance in new level
    if(p->playeroutput(1)>=116){
        clear();
        refresh();
        //reward for passing lvl
        game_scr+=100;
        int kek=0;
        int seed_generated=map_randomizer(map1,map2,map3,map4,map5,map6,map7,
                                               map8,map9,map10,seed,true);
        WINDOW* new_map = map_generator(map1,map2,map3,map4,map5,map6,
                                        map7,map8,map9,map10,seed_generated,false);
        LOGFILE << "preparing to save data for new level entrance:-->" ;

        kek=save_data(p, seed_generated, game_scr, "savegame.txt", enemyEntity);
        LOGFILE << "	automatic savegame complete (b_e)" << endl;

        if(kek!=-1){
        	LOGFILE << "successful operation" << endl;
        }else
        	LOGFILE << "operation failed and returned error code " << kek << endl;

        //DEVNOTE
        /*
         * per qualche ragione, mettere qualunque istruzione fuori dall'if soprastante, prima dell'avvio di gameflow, rompe la creazione della mappa
         * la mappa creata è quella corretta, difatti mettendo in pausa e cliccando resume, tutto torna come dovrebbe essere, eppure, eccoci qua
         * non ho idea del perché succeda, ma oggi, nella sfida tra uomo e macchina, ha vinto la macchina
         */
        game_flow(y_scr,x_scr,new_map,box,map1,map2,map3,map4,map5,
                    map6,map7,map8,map9,map10,seed_generated,true,false,false);
        endwin();
        return;
    }

    //entrance in previous level
    if(p->playeroutput(1) < 4 && !first_lvl)
    {
    	clear();
    	refresh();
        if(seed==1)
            seed=10;
        else    
            seed=seed-1;
        WINDOW* n_map = map_generator(map1,map2,map3,map4,map5,map6,
                                            map7,map8,map9,map10,seed,false);
    		save_data(p, seed, game_scr, "savegame.txt", enemyEntity);

            game_flow(y_scr,x_scr,n_map,box,map1,map2,map3,map4,map5,
                        map6,map7,map8,map9,map10,seed,false,true,first_lvl);
    	endwin();
    	return;
    }

    //death of player
    if(p->life<=0){
        clear();
        refresh();
        death_screen(box,y_scr,x_scr,map1,map2,map3,map4,map5,map6,map7,
                        map8,map9,map10,seed);
        remove("savegame.txt");
        LOGFILE << "player death, removing savegame.txt" << endl;
        LOGFILE.close();
        endwin();
        return;
    }

    char v1[20], v2[20], v3[20], v4[20];
        strcpy(v1,"Menu");
        strcpy(v2,"Resume");
        strcpy(v3,"Market");
        strcpy(v4,"Save and exit");

    MENU menu(y_scr/2,x_scr/2,y_scr/4,x_scr/4,v1,v2,v3,v4);

    char v5[20], v6[20], v7[20], v8[20], v9[50], v10[50], v1_power[50], v2_power[50];
        strcpy(v5,"Market");
        strcpy(v6,"Health boost 80$+");
        strcpy(v7,"Jump boost 50$+");
        strcpy(v8,"Magic Potion 120$+");
        strcpy(v9,"Artifact 180$+");
        strcpy(v10,"Return to the game");

        //upgrade randomized
        int upgrade_rand=rand()%3;
        if(upgrade_rand%2==0)
        	strcpy(v1_power,v6);
        else
        	strcpy(v1_power,v8);

        if(upgrade_rand==1)
        	strcpy(v2_power,v9);
        else
        	strcpy(v2_power,v7);

        MARKET market(y_scr/2,x_scr/4,y_scr/4,x_scr/4,v5,v1_power,v2_power,v10);

        clear();
        refresh();

        int cx=menu.choice();
    if(cx==1){
            clear();
            refresh();
            int kek;
            LOGFILE << "preparing to save data for resume:-->" ;

            kek=save_data(p, seed, game_scr, "savegame.txt", enemyEntity);
            LOGFILE << "	automatic save complete (b_e) " << endl;

            LOGFILE << "operation yielded result: " << kek<< endl;
            if(kek!=-1){
                clear();
                mvprintw(0, 0, "loading");
                mvprintw(1, 0, "press a key to continue");
                refresh();
                getch();
                clear();
                refresh();
            }else{
                clear();
                mvprintw(0, 0, "error in load screen ");
                mvprintw(1, 0, "press a key to continue");
                LOGFILE << "error during resume operation, code: " << kek;
                refresh();
                getch();
                clear();
                refresh();
            }
            WINDOW* n_map = map_generator(map1,map2,map3,map4,map5,map6,
                                            map7,map8,map9,map10,seed,false);
            game_flow(y_scr,x_scr,n_map,box,map1,map2,map3,map4,map5,
                        map6,map7,map8,map9,map10,seed,false,false,first_lvl);
            endwin();
            return;
    }else if(cx==2){
    	//market access
    	market.draw_market();
    	int mx=market.choice();
    	if(mx==1){
    		//upgrade randomized
    		if(upgrade_rand%2==0)
    			buy_Health(p);
    		else
    			buy_MagicPotion(p);
    		clear();
    		refresh();
    		int kek;
    		LOGFILE << "preparing to save data for access to market:-->" ;

    		kek=save_data(p, seed, game_scr, "savegame.txt", enemyEntity);

    		LOGFILE << "operation yielded result: " << kek<< endl;

                if(kek!=1){
                	clear();
                	mvprintw(0, 0, "loading");
                    mvprintw(1, 0, "press a key to continue");
                	refresh();
                	getch();
                	clear();
                	refresh();
                }else{
                	clear();
                	mvprintw(0, 0, "error in load screen ");
                    mvprintw(1, 0, "press a key to continue");
                    LOGFILE << "error during health purchase, code: " << kek;
                	refresh();
                	getch();
                	clear();
                	refresh();
                }
                WINDOW* n_map = map_generator(map1,map2,map3,map4,map5,map6,
                                                map7,map8,map9,map10,seed,false);
                game_flow(y_scr,x_scr,n_map,box,map1,map2,map3,map4,map5,
                            map6,map7,map8,map9,map10,seed,false,false,first_lvl);
                endwin();
                return;
            }else if(mx==2){
            	//upgrade randomized
            	if(upgrade_rand==1)
            		game_scr+=buy_Artifact(p);
            	else
            		buy_Jumpboost(p);
            	clear();
            	refresh();
                int kek;
                LOGFILE << "preparing to save data for access to market:-->" ;

                kek=save_data(p, seed, game_scr, "savegame.txt", enemyEntity);

                LOGFILE << "operation yielded result: " << kek<< endl;

                if(kek!=1){
                	clear();
                    mvprintw(0, 0, "loading");
                    mvprintw(1, 0, "press a key to continue");
                    refresh();
                    getch();
                    clear();
                    refresh();
                }else{
                	clear();
                	mvprintw(0, 0, "error in load screen ");
                    mvprintw(1, 0, "press a key to continue");
                    LOGFILE << "error during jumpboost purchase, code: " << kek;
                	refresh();
                	getch();
                	clear();
                	refresh();
                }
                WINDOW* n_map = map_generator(map1,map2,map3,map4,map5,map6,
                                                map7,map8,map9,map10,seed,false);
                game_flow(y_scr,x_scr,n_map,box,map1,map2,map3,map4,map5,
                            map6,map7,map8,map9,map10,seed,false,false,first_lvl);
                endwin();
                return;
            }else{
                clear();
                refresh();
                /*
                 * giving back player data after resume
                 *
                 */
                int kek;
                LOGFILE << "preparing to save data for resume function:-->" ;

                	kek=save_data(p, seed, game_scr, "savegame.txt", enemyEntity);

                LOGFILE << "	operation yielded result:  " << kek << endl;
                if(kek!=1){
            		clear();
            		mvprintw(0, 0, "loading");
                    mvprintw(1, 0, "press a key to continue");
            		refresh();
            		getch();
            		clear();
            		refresh();
            	}else{
                	clear();
            		mvprintw(0, 0, "error in load screen ");
                    mvprintw(1, 0, "press a key to continue");
                    LOGFILE << "error during resume, code: " << kek;
                    refresh();
            	    getch();
            	    clear();
            	    refresh();
            	}
            WINDOW* n_map = map_generator(map1,map2,map3,map4,map5,map6,
                                            map7,map8,map9,map10,seed,false);
            game_flow(y_scr,x_scr,n_map,box,map1,map2,map3,map4,map5,
                        map6,map7,map8,map9,map10,seed,false,false,first_lvl);
            endwin();
            return;
            }
    }else if(cx==3){
        //save game
        int kek;
        LOGFILE << "preparing to save data throught savedata manual command: -->" ;

        	kek=save_data(p, seed, game_scr, "savegame.txt", enemyEntity);

        LOGFILE << "operation yielded result: "<< kek << endl;

    	if(kek!=-1)
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
            LOGFILE << "error during savegame, code: " << kek;
    		refresh();
    	    getch();
    	}
        endwin();
        LOGFILE.close();
        return;
    }
}