#include <iostream>
#include <cstring>
#include <ctime>
#include <ncurses.h>
#include "box.hpp"
#include "player.hpp"
using namespace std;

bool check_Currency(int price, player* player);
void buy_Health(player* player);
void buy_Jumpboost(player* player);
void buy_MagicPotion(player* player);
int buy_Artifact(player* player);