#include "box.hpp"

WINDOW* BOX::create_box(){
    WINDOW* fin= newwin(height,width,start_y,start_x);
    box(fin, 0,0); //fin, crarattere top-bot, carattere left-right
    refresh();
    wrefresh(fin);
    return fin;
}

WINDOW* BOX::modify_box(char tag[]){
    WINDOW* fin= BOX::create_box();
    mvwprintw(fin, 0,23, tag); //muovi e stampa in finestra
    wrefresh(fin);
    return fin;
}

int MENU::choice(){
    WINDOW* fin= BOX::modify_box(tag);
    keypad(fin,true);
    string choice[3]{tag2,tag3,tag4};
    int user_typing, h_light=0, exit_value;
    bool found=false;

    while(1 && !found){
        for(int i=0;i<3;i++){
            if(i==h_light){
                wattron(fin,A_REVERSE);
            }
            mvwprintw(fin,i+1,1,choice[i].c_str());
            wattroff(fin,A_REVERSE);
        }
        user_typing=wgetch(fin);

        if(user_typing==KEY_UP){
            h_light--;
            if(h_light==-1)
                h_light=0;    
        }else if(user_typing==KEY_DOWN){
            h_light++;
            if(h_light==3)
                h_light=2;
        }
        if(user_typing=='k'){
            found=true;
            clear();
            exit_value=h_light+1;
        }
    }
    return exit_value;
}

void MARKET::draw_market(){
    mvprintw(3,80,"////// MARKET //////");
    mvprintw(4,80," | (Buy or )      | ");
    mvprintw(5,80," |  ( Die! )      | ");
    mvprintw(6,80," |        O       | ");
    mvprintw(7,80," |       /||      | ");
    mvprintw(8,80,"####################");
    mvprintw(9,80,"####################");
    mvprintw(10,80,"####################");
    refresh();
}

WINDOW* MAP::create_map(){
    WINDOW* fin=BOX::create_box();
    string map_seed_str= to_string(map_seed);
    mvprintw(0, 0, "mappa: %s", map_seed_str.c_str());
    mvwprintw(fin,22,1,"[]");
    mvwprintw(fin,22,width-3,"{}");
    //buchi nella mappa
    for(int i=0;i<width;i++){
        for(int j=0;j<height;j++){
            if(j>=23){
                if(holes_on==true){
                    if(i<x1_hole_start || i>x1_hole_finish)
                        if(two_holes==true){
                            if(i<x2_hole_start || i>x2_hole_finish)
                                mvwprintw(fin,j,i,"#");
                            }else{
                                mvwprintw(fin,j,i,"#");
                            }
                }else{
                    mvwprintw(fin,j,i,"#");
                }
            }
        }
    }
    
    //scale
    if(ladder_on==true){
        for(int i=0;i<width;i++){
            for(int j=0;j<height;j++){
                if(two_ladders==true){
                    if(i==x1_hole_start || i==x2_hole_start){
                        if(j>=18 && j<23){
                            mvwprintw(fin,j-1,i-3,"|");
                            mvwprintw(fin,j,i-2,"-");
                            mvwprintw(fin,j-1,i-1,"|");

                            mvwprintw(fin,j-1,i+10,"|");
                            mvwprintw(fin,j,i+11,"-");
                            mvwprintw(fin,j-1,i+12,"|");
                        }
                        mvwprintw(fin,17,i,"##########");
                        mvwprintw(fin,17,i-2,"-");
                        mvwprintw(fin,17,i+11,"-");
                    }
                }else{
                    if(i==x1_hole_start){
                        if(j>=18 && j<23){
                            mvwprintw(fin,j-1,i-3,"|");
                            mvwprintw(fin,j,i-2,"-");
                            mvwprintw(fin,j-1,i-1,"|");

                            mvwprintw(fin,j-1,i+10,"|");
                            mvwprintw(fin,j,i+11,"-");
                            mvwprintw(fin,j-1,i+12,"|");
                        }
                        mvwprintw(fin,17,i,"##########");
                        mvwprintw(fin,17,i-2,"-");
                        mvwprintw(fin,17,i+11,"-");
                    }
                }
            }
        }
    }

    //decorations
    if(cloud==true){
        //clouds
        mvwprintw(fin,3,7,".°(||)°.");
        mvwprintw(fin,4,6,"((((||))))");
        mvwprintw(fin,5,6,"((((||))))");
        mvwprintw(fin,6,7,"'°(||)°'");

        mvwprintw(fin,4,33,".°(||)°.");
        mvwprintw(fin,5,32,"((((||))))");
        mvwprintw(fin,6,32,"((((||))))");
        mvwprintw(fin,7,33,"'°(||)°'");

        mvwprintw(fin,3,63,".°(||)°.");
        mvwprintw(fin,4,62,"((((||))))");
        mvwprintw(fin,5,62,"((((||))))");
        mvwprintw(fin,6,63,"'°(||)°'");
    }else if(cloud == false && day == false){
        //stars
        mvwprintw(fin,3,90,"*");
        mvwprintw(fin,6,50,"*");
        mvwprintw(fin,8,30,"*");
        mvwprintw(fin,10,80,"*");
    }else if (cloud ==false && day ==true){
        //pigeons
        mvwprintw(fin,3,90,"^-^");
        mvwprintw(fin,6,50,"^-^");
        mvwprintw(fin,8,30,"^-^");
        mvwprintw(fin,10,80,"^-^");       
    }

    if(day==true){
        //sun
        mvwprintw(fin,2,102,">ççç<");
        mvwprintw(fin,3,100,">ççççççç<");
        mvwprintw(fin,4,99,">ççççççççç<");
        mvwprintw(fin,5,99,">ççççççççç<");
        mvwprintw(fin,6,100,">ççççççç<");
        mvwprintw(fin,7,102,">ççç<");
    }else{
        //moon
        mvwprintw(fin,2,100,"+,");
        mvwprintw(fin,3,101,"]!}");
        mvwprintw(fin,4,101,";çç}");
        mvwprintw(fin,5,101,"çççç}");
        mvwprintw(fin,6,101,"ççç}*");
        mvwprintw(fin,7,100,";]}}'");
        mvwprintw(fin,8,99,"+**");
    } 


    refresh();
    box(fin,0,0);
    wrefresh(fin);
    return fin;
}