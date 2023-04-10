#include <iostream>
#include <cstring>
#include <ctime>
#include <ncurses.h>
#include "box.hpp"
#include "player.hpp"
using namespace std;

bool checkCurrency(int price, player* player);
void buyHealth(player* player);
void buyJumpboost(player* player);
