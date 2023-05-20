#include "market.hpp"

bool checkCurrency(int price, player* P1){
    if(price > (P1->money))
    {
    	return false;
    }else
    	return true;
}

void buyHealth(player* player){
    if(checkCurrency(player->healthPrice, player)){
        player->life=player->life+1;
        player->money=(player->money)-(player->healthPrice);
        player->healthPrice=player->healthPrice+10;
    }
}
void buyJumpboost(player* player){
    if(checkCurrency(player->jumpPrice, player)){
        (player->salto) ++;
        player->money=(player->money)-(player->jumpPrice);
        player->jumpPrice=player->jumpPrice+10;
    }
}