#include "dataManager.hpp"	//includes basicEnem.hpp and market.hpp, which includes player.hpp and box.hpp

//screen initzialization
void initialize();
//initail screen
void pregame(class BOX box, int y_scr, int x_scr);
//death screen
void death_screen(class BOX box, int y_scr, int x_scr, class MAP map1, class MAP map2, class MAP map3, class MAP map4,
                       class MAP map5, class MAP map6, class MAP map7, class MAP map8,
                       class MAP map9, class MAP map10, int seed);
//return a random seed from a map
int map_randomizer(class MAP map1, class MAP map2, class MAP map3, class MAP map4,
                       class MAP map5, class MAP map6, class MAP map7, class MAP map8,
                       class MAP map9, class MAP map10, int prev_seed, bool next_seed);
//return the map pointer based on seed
WINDOW* map_generator(class MAP map1, class MAP map2, class MAP map3, class MAP map4,
                       class MAP map5, class MAP map6, class MAP map7, class MAP map8,
                       class MAP map9, class MAP map10, int seed, bool nxt_lvl);
//game engine
void game_flow(int y_scr, int x_scr, WINDOW* map, class BOX box,
                class MAP map1, class MAP map2, class MAP map3, class MAP map4,
                class MAP map5, class MAP map6, class MAP map7, class MAP map8,
                class MAP map9, class MAP map10, int seed, bool new_lvl, bool last_lvl, bool first_lvl);
