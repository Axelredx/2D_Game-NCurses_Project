#include "market.hpp"

bool check_Currency(int price, player* player){
    if(price > (player->money))
        return true;
    else
        return false;
}

void buy_Health(player* player){
    if(!check_Currency(player->health_Price, player)){
        player->life=player->life+1;
        player->money=(player->money)-(player->health_Price);
        player->health_Price=player->health_Price+10;
    }
}
void buy_Jumpboost(player* player){
    if(!check_Currency(player->jump_Price, player)){
        (player->jump_width) ++;
        player->money=(player->money)-(player->jump_Price);
        player->jump_Price=player->jump_Price+10;
    }
}

void buy_MagicPotion(player* player){
    if(!check_Currency(player->Potion_Price, player)){
        player->life=player->life+3;
        player->money=(player->money)-(player->Potion_Price);
        player->Potion_Price=player->Potion_Price+10;
    }
}

int buy_Artifact(player* player){
    if(!check_Currency(player->Artifact_Price, player)){
        int score =150;
        player->life=player->life+1;
        player->money=(player->money)-(player->Artifact_Price);
        player->Artifact_Price=player->Artifact_Price+10;
    }
}