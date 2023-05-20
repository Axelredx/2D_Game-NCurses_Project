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
	saveFile <<"map#"<< dataInt << endl;

	dataInt= P->playeroutput(12);
	saveFile << "jumpH#" << dataInt << endl;

	saveFile.close();

	return 1;
}
//void read_data(){};


void copyFile(string oldFileName, string newFileName)
{
	ifstream oldFile;
	oldFile.open(oldFileName);

	ofstream newFile;
	newFile.open(newFileName);

	string jojo;

	while(!oldFile.eof())
	{
		getline(oldFile, jojo);
		newFile << jojo << endl;
	}

	oldFile.close();
	newFile.close();

}



void changeData_basic(int itemNum, string content)
{
	/*
	 * ITA: itemNum corrisponde al dato che si vuole modificare; la funzione naviga 1 volta il file fino alla riga corretta, e modifica il dato
	 * content è una stringa corrispondente a ciò che va scritto sul file al posto del precedente dato; il formato stringa è per semplificare la funzione
	 * ENG: itemNum corresponds to the to be modified data; the function navigates through the file once, until the right row is reached, then it modifies the data
	 * content is a string corresponding to what is to be written on the file instead of the precedent data; the string format was chosen to simplify the function
	 */
	ifstream File;
	ofstream oFile;
	File.open("savegame.txt");
	oFile.open("copy.txt");
	string lookOut="";

	switch(itemNum){
	case 1:
		lookOut="Y_loc#";
		break;
	case 2:
		lookOut="X_loc#";
		break;
	case 3:
		lookOut="life#";
		break;
	case 4:
		lookOut="credits#";
		break;
	case 5:
		lookOut="map#";
		break;
	default:
		break;
	}

	//cout << "current lookout= " << lookOut << endl;

	if(lookOut.compare("")==0)
	{
		//cout << "error,  current lookOut variable is invalid" << endl;
	}else
	{
		string kek;
		int sus=-1;
		while(!File.eof())
		{
			getline(File,kek);
			sus=kek.find(lookOut);
			if(sus != (int)string::npos)
			{

				kek.replace(sus+lookOut.length(), string::npos, content);

			}
			oFile << kek << endl;
		}
		oFile.close();
		File.close();
		//elimina vecchio file
		//crea una funzione per la copia di un file
		//richiamala per ricopiare saveGame
		//elimina la copia del file;

		remove("savegame.txt");
		copyFile("copy.txt", "savegame.txt");
		remove("copy.txt");
	}
}

int obtain_data(int kek)
{
	string lookOut;
	switch (kek){
	case 1:	//player x
		lookOut="X_loc#";
	break;
	case 2: // player y
		lookOut="Y_loc#";
	break;
	case 3:	//player life
		lookOut="life#";
	break;
	case 4:	//player credits
		lookOut="credits#";
	break;
	case 5:
		lookOut="map#";
	break;
	default:
		return -4;
	break;
	}
	ifstream inFile;
	inFile.open("savegame.txt");
	string uwu="";
	if(inFile.is_open())
	while(!inFile.eof())
	{
		getline(inFile, uwu, '#');
		if(uwu.compare(lookOut)==0)
		{
			getline(inFile, uwu, '\n');
			break;
		}else
		{
			getline(inFile, uwu, '\n');
			uwu="";
		}

	}

	if(uwu.compare("")==0)
		return -1;
	else
		return stoi(uwu);

	return -1;
}
