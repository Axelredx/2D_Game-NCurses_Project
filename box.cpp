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
    mvwprintw(fin, 0,23, tag); //muovi e stampa in finestra
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
                            mvwprintw(fin,j,i-3,"|");
                            mvwprintw(fin,j,i-2,"-");
                            mvwprintw(fin,j,i-1,"|");

                            mvwprintw(fin,j,i+10,"|");
                            mvwprintw(fin,j,i+11,"-");
                            mvwprintw(fin,j,i+12,"|");
                        }
                        mvwprintw(fin,18,i,"##########");
                    }
                }else{
                    if(i==x1_hole_start){
                        if(j>=18 && j<23){
                            mvwprintw(fin,j,i-3,"|");
                            mvwprintw(fin,j,i-2,"-");
                            mvwprintw(fin,j,i-1,"|");

                            mvwprintw(fin,j,i+10,"|");
                            mvwprintw(fin,j,i+11,"-");
                            mvwprintw(fin,j,i+12,"|");
                        }
                        mvwprintw(fin,18,i,"##########");
                    }
                }
            }
        }
    }

    //decorations
    if(cloud==true){
        //nuvole
        mvwprintw(fin,3,4,".°(||)°.");
        mvwprintw(fin,4,3,"((((||))))");
        mvwprintw(fin,5,3,"((((||))))");
        mvwprintw(fin,6,4,"'°(||)°'");

        mvwprintw(fin,4,33,".°(||)°.");
        mvwprintw(fin,5,32,"((((||))))");
        mvwprintw(fin,6,32,"((((||))))");
        mvwprintw(fin,7,33,"'°(||)°'");

        mvwprintw(fin,3,63,".°(||)°.");
        mvwprintw(fin,4,62,"((((||))))");
        mvwprintw(fin,5,62,"((((||))))");
        mvwprintw(fin,6,63,"'°(||)°'");
    }

    if(day==true){
        //sole
        mvwprintw(fin,2,102,">ççç<");
        mvwprintw(fin,3,100,">ççççççç<");
        mvwprintw(fin,4,99,">ççççççççç<");
        mvwprintw(fin,5,99,">ççççççççç<");
        mvwprintw(fin,6,100,">ççççççç<");
        mvwprintw(fin,7,102,">ççç<");
    }else{
        //luna
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