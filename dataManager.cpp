#include "dataManager.hpp"

/*
 * Save data takes the player item, a seed item, and a filename for the new/to-be updated
 * saved games data, and store position, life and money of the player
 * saves the current map seed
 */

int save_data(player* P, int Seed, string fileName)
{
	/*
	 * MEMO: savegame structure as follows (WIP)
	 * Line1: yloc (code 0)
	 * Line2: xLoc (code 1)
	 * Line3: Life (code 4)
	 * Line4: money (code 11)
	 * Line5: map seed
	 *
	 *
	 *
	 */


	ofstream saveFile;	//crea variabile di alloggio del file
	saveFile.open(fileName);	//apre (o crea se non esiste) il file
	int dataInt;
	char dataChar [20];

	dataInt=P->playeroutput(0);	//get_y
	saveFile << dataInt ;
	saveFile << endl;

	dataInt=P->playeroutput(1);	//get_x
	saveFile << dataInt << endl;

	dataInt = P->playeroutput(4);	//get_life
	saveFile << dataInt << endl;

	dataInt = P->playeroutput(11);	//get_credits
	saveFile << dataInt << endl;

	dataInt = Seed;					//get_mapSeed
	saveFile << Seed << endl;

	saveFile.close();

	return 1;
}
//void read_data(){};