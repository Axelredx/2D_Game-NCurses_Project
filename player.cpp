
#include "player.hpp"

player::player(WINDOW * win, int y, int x, char c){			//Costruttore della classe
	curwin = win;
	yLoc=y;
	xLoc = x;
	originy=y;
	originx=x;
	getmaxyx(curwin, yMax, xMax);
	keypad(curwin, true);
	character=c;
	dir=2;
	life=3;
	mvwprintw(curwin, 0, 0,"HP: %d", life);					//Stampa la vita del personaggio
}

bool player::isterrain(char t){								//ritorna true se quello sotto al giocatore è considerabile terreno, false atrimenti
	if(t=='#' || t=='-' || t=='|')
		return true;
	else
		return false;
}

void player::stairsup(){									//Controlla se ci sono scale, la loro direzione e fa salire il personaggio
	if(mvwinch(curwin, yLoc, xLoc+1)=='-'){
		mvwaddch(curwin, yLoc, xLoc, ' ');
		xLoc++;
		while(mvwinch(curwin, yLoc-1, xLoc)=='-'){
			mvwaddch(curwin, yLoc, xLoc, ' ');
			yLoc--;
			if(yLoc<=0)
				yLoc=1;
			display();
			mvwaddch(curwin, yLoc+1, xLoc, '-');
			usleep(30000);
			wrefresh(curwin);
		}
		yLoc--;
		if(yLoc<=0)
			yLoc=1;
		xLoc--;
		display();
		mvwaddch(curwin, yLoc+1, xLoc+1, '-');
		usleep(30000);
		wrefresh(curwin);
	}
	else{
		mvwaddch(curwin, yLoc, xLoc, ' ');
		xLoc--;
		while(mvwinch(curwin, yLoc-1, xLoc)=='-'){
			mvwaddch(curwin, yLoc, xLoc, ' ');
			yLoc--;
			if(yLoc<=0)
				yLoc=1;
			display();
			mvwaddch(curwin, yLoc+1, xLoc, '-');
			usleep(30000);
			wrefresh(curwin);
		}
		yLoc--;
		if(yLoc<=0)
			yLoc=1;
		xLoc++;
		display();
		mvwaddch(curwin, yLoc+1, xLoc-1, '-');
		usleep(30000);
		wrefresh(curwin);
	}
}

void player::stairsdown(){								//Come stairsup ma fa scendere il personaggio
	int cont=0;
	while(mvwinch(curwin, yLoc+1, xLoc)=='-'){
		mvwaddch(curwin, yLoc, xLoc, ' ');
		yLoc++;
		if(yLoc>=yMax-1)
			yLoc=yMax-2;
		display();
		usleep(45000);
		wrefresh(curwin);
		cont++;
		if(cont>1)
			mvwaddch(curwin, yLoc-1, xLoc, '-');
	}

	if(mvwinch(curwin, yLoc+1, xLoc)=='#' && mvwinch(curwin, yLoc, xLoc+1)=='#'){	//Controlla i blocchi attorno e sotto il personaggio
		mvwaddch(curwin, yLoc, xLoc, ' ');											//e in base a quello decide come stamparlo
		if(xLoc<=0)
			xLoc=1;
		mvwaddch(curwin, yLoc, xLoc, '-');
		xLoc--;
		yLoc--;
		while(mvwinch(curwin, yLoc, xLoc)=='|')
			xLoc--;
		display();
		usleep(45000);
		wrefresh(curwin);
	}
	else if(mvwinch(curwin, yLoc+1, xLoc)=='#' || mvwinch(curwin, yLoc, xLoc-1)=='#'){
		mvwaddch(curwin, yLoc, xLoc, ' ');
		if(xLoc<=0)
			xLoc=1;
		mvwaddch(curwin, yLoc, xLoc, '-');
		xLoc++;
		yLoc--;
		while(mvwinch(curwin, yLoc, xLoc)=='|')
			xLoc++;
		display();
		usleep(45000);
		wrefresh(curwin);
	}
	else{
		mvwaddch(curwin, yLoc, xLoc, ' ');
		mvwaddch(curwin, yLoc, xLoc, '-');
		yLoc++;
		while(mvwinch(curwin, yLoc, xLoc)=='|')
			xLoc--;
		if(yLoc>=yMax-1)
			yLoc=yMax-2;
		display();
		usleep(45000);
		wrefresh(curwin);
	}

}

void player::mvup(){																	//Da mvup a mvleft cambiano la posizione del personaggio e controllano di
	if(isterrain(mvwinch(curwin, yLoc-1, xLoc))==true)									//non farlo sbattere contro del terreno
		return;
	mvwaddch(curwin, yLoc, xLoc, ' ');
	yLoc--;
	if(yLoc<=0)
		yLoc=1;
}

void player::mvdown(){
	if(mvwinch(curwin, yLoc+1, xLoc)=='#' || mvwinch(curwin, yLoc+1, xLoc)=='|')
		return;
	if(mvwinch(curwin, yLoc+1, xLoc)=='-')
		stairsdown();
	mvwaddch(curwin, yLoc, xLoc, ' ');
	yLoc++;
	if(yLoc>=yMax-1)
		yLoc=yMax-2;
}

void player::mvright(){
	if(mvwinch(curwin, yLoc, xLoc+1)=='#' || mvwinch(curwin, yLoc, xLoc+1)=='|')
		return;
	if(mvwinch(curwin, yLoc, xLoc+1)=='-')
		stairsup();
	mvwaddch(curwin, yLoc, xLoc, ' ');
	xLoc++;
	if(xLoc>=xMax-1)
		xLoc=xMax-2;

}

void player::mvleft(){
	if(mvwinch(curwin, yLoc, xLoc-1)=='#' || mvwinch(curwin, yLoc, xLoc-1)=='|')
		return;
	if(mvwinch(curwin, yLoc, xLoc-1)=='-')
		stairsup();
	mvwaddch(curwin, yLoc, xLoc, ' ');
	xLoc--;
	if(xLoc<=0)
		xLoc=1;

}

void player::jump(){											//Funzione per il salto. Prende in input l'ultima direzione
	switch(dir){												//in cui il giocatore stava guardando e in base a quella direziona
		case 0:													//il salto. Si può cambiare l'altezza del salto con una semplice variabile.
			for(int cont = 0; cont < 6; cont++){
				mvup();
				display();
				usleep(30000);
				wrefresh(curwin);
				mvleft();
				display();
				usleep(30000);
				wrefresh(curwin);
			}
			while(isterrain(mvwinch(curwin, yLoc+1, xLoc))==false && yLoc+1!=yMax-1){  //Controlla che sotto il personaggio ci sia del terreno, altrimenti continua a cadere
				mvdown();
				display();
				usleep(30000);
				wrefresh(curwin);
				mvleft();
				display();
				usleep(30000);
				wrefresh(curwin);
			}
			break;
		case 1:
			for(int cont = 0; cont < 6; cont++){
				mvup();
				display();
				usleep(30000);
				wrefresh(curwin);
				mvright();
				display();
				usleep(30000);
				wrefresh(curwin);
			}
			while(isterrain(mvwinch(curwin, yLoc+1, xLoc))==false && yLoc+1!=yMax-1){
				mvdown();
				display();
				usleep(30000);
				wrefresh(curwin);
				mvright();
				display();
				usleep(30000);
				wrefresh(curwin);
			}
			break;
		default:										//Al momento inutilizzata: salta in alto invece che alto a destra o alto a sinistra
			for(int cont = 0; cont < 6; cont++){
				mvup();
				display();
				usleep(42000);
				wrefresh(curwin);
			}
			while((mvwinch(curwin, yLoc+1, xLoc)!='#' && (mvwinch(curwin, yLoc+1, xLoc)!='-')) && yLoc+1!=yMax-1){
				mvdown();
				display();
				usleep(42000);
				wrefresh(curwin);
			}
			break;
	}
}
int player::leftright(){
	if(yLoc+1==yMax-1){                                    //Stampa il numero di vite in alto a sinistra
		life--;
		mvwprintw(curwin, 0, 0,"HP: %d", life);			   //Al momento non c'è una scermata di morte quindi va in negativo
		mvwaddch(curwin, yLoc, xLoc, ' ');
		yLoc=originy;
		xLoc=originx;
		display();
	}
	while(isterrain(mvwinch(curwin, yLoc+1, xLoc))==false  && yLoc+1!=yMax-1){			   //Controlla che sotto al pesonaggio ci sia del terreno
		mvdown();
		display();
		usleep(42000);
		wrefresh(curwin);
	}
	wtimeout(curwin, 2000);
	int choice = wgetch(curwin);						   //Prende l'input di movimento
	switch(choice){
	case KEY_LEFT:
		dir=0;
		mvleft();
		break;
	case KEY_RIGHT:
		dir=1;
		mvright();
		break;
	case KEY_UP:
		jump();
		break;
	case KEY_DOWN:
		mvdown();
		break;
	default:
		dir=2;
		break;
	}
	return(choice);

}

int player::move(){
	return leftright();									//Fa partire il movimento e controlla se si preme esc
}

void player::display(){
	mvwaddch(curwin, yLoc, xLoc, character);			//Stampa il personaggio
	usleep(5000);
	wrefresh(curwin);
}