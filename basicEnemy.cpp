
#include "basicEnemy.hpp"

		/*
		 *      ___ ___  ___      __    __        ___
 	 	 	/\   |   |  |__  |\ |  / | /  \ |\ | |__
		 * /~~\  |   |  |___ | \| /_ | \__/ | \| |___
		 *
		 * Questa classe funziona ma è da migliorare e sono presenti alcuni bug che non ho ancora risolto quali:
		 *
		 * - P che spuntano apparentemente senza motivo nella mappa
		 *
		 * Se trovate modo di risolvere questi bug, ditemelo e modificherò la classe!
		 */

//Costruttore della classe
basicenemy::basicenemy(WINDOW * win, int y, int x, int l, char e){
	curwin=win;
	yLoc=y;
	xLoc=x;

	//Vita del nemico
	life=l;
	enemy=e;

	//Indica se si sta sparando un proiettile
	s=false;

	//Coordinate x e y del proiettile
	projx=0;
	projy=0;

	getmaxyx(curwin, yMax, xMax);
	dirlock=0;

	//setto rand
	srand(time(0));
}

//Questo metodo serve a controllare se è presente un giocatore a una distanza massima di nove blocchi dal nemico
int basicenemy::playerfinder(){
	if(mvwinch(curwin, yLoc, xLoc-1)=='P' || mvwinch(curwin, yLoc, xLoc-2)=='P' || mvwinch(curwin, yLoc, xLoc-3)=='P'
	   || mvwinch(curwin, yLoc, xLoc-4)=='P' || mvwinch(curwin, yLoc, xLoc-5)=='P' || mvwinch(curwin, yLoc, xLoc-6)=='P'
	   || mvwinch(curwin, yLoc, xLoc-7)=='P' || mvwinch(curwin, yLoc, xLoc-8)=='P' || mvwinch(curwin, yLoc, xLoc-9)=='P')
		return 0;
	else if (mvwinch(curwin, yLoc, xLoc+1)=='P' || mvwinch(curwin, yLoc, xLoc+2)=='P' || mvwinch(curwin, yLoc, xLoc+3)=='P'
			|| mvwinch(curwin, yLoc, xLoc+4)=='P' || mvwinch(curwin, yLoc, xLoc+5)=='P' || mvwinch(curwin, yLoc, xLoc+6)=='P'
			|| mvwinch(curwin, yLoc, xLoc+7)=='P' || mvwinch(curwin, yLoc, xLoc+8)=='P' || mvwinch(curwin, yLoc, xLoc+9)=='P')
		return 1;
	else
		return 2;
}

//mvright e mvleft muovono il nemico a destra o a sinistra
void basicenemy::mvright(){
	takedamage();
	mvwaddch(curwin, yLoc, xLoc, ' ');
	xLoc++;
	if(xLoc>=xMax-1)
		xLoc=xMax-2;
}

void basicenemy::mvleft(){
	takedamage();
	mvwaddch(curwin, yLoc, xLoc, ' ');
	xLoc--;
	if(xLoc<=0)
		xLoc=1;
}

//Funzione principale del nemico, che contiene la sua IA
//Prima di tutto controlla se è già stato sparato un proiettile, in caso affermativo, continua a spararlo, dopodichè si assicura
//che il nemico sia vivo.
//Successivamente controlla se il giocatore è vicino al nemico, in caso affermativo, c'è una possibilità
//su due che decida di sparare.
//Nel caso non ci sia nessun nemico, allora c'è una possibilità su tre che decida di muoversi in una direzione casuale.
//I nemici non possono cadere
void* basicenemy::behaviour(void*){

	if(s==true)
		shoot(dirlock);
	if(life>0){
		if(playerfinder()==0 && life>0){
			takedamage();
			if(rand()%2==0)
			shoot(0);
		}
		else if(playerfinder()==1 && life>0){
			takedamage();
			if(rand()%2==0)
				shoot(1);
		}
		else{
			takedamage();
			usleep(50000);
			if(rand()%2==0 && (isterrain(mvwinch(curwin, yLoc+1, xLoc+1))==true)){
				if(isterrain(mvwinch(curwin, yLoc, xLoc+1))==true){
					mvleft();
					display();
				}
				else if (isterrain(mvwinch(curwin, yLoc, xLoc-1))==false){
					mvright();
					display();
				}
			}

			else if(rand()%2==1 && (isterrain(mvwinch(curwin, yLoc+1, xLoc-1))==true)){
				if(isterrain(mvwinch(curwin, yLoc, xLoc-1))==true){
					mvright();
					display();
				}
				else if (isterrain(mvwinch(curwin, yLoc, xLoc+1))==false){
					mvleft();
					display();
				}
			}
			return NULL;
		}
	}
	else
		return NULL;
}

//Controlla che il carattere in input sia considerato terreno o no
bool basicenemy::isterrain(char t){
	if(t=='#' || t=='-' || t=='|' || t=='e')
		return true;
	else
		return false;
}

//Funzione che fa si che il nemico prenda danno
void basicenemy::takedamage(){
	if(mvwinch(curwin, yLoc, xLoc-1)=='o' || mvwinch(curwin, yLoc, xLoc+1)=='o'){
		mvwaddch(curwin, yLoc, xLoc, ' ');
		life--;
		if(mvwinch(curwin, yLoc, xLoc-1)=='o')
			mvwaddch(curwin, yLoc, xLoc-1, ' ');
		else
			mvwaddch(curwin, yLoc, xLoc+1, ' ');
		if(life>0){
			mvwaddch(curwin, yLoc, xLoc, enemy);
			wrefresh(curwin);
		}
		else
			enemy=' ';
	}

}

//Funzione dello sparo molto simile a quella del giocatore
void basicenemy::shoot(int dir){
	if(dir==0 && s==false){
		projy = yLoc;
		projx= xLoc-2;
		dirlock=dir;
		s=true;
		if(isterrain(mvwinch(curwin, projy, projx))==false && isterrain(mvwinch(curwin, projy, projx+1))==false && projx>=1){
			mvwaddch(curwin, projy, projx+1, ' ');
			usleep(5000);
			display();
			wrefresh(curwin);
			mvwaddch(curwin, projy, projx, 'o');
			projx--;
			usleep(5000);
			display();
			wrefresh(curwin);
		}
		else if(isterrain(mvwinch(curwin, projy, projx+1))==false)
			mvwaddch(curwin, projy, projx+1, ' ');
		else{
			mvwaddch(curwin, projy, projx+2, ' ');
			s=false;
			display();
			wrefresh(curwin);
		}
	}
	else if(dir==1 && s==false){
		projy = yLoc;
		projx= xLoc+2;
		dirlock=dir;
		s=true;
		if(isterrain(mvwinch(curwin, projy, projx))==false && isterrain(mvwinch(curwin, projy, projx-1))==false && projx<=xMax-2){
			mvwaddch(curwin, projy, projx-1, ' ');
			usleep(5000);
			display();
			wrefresh(curwin);
			mvwaddch(curwin, projy, projx, 'o');
			projx++;
			usleep(5000);
			display();
			wrefresh(curwin);
		}
		else if(isterrain(mvwinch(curwin, projy, projx-1))==false)
			mvwaddch(curwin, projy, projx-1, ' ');
		else{
			mvwaddch(curwin, projy, projx-2, ' ');
			s=false;
			display();
			wrefresh(curwin);
		}

	}
	else if(dir==0 && s==true){
		if(isterrain(mvwinch(curwin, projy, projx))==false && isterrain(mvwinch(curwin, projy, projx+1))==false && projx>=1){
			mvwaddch(curwin, projy, projx+1, ' ');
			usleep(5000);
			display();
			wrefresh(curwin);
			mvwaddch(curwin, projy, projx, 'o');
			projx--;
			usleep(5000);
			display();
			wrefresh(curwin);
		}
		else{
			mvwaddch(curwin, projy, projx+1, ' ');
			s=false;
		}
	}
	else if(dir==1 && s==true){
		if(isterrain(mvwinch(curwin, projy, projx))==false && isterrain(mvwinch(curwin, projy, projx-1))==false && projx<=xMax-2){
			mvwaddch(curwin, projy, projx-1, ' ');
			usleep(5000);
			display();
			wrefresh(curwin);
			mvwaddch(curwin, projy, projx, 'o');
			projx++;
			usleep(5000);
			display();
			wrefresh(curwin);
		}
		else{
			mvwaddch(curwin, projy, projx-1, ' ');
			s=false;
		}
	}
	wrefresh(curwin);
}

//Funzione che stampa il nemico
void basicenemy::display(){
	mvwaddch(curwin, yLoc, xLoc, enemy);
	takedamage();
}