#include "box.hpp"
#include <cstring>

WINDOW* BOX::create_box(){
    WINDOW* fin= newwin(height,width,start_y,start_x);
    box(fin, 0,0); //fin, crarattere top-bot, carattere left-right
    refresh();
    wrefresh(fin);
    return fin;
}

WINDOW* BOX::modify_box(char tag[]){
    WINDOW* fin= BOX::create_box();
    mvwprintw(fin, 0,23, tag); //muotagi e stampa in finestra
    wrefresh(fin);
    return fin;
}

int MENU::choice(){
    WINDOW* fin= BOX::modify_box(tag);
    mvwprintw(fin,1,1,tag2);
    mvwprintw(fin,4,1,tag3);
    mvwprintw(fin,7,1,tag4);
    int input_choice=-1;

    char c;
    while(c=wgetch(fin)){
        if(c=='1'){
                wattron(fin, A_STANDOUT);//evidenzia
                mvwprintw(fin,1,1,tag2); 
                wattroff(fin, A_STANDOUT);//toglie la selez
                mvwprintw(fin,7,1,tag4); 
                mvwprintw(fin,4,1,tag3);
                if(wgetch(fin)==' '){
                    input_choice=1;            
                    clear();
                    return(input_choice);
                }
        }
        else if(c=='2'){
                wattron(fin, A_STANDOUT);
                mvwprintw(fin,4,1,tag3); 
                wattroff(fin, A_STANDOUT);
                mvwprintw(fin,7,1,tag4); 
                mvwprintw(fin,1,1,tag2);
                if(wgetch(fin)==' '){
                    input_choice=2;
                    clear();
                    return(input_choice);
                }
        }
        else if(c=='3'){
                wattron(fin, A_STANDOUT);
                mvwprintw(fin,7,1,tag4); 
                wattroff(fin, A_STANDOUT);
                mvwprintw(fin,1,1,tag2);
                mvwprintw(fin,4,1,tag3);
                if(wgetch(fin)==' '){
                    input_choice=3;
                    clear();
                    return(input_choice);
                } 
        }   
        else
            mvwprintw(fin,1,1,tag2);
            mvwprintw(fin,4,1,tag3);
            mvwprintw(fin,7,1,tag4);              
        }
}

WINDOW* MAP::create_map(){
    WINDOW* fin=BOX::create_box();
    mvwprintw(fin,22,1,"[]");
    mvwprintw(fin,22,width-3,"()");
    if(holes_on==true){
        for(int i=0;i<width;i++){
            for(int j=0;j<height;j++){
                if(j>=23){
                    if(i<x1_hole || i>x2_hole)
                        if(two_holes==true)
                            if(i<x3_hole || i>x4_hole)
                                mvwprintw(fin,j,i,"#");
                }
            }
        }
    }
    //fare scale
    refresh();
    box(fin,0,0);
    wrefresh(fin);
    return fin;
}