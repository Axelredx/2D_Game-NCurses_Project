#include "gameEngine.hpp"
typedef void * (*THREADFUNCPTR)(void *);
//player score
int game_scr = 0;

void initialize(){
    initscr(); //initialization of screen and memory
    refresh(); //refresh screen to be compatible with what is in memory
    noecho(); //prevents user to write on screen
    curs_set(false); //cursor hider
}

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
    mvwprintw(fin,y_scr/4,(x_scr/4)-4,"YOU DIED");
    mvwprintw(fin,(y_scr/4)+1,(x_scr/4)-6,"Your SCORE: %d", game_scr);
    mvwprintw(fin,(y_scr/4)+2,(x_scr/4)-10," press a key to exit");
    refresh();
    wrefresh(fin);
    getch();
    clear();
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
                class MAP map9, class MAP map10, int seed, bool new_lvl, 
                bool last_lvl, bool first_lvl){
    srand(time(0));

	//FOLLOWING: default values for creating player-class items
	int player_x=4, player_y=15, money=100, life=3, jump_w=10, mapSeed=0;

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

            getline(savegame, lel, '#');		//check for saving of the score
            if(lel.compare("score")==0)
            {
                getline(savegame, lel, '\n');
                game_scr=stoi(lel);
            }


            savegame.close();
	    }

    //set position of player if there was savefile and proceed in a new level
    if(new_lvl==true){
        player_x=6;
	    player_y=22;
    }

    if(last_lvl==true){
        player_x=114;
	    player_y=22;
    }

    player * p = new player(map, player_y, player_x, 'P', money, life);
        //(win, y spawn of player, x spawn of player, player icon)

    p->jump_width=jump_w;
    //sintax: (win, y spawn of enemy, x spawn of enemy,
    //             enemy life, enemy icon, money given if defeated)
	basicenemy * e1 = new basicenemy(map, 15, 25, 1, 'e', 50);

	basicenemy * e2 = new basicenemy(map, 15, 35, 1, 'j', 50);

	basicenemy * e3 = new basicenemy(map, 15, 65, 3, '<', 80);

    //sintax: (win, y spawn of enemy, x spawn of enemy,
    //             enemy life, enemy icon, money given if defeated, difficulty of enemy)
    //Lower the number higher is the difficulty! (don't use neg. number; 
    //seggest to not be lower than 3 
	jumpingenemy * e4 = new jumpingenemy (map, 15, 95, 3, 'E', 100, 4);

	//player and enemy initialization
	pthread_t playerthread, enemythread;

	basicenemy* enemyEntity;	
    basicenemy* b_e;
    jumpingenemy* j_e=jumping_enemy_randomizer(e4);
    if(j_e==NULL){
    	b_e=basic_enemy_randomizer(e1,e2,e3);
    	enemyEntity= b_e;
    }else
    	enemyEntity= j_e;
    //prevents infinite money
    int count_money=0;
    //counter if enemy is dead
    bool dead_enemy=false;
	do{
        //brak if life below 0 or if player is prepared to go to next lvl
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
        remove("savegame.txt");

        //exit if you press "Esc"
	}while(p->move()!=27);

    //entrance in new level
    if(p->playeroutput(1)>=116){
        clear();
        refresh();
        //reward for passing lvl
        game_scr+=100;
        int seed_generated=map_randomizer(map1,map2,map3,map4,map5,map6,map7,
                                               map8,map9,map10,seed,true);
        WINDOW* new_map = map_generator(map1,map2,map3,map4,map5,map6,
                                        map7,map8,map9,map10,seed_generated,false);
        if (j_e==NULL)
        	{
        		save_data(p, seed_generated, game_scr, "savegame.txt","b_e", b_e);
        	}else
        	{
        		save_data(p, seed_generated, game_scr, "savegame.txt","j_e", j_e);
        	}
        game_flow(y_scr,x_scr,new_map,box,map1,map2,map3,map4,map5,
                    map6,map7,map8,map9,map10,seed_generated,true,false,false);
        endwin();
        return;
    }

    //entrance last level
    if(p->playeroutput(1)<4 && !first_lvl){
        clear();
        refresh();
        if(seed==1)
            seed=10;
        else    
            seed=seed-1;
        WINDOW* n_map = map_generator(map1,map2,map3,map4,map5,map6,
                                            map7,map8,map9,map10,seed,false);
        if (j_e==NULL)
        	{
        		save_data(p, seed, game_scr, "savegame.txt","b_e", b_e);
        	}else
        	{
        		save_data(p, seed, game_scr, "savegame.txt","j_e", j_e);
        	}
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
        endwin();
        return;
    }

    char v1[20], v2[20], v3[20], v4[20];
        strcpy(v1,"Menu");
        strcpy(v2,"Resume");
        strcpy(v3,"Market");
        strcpy(v4,"Save and exit");

    MENU menu(y_scr/2,x_scr/2,y_scr/4,x_scr/4,v1,v2,v3,v4);

    char v5[20], v6[50], v7[50], v8[50], v9[50], v10[20], v1_power[50], v2_power[50];
        strcpy(v5,"Market");
        strcpy(v6,"Health boost 80$");
        strcpy(v7,"Jump boost 50$");
        strcpy(v8,"Magic Potion 120$");
        strcpy(v9,"Artifact 180$");
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
                if (j_e==NULL)
                {
                	kek=save_data(p, seed, game_scr, "savegame.txt","b_e", b_e);
                }else
                {
                	kek=save_data(p, seed, game_scr, "savegame.txt","j_e", j_e);
                }
            if(kek==1){
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
                if (j_e==NULL)
                {
                	kek=save_data(p, seed, game_scr, "savegame.txt","b_e", b_e);
                }else
                {
                	kek=save_data(p, seed, game_scr, "savegame.txt","j_e", j_e);
                }
                if(kek==1){
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
                if (j_e==NULL)
                {
                	kek=save_data(p, seed, game_scr, "savegame.txt","b_e", b_e);
                }else
                {
                	kek=save_data(p, seed, game_scr, "savegame.txt","j_e", j_e);
                }
                if(kek==1){
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
                if (j_e==NULL)
                {
                	kek=save_data(p, seed, game_scr, "savegame.txt","b_e", b_e);
                }else
                {
                	kek=save_data(p, seed, game_scr, "savegame.txt","j_e", j_e);
                }
                if(kek==1){
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
        if (j_e==NULL)
        {
        	kek=save_data(p, seed, game_scr, "savegame.txt","b_e", b_e);
        }else
        {
        	kek=save_data(p, seed, game_scr, "savegame.txt","j_e", j_e);
        }
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
    		refresh();
    	    getch();
    	}
        endwin();
        return;
    }
}