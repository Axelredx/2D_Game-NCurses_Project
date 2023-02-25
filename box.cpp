#include "box.hpp"
#include <cstring>

WINDOW* BOX::create_box(){
    WINDOW* fin= newwin(height,width,start_y,start_x);
    box(fin, 0,0); //fin, crarattere top-bot, carattere left-right
    refresh();
    wrefresh(fin);
    return fin;
}

WINDOW* BOX::modify_box(char v[]){
    WINDOW* fin= BOX::create_box();
    mvwprintw(fin, 0,23, v); //muovi e stampa in finestra
    wrefresh(fin);
    return fin;
}

int MENU::choice(){
    WINDOW* fin= BOX::modify_box(v);
    mvwprintw(fin,1,1,v2);
    mvwprintw(fin,4,1,v3);
    mvwprintw(fin,7,1,v4);
    int input_choice=-1;

    char c;
    while(c=wgetch(fin)){
        switch(c){
            case 's':
                wattron(fin, A_STANDOUT);//evidenzia
                mvwprintw(fin,1,1,v2); 
                wattroff(fin, A_STANDOUT);//toglie la selez
                mvwprintw(fin,7,1,v4); 
                mvwprintw(fin,4,1,v3);
                if(c==' '){
                    input_choice=1;
                }
            break;
            case 'm':
                wattron(fin, A_STANDOUT);
                mvwprintw(fin,4,1,v3); 
                wattroff(fin, A_STANDOUT);
                mvwprintw(fin,7,1,v4); 
                mvwprintw(fin,1,1,v2);
                if(c==' '){
                    input_choice=2;
                }
            break;
            case 'e':
                wattron(fin, A_STANDOUT);
                mvwprintw(fin,7,1,v4); 
                wattroff(fin, A_STANDOUT);
                mvwprintw(fin,1,1,v2);
                mvwprintw(fin,4,1,v3);
                if(c==' '){
                    input_choice=3;
                }    
            break;
            default:
            mvwprintw(fin,1,1,v2);
            mvwprintw(fin,4,1,v3);
            mvwprintw(fin,7,1,v4); 
            break;              

        }
        if(c==' '){
            clear();
            return(input_choice);
        }
    }
}