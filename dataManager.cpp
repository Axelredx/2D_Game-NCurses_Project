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

	dataInt=P->playeroutput(0);	//get_y
	saveFile <<"Y_loc#"<<dataInt ;
	saveFile << endl;

	dataInt=P->playeroutput(1);	//get_x
	saveFile << "X_loc#"<<dataInt << endl;

	dataInt = P->playeroutput(4);	//gemt_life
	saveFile <<"life#" <<dataInt << endl;

	dataInt = P->playeroutput(11);	//get_credits
	saveFile <<"credits#" <<dataInt << endl;

	dataInt = Seed;					//get_mapSeed
	saveFile <<"map#"<< Seed << endl;

	dataInt= P->playeroutput(12);
	saveFile << "jumpH#" << dataInt << endl;

	saveFile.close();

	return 1;
}
//void read_data(){};