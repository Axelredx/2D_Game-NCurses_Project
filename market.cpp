#include "market.hpp"

bool checkCurrency(int price, player* player){
    if(price < player->money)
        return false;
    else 
        return true;
}

void buyHealth(player* player){
    if(checkCurrency(player->healthPrice, player)){
        player->life=player->life+1;
        player->money=player->money-player->healthPrice;
        player->healthPrice=player->healthPrice+10;
    }
}
void buyJumpboost(player* player){
    if(checkCurrency(player->jumpPrice, player)){
        player->salto=player->salto+1;
        player->salto=player->salto-player->healthPrice;
        player->jumpPrice=player->jumpPrice+10;
    }
}