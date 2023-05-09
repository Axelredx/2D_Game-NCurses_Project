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
	if(isterrain(mvwinch(curwin, yLoc, xLoc+1))==true || isterrain(mvwinch(curwin, yLoc+1, xLoc+1))==false)
		return;
	mvwaddch(curwin, yLoc, xLoc, ' ');
	xLoc++;
	if(xLoc>=xMax-1)
		xLoc=xMax-2;
}

void basicenemy::mvleft(){
	takedamage();
	if(isterrain(mvwinch(curwin, yLoc, xLoc-1))==true || isterrain(mvwinch(curwin, yLoc+1, xLoc-1))==false)
		return;
	mvwaddch(curwin, yLoc, xLoc, ' ');
	xLoc--;
	if(xLoc<=0)
		xLoc=1;
}

void basicenemy::mvdown(){
	if(isterrain(mvwinch(curwin, yLoc+1, xLoc))==true)
		return;
	mvwaddch(curwin, yLoc, xLoc, ' ');
	yLoc++;
	if(yLoc>=yMax-1)
		yLoc=yMax-2;
}

//Funzione principale del nemico, che contiene la sua IA
//Prima di tutto controlla se è già stato sparato un proiettile, in caso affermativo, continua a spararlo, dopodichè si assicura
//che il nemico sia vivo.
//Successivamente controlla se il giocatore è vicino al nemico, in caso affermativo, c'è una possibilità
//su due che decida di sparare.
//Nel caso non ci sia nessun giocatore, allora c'è una possibilità su tre che decida di muoversi in una direzione casuale.
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
			if(rand()%5==0){
				if(isterrain(mvwinch(curwin, yLoc, xLoc+1))==true){
					mvleft();
					display();
					usleep(50000);
					wrefresh(curwin);
				}
				else{
					mvright();
					display();
					usleep(50000);
					wrefresh(curwin);
				}
			}

			else if(rand()%5==1){
				if(isterrain(mvwinch(curwin, yLoc, xLoc-1))==true){
					mvright();
					display();
					usleep(50000);
					wrefresh(curwin);
				}
				else{
					mvleft();
					display();
					usleep(50000);
					wrefresh(curwin);
				}
			}
			else{
				usleep(50000);
				wrefresh(curwin);
				return NULL;
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

void basicenemy::gravity(){
	while(isterrain(mvwinch(curwin, yLoc+1, xLoc))==false && yLoc+1!=yMax-1){
		mvdown();
		display();
		usleep(42000);
		wrefresh(curwin);
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



/*
 *
 * SOTTOCLASSE JUMPING ENEMY
 *
 */

void* jumpingenemy::behaviour(void*){

	if(s==true){
		shoot(dirlock);
		return NULL;
	}
	if(life>0){
		gravity();
		if((playerfinder()==0 || playerfinder()==1) && life>0 && rand()%difficulty==0){
			takedamage();
			shoot(playerfinder());
		}
		if((bulletfinder()==0 || bulletfinder()==1) && s==false && rand()%difficulty==0){
			jump(bulletfinder());
		}
		else{
			takedamage();
			if(rand()%5==0){
				if(isterrain(mvwinch(curwin, yLoc, xLoc+1))==true){
					mvleft();
					display();
					usleep(50000);
					wrefresh(curwin);
				}
				else{
					mvright();
					display();
					usleep(50000);
					wrefresh(curwin);
				}
			}

			else if(rand()%5==1){
				if(isterrain(mvwinch(curwin, yLoc, xLoc-1))==true){
					mvright();
					display();
					usleep(50000);
					wrefresh(curwin);
				}
				else{
					mvleft();
					display();
					usleep(50000);
					wrefresh(curwin);
				}
			}
			else{
				usleep(50000);
				wrefresh(curwin);
				return NULL;
			}
			return NULL;
		}
	}
	else
		return NULL;
}

void jumpingenemy::mvup(){
	if(isterrain(mvwinch(curwin, yLoc-1, xLoc))==true)
		return;
	mvwaddch(curwin, yLoc, xLoc, ' ');
	yLoc--;
	if(yLoc<=0)
		yLoc=1;
}

void jumpingenemy::mvright(){
	takedamage();
	if(isterrain(mvwinch(curwin, yLoc, xLoc+1))==true)
		return;
	mvwaddch(curwin, yLoc, xLoc, ' ');
	xLoc++;
	if(xLoc>=xMax-1)
		xLoc=xMax-2;
}

void jumpingenemy::mvleft(){
	takedamage();
	if(isterrain(mvwinch(curwin, yLoc, xLoc-1))==true)
		return;
	mvwaddch(curwin, yLoc, xLoc, ' ');
	xLoc--;
	if(xLoc<=0)
		xLoc=1;
}

//Questo metodo serve a controllare se è presente un giocatore a una distanza massima di nove blocchi dal nemico
int jumpingenemy::playerfinder(){
	if(mvwinch(curwin, yLoc, xLoc-1)=='P' || mvwinch(curwin, yLoc, xLoc-2)=='P' || mvwinch(curwin, yLoc, xLoc-3)=='P'
	   || mvwinch(curwin, yLoc, xLoc-4)=='P' || mvwinch(curwin, yLoc, xLoc-5)=='P' || mvwinch(curwin, yLoc, xLoc-6)=='P'
	   || mvwinch(curwin, yLoc, xLoc-7)=='P' || mvwinch(curwin, yLoc, xLoc-8)=='P' || mvwinch(curwin, yLoc, xLoc-9)=='P'
	   || mvwinch(curwin, yLoc, xLoc-10)=='P' || mvwinch(curwin, yLoc, xLoc-11)=='P' || mvwinch(curwin, yLoc, xLoc-12)=='P'
	   || mvwinch(curwin, yLoc, xLoc-13)=='P' || mvwinch(curwin, yLoc, xLoc-14)=='P' || mvwinch(curwin, yLoc, xLoc-15)=='P')
		return 0;
	else if (mvwinch(curwin, yLoc, xLoc+1)=='P' || mvwinch(curwin, yLoc, xLoc+2)=='P' || mvwinch(curwin, yLoc, xLoc+3)=='P'
			|| mvwinch(curwin, yLoc, xLoc+4)=='P' || mvwinch(curwin, yLoc, xLoc+5)=='P' || mvwinch(curwin, yLoc, xLoc+6)=='P'
			|| mvwinch(curwin, yLoc, xLoc+7)=='P' || mvwinch(curwin, yLoc, xLoc+8)=='P' || mvwinch(curwin, yLoc, xLoc+9)=='P'
		    || mvwinch(curwin, yLoc, xLoc+10)=='P' || mvwinch(curwin, yLoc, xLoc+11)=='P' || mvwinch(curwin, yLoc, xLoc+12)=='P'
			|| mvwinch(curwin, yLoc, xLoc+13)=='P' || mvwinch(curwin, yLoc, xLoc+14)=='P' || mvwinch(curwin, yLoc, xLoc+15)=='P')
		return 1;
	else
		return 2;
}

void jumpingenemy::takedamage(){
	if(yLoc+1==yMax-1){
		enemy=' ';
		life=0;
		mvwaddch(curwin, yLoc, xLoc, ' ');
		wrefresh(curwin);
	}
	else if(mvwinch(curwin, yLoc, xLoc-1)=='o' || mvwinch(curwin, yLoc, xLoc+1)=='o'){
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

int jumpingenemy::bulletfinder(){
	if(mvwinch(curwin, yLoc, xLoc-1)=='o' || mvwinch(curwin, yLoc, xLoc-2)=='o' || mvwinch(curwin, yLoc, xLoc-3)=='o')
		return 0;
	else if (mvwinch(curwin, yLoc, xLoc+1)=='o' || mvwinch(curwin, yLoc, xLoc+2)=='o' || mvwinch(curwin, yLoc, xLoc+3)=='o')
		return 1;
	else
		return 2;
}

void jumpingenemy::jump(int dir){
	if(dir==0){
		j=true;
		for(int cont = 0; cont < 10; cont++){
			mvup();
			display();
			usleep(10000);
			wrefresh(curwin);
			mvleft();
			display();
			usleep(10000);
			wrefresh(curwin);
		}
		while(isterrain(mvwinch(curwin, yLoc+1, xLoc))==false && yLoc+1!=yMax-1){
			mvdown();
			display();
			usleep(10000);
			wrefresh(curwin);
			mvleft();
			display();
			usleep(10000);
			wrefresh(curwin);
		}
		j=false;
	}
	else{
		j=true;
		for(int cont = 0; cont < 10; cont++){
			mvup();
			display();
			usleep(10000);
			wrefresh(curwin);
			mvright();
			display();
			usleep(10000);
			wrefresh(curwin);
		}
		while(isterrain(mvwinch(curwin, yLoc+1, xLoc))==false && yLoc+1!=yMax-1){
			mvdown();
			display();
			usleep(10000);
			wrefresh(curwin);
			mvright();
			display();
			usleep(10000);
			wrefresh(curwin);
		}
		j=false;
	}
}