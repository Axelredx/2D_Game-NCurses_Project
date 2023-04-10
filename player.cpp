//aggiorna la funzione di spawn per leggere eventuali salvataggi; se presenti, passa x ed y per lo spawn altrimenti default
//nella funzione che crea il player, tieni conto della vita nei salvataggi
#include "player.hpp"

//Costruttore della classe
player::player(WINDOW * win, int y, int x, char c, int m, int l){
	curwin = win;
	yLoc=y;
	xLoc = x;

	//Coordinata y dello spawn del giocatore
	originy=y;

	//Coordinata x dello spawn del giocatore
	originx=x;

	getmaxyx(curwin, yMax, xMax);
	keypad(curwin, true);
	character=c;

	//Vita del giocatore
	life=l;

	//Soldi del giocatore 
	money=m;

	//prezzo upgrade della vita e del salto
	healthPrice=20;
	jumpPrice=20;

	//Indica le y del proiettile
	projy=y;

	//Indica le x del proiettile
	projx=x;

	//Indica se un proiettile sta venendo disegnato
	s=false;

	//Indica l'ultima direzione in cui il giocatore è andato
	dir=false;

	//Blocca la direzione del proiettile
	dirlock=false;

	//Indica se il giocatore sta saltando
	j=false;

	//Stampa la vita del giocatore
	mvwprintw(curwin, 0, 0,"HP: %d", life);
}

//ritorna true se il char in input è considerabile terreno, false atrimenti
bool player::isterrain(char t){
	if(t=='#' || t=='-' || t=='|')
		return true;
	else
		return false;
}

int player::getLife(){
	return life;
}

//Controlla se ci sono scale, se si, controlla la loro direzione e fa salire il giocatore
void player::stairsup(){
	if(mvwinch(curwin, yLoc, xLoc+1)=='-'){
		mvwaddch(curwin, yLoc, xLoc, ' ');
		xLoc++;
		while(mvwinch(curwin, yLoc-1, xLoc)=='-'){
			mvwaddch(curwin, yLoc, xLoc, ' ');
			yLoc--;
			if(yLoc<=0)
				yLoc=1;
			display(NULL);
			mvwaddch(curwin, yLoc+1, xLoc, '-');
			usleep(12000);
			wrefresh(curwin);
		}
		yLoc--;
		if(yLoc<=0)
			yLoc=1;
		xLoc--;
		display(NULL);
		mvwaddch(curwin, yLoc+1, xLoc+1, '-');
		usleep(12000);
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
			display(NULL);
			mvwaddch(curwin, yLoc+1, xLoc, '-');
			usleep(12000);
			wrefresh(curwin);
		}
		yLoc--;
		if(yLoc<=0)
			yLoc=1;
		xLoc++;
		display(NULL);
		mvwaddch(curwin, yLoc+1, xLoc-1, '-');
		usleep(12000);
		wrefresh(curwin);
	}
}

//Come stairsup ma fa scendere il giocatore.
//La velocità del movimento è stata aumentata rispetto a prima
//per incentivare il giocatore a usare le scale invece che
//semplicemente cadere
void player::stairsdown(){
	int cont=0;
	while(mvwinch(curwin, yLoc+1, xLoc)=='-'){
		mvwaddch(curwin, yLoc, xLoc, ' ');
		yLoc++;
		if(yLoc>=yMax-1)
			yLoc=yMax-2;
		display(NULL);
		usleep(12000);
		wrefresh(curwin);
		cont++;
		if(cont>1)
			mvwaddch(curwin, yLoc-1, xLoc, '-');
	}

	//Controlla i char attorno e sotto il giocatore e in base a quello
	//decide come stamparlo
	if(mvwinch(curwin, yLoc+1, xLoc)=='#' && mvwinch(curwin, yLoc, xLoc+1)=='#'){
		mvwaddch(curwin, yLoc, xLoc, ' ');
		if(xLoc<=0)
			xLoc=1;
		mvwaddch(curwin, yLoc, xLoc, '-');
		xLoc--;
		yLoc--;
		while(mvwinch(curwin, yLoc, xLoc)=='|')
			xLoc--;
		display(NULL);
		usleep(12000);
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
		display(NULL);
		usleep(12000);
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
		display(NULL);
		usleep(12000);
		wrefresh(curwin);
	}
}

//Le funzioni da mvup a mvleft stampano il giocatore, controllando
//di non fargli colpire il terreno.
//mvdown, mvright e mvleft sanno riconoscere se i char attorno al giocatore sono
//normale terreno o scale.
void player::mvup(){
	if(isterrain(mvwinch(curwin, yLoc-1, xLoc))==true)
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

//Funzione per il salto. E' connessa con la funzione shoot() per permettere di saltare mentre
//il proiettile sta venendo disegnato.
//Ho aumentato l'ampiezza del salto e la sua velocità per migliorare il feeling del gioco.

//!IDEA PER UN POTENZIAMENTO!
//Si potrebbe cambiare l'ampiezza del salto con una semplice variabile, essendo che questa è controllata
//da un contatore.
void player::jump(){
	if(dir==true && s==false){
		j=true;
		for(int cont = 0; cont < 10; cont++){
			mvup();
			display(NULL);
			usleep(10000);
			wrefresh(curwin);
			mvleft();
			display(NULL);
			usleep(10000);
			wrefresh(curwin);
		}
		while(isterrain(mvwinch(curwin, yLoc+1, xLoc))==false && yLoc+1!=yMax-1){  //Controlla che sotto il giocatore ci sia del terreno, altrimenti continua a cadere
			mvdown();
			display(NULL);
			usleep(10000);
			wrefresh(curwin);
			mvleft();
			display(NULL);
			usleep(10000);
			wrefresh(curwin);
		}
		j=false;
	}
	else if(dir==false && s==false){
		j=true;
		for(int cont = 0; cont < 10; cont++){
			mvup();
			display(NULL);
			if(s==true)
				shoot();
			usleep(10000);
			wrefresh(curwin);
			mvright();
			display(NULL);
			usleep(10000);
			wrefresh(curwin);
		}
		while(isterrain(mvwinch(curwin, yLoc+1, xLoc))==false && yLoc+1!=yMax-1){
			mvdown();
			display(NULL);
			usleep(10000);
			wrefresh(curwin);
			mvright();
			display(NULL);
			usleep(10000);
			wrefresh(curwin);
		}
		j=false;
	}
	else if(dir==true && s==true){
		j=true;
		for(int cont = 0; cont < 10; cont++){
			mvup();
			display(NULL);
			shoot();
			if(s==false){
				usleep(10000);
				wrefresh(curwin);
			}
			mvleft();
			display(NULL);
			shoot();
			if(s==false){
				usleep(10000);
				wrefresh(curwin);
			}
		}
		while(isterrain(mvwinch(curwin, yLoc+1, xLoc))==false && yLoc+1!=yMax-1){
			mvdown();
			display(NULL);
			shoot();
			if(s==false){
				usleep(10000);
				wrefresh(curwin);
			}
			mvleft();
			display(NULL);
			shoot();
			if(s==false){
				usleep(10000);
				wrefresh(curwin);
			}
		}
		j=false;
	}
	else if(dir==false && s==true){
		j=true;
		for(int cont = 0; cont < 10; cont++){
			mvup();
			display(NULL);
			shoot();
			if(s==false){
				usleep(10000);
				wrefresh(curwin);
			}
			mvright();
			display(NULL);
			shoot();
			if(s==false){
				usleep(10000);
				wrefresh(curwin);
			}
		}
		while(isterrain(mvwinch(curwin, yLoc+1, xLoc))==false && yLoc+1!=yMax-1){
			mvdown();
			display(NULL);
			shoot();
			if(s==false){
				usleep(10000);
				wrefresh(curwin);
			}
			mvright();
			display(NULL);
			shoot();
			if(s==false){
				usleep(10000);
				wrefresh(curwin);
			}
		}
		j=false;
	}
}

//Funzione che serve a prendere l'input del giocatore.
//Inoltre richiama lifeshow() ogni volta che viene richiamata.
int player::leftright(){
	lifeshow();

	//wtimeout imposta un timeout di un secondo per ricevere l'input. Se entro quel secondo
	//nessun input è stato ricevuto, le funzioni che richiamano leftright() sono in grado
	//di riconoscerlo
	wtimeout(curwin, 1);
	int choice = wgetch(curwin);
	switch(choice){

	//Sposta a sinistra il giocatore
	case KEY_LEFT:
		dir=true;
		mvleft();
		break;

	//Sposta a destra il giocatore
	case KEY_RIGHT:
		dir=false;
		mvright();
		break;

	//Fa saltare il giocatore
	case KEY_UP:
		if(j==false)
			jump();
		break;

	//Fa scendere il giocatore se ci sono scale
	case KEY_DOWN:
		mvdown();
		break;

	//Spara se non ci sono altri proiettili sullo schermo e se
	//il giocatore non sta saltando.

	//Per chiarezza: 32 = barra spaziatrice
	case 32:
		if(s==false && j==false)
			shoot();
		break;
	default:
		break;
	}
	return(choice);
}

//Funzione che inizializza il movimento del giocatore e garantisce l'efficacia della funzione gravity()
int player::move(){
	lifeshow();
	gravity();
	//Fa partire il movimento e controlla se si preme esc
	return leftright();
}

//Controlla se sotto al giocatore c'è del terreno. Se non ce n'è, lo muove verso il basso
void player::gravity(){
	while(isterrain(mvwinch(curwin, yLoc+1, xLoc))==false  && yLoc+1!=yMax-1){
		mvdown();
		display(NULL);
		usleep(42000);
		wrefresh(curwin);
	}
}

//Stampa il numero di vite restanti in alto a sinistra. (!GRAFICA DA CAMBIARE!)
//Inoltre è responsabile di diminuire la vita del giocatore.
//Al momento non c'è una scermata di morte quindi il counter va in negativo
void player::lifeshow(){
	if(yLoc+1==yMax-1){
		life--;
		mvwprintw(curwin, 0, 0,"HP: %d", life);
		mvwaddch(curwin, yLoc, xLoc, ' ');
		yLoc=originy;
		xLoc=originx;
		display(NULL);
	}
}

//Funzione per lo sparo. Il suo funzionamento è abbastanza complesso, riassumendo, ciò che fa
//è controllare due variabili: la posizione del personagggio mentre spara (variabile dir) e
//se un proiettile sta già venendo stampato a schermo (variabile s).
//In base a questi due booleani decide in che direzione far stampare il proiettile e se
//continuare l'animazione di un proiettile già stampato o stamparne uno nuovo
void player::shoot(){
	if(dir==true && s==false){
		if(j==true)
			return;
		projy = yLoc;
		projx= xLoc-2;
		dirlock=dir;
		s=true;
		while(isterrain(mvwinch(curwin, projy, projx))==false && isterrain(mvwinch(curwin, projy, projx+1))==false && projx>=1){
			mvwaddch(curwin, projy, projx+1, ' ');
			usleep(5000);
			display(NULL);
			wrefresh(curwin);
			mvwaddch(curwin, projy, projx, 'o');
			projx--;
			usleep(5000);
			display(NULL);
			wrefresh(curwin);
			leftright();
			if(j==false)
				gravity();
		}
		if(isterrain(mvwinch(curwin, projy, projx+1))==false)
			mvwaddch(curwin, projy, projx+1, ' ');
		else
			mvwaddch(curwin, projy, projx+2, ' ');
		s=false;
	}
	else if(dir==false && s==false){
		if(j==true)
			return;
		projy = yLoc;
		projx= xLoc+2;
		dirlock=dir;
		s=true;
		while(isterrain(mvwinch(curwin, projy, projx))==false && isterrain(mvwinch(curwin, projy, projx-1))==false && projx<=xMax-2){
			mvwaddch(curwin, projy, projx-1, ' ');
			usleep(5000);
			display(NULL);
			wrefresh(curwin);
			mvwaddch(curwin, projy, projx, 'o');
			projx++;
			usleep(5000);
			display(NULL);
			wrefresh(curwin);
			leftright();
			if(j==false)
				gravity();
		}
		if(isterrain(mvwinch(curwin, projy, projx-1))==false)
			mvwaddch(curwin, projy, projx-1, ' ');
		else
			mvwaddch(curwin, projy, projx-2, ' ');
		s=false;
	}
	else if(dirlock==true && s==true){
		if(isterrain(mvwinch(curwin, projy, projx))==false && isterrain(mvwinch(curwin, projy, projx+1))==false && projx>=1){
			mvwaddch(curwin, projy, projx+1, ' ');
			usleep(5000);
			display(NULL);
			wrefresh(curwin);
			mvwaddch(curwin, projy, projx, 'o');
			projx--;
			usleep(5000);
			display(NULL);
			wrefresh(curwin);
			leftright();
			if(j==false)
				gravity();
		}
		else{
			mvwaddch(curwin, projy, projx+1, ' ');
			s=false;
		}
	}
	else if(dirlock==false && s==true){
		if(isterrain(mvwinch(curwin, projy, projx))==false && isterrain(mvwinch(curwin, projy, projx-1))==false && projx<=xMax-2){
			mvwaddch(curwin, projy, projx-1, ' ');
			usleep(5000);
			display(NULL);
			wrefresh(curwin);
			mvwaddch(curwin, projy, projx, 'o');
			projx++;
			usleep(5000);
			display(NULL);
			wrefresh(curwin);
			leftright();
			if(j==false)
				gravity();
		}
		else{
			mvwaddch(curwin, projy, projx-1, ' ');
			s=false;
		}
	}


	wrefresh(curwin);
}

//Funzione che stampa il char del giocatore
void* player::display(void * arg){
	mvwaddch(curwin, yLoc, xLoc, character);
	return NULL;
}


//Funzione che ritorna una variabile della classe, utile per il salvataggio o operazioni di debug

//Output in base al numero in input:
/*
 * input=0
 * ritorna la coordinata y del giocatore
 *
 * input=1
 * ritorna la coordinata x del giocatore
 *
 * input=2
 * ritorna la coordinata y dello spawn del giocatore
 *
 * input=3
 * ritorna la coordinata x dello spawn del giocatore
 *
 * input=4
 * ritorna la vita del giocatore
 *
 * input=5
 * ritorna la coordinata y del proiettile
 *
 * input=6
 * ritorna la coordinata x del proiettile
 *
 * input=7
 * ritorna un booleano che indica se il proiettile sta venendo disegnato
 *
 * input=8
 * ritorna l'ultima direzione guardata dal giocatore
 *
 * input=9
 * ritorna la direzione in cui ha viaggiato l'ultimo proiettile disegnato
 *
 * input=10
 * ritorna un booleano che indica se il giocatore sta saltando
 *
 * input=11
 * ritorna il numero di soldi del giocatore
 *
 * altri input:
 * ritorna -1
 *
 */
int player::playeroutput(int input){
	switch(input){
	case 0:
		return yLoc;
		break;
	case 1:
		return xLoc;
		break;
	case 2:
		return originy;
		break;
	case 3:
		return originx;
		break;
	case 4:
		return life;
		break;
	case 5:
		return projy;
		break;
	case 6:
		return projx;
		break;
	case 7:
		return s;
		break;
	case 8:
		return dir;
		break;
	case 9:
		return dirlock;
		break;
	case 10:
		return j;
		break;
	case 11:
		return money;
		break;
	default:
		return -1;
		break;
	}
}