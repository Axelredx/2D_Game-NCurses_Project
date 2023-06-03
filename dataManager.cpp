#include "dataManager.hpp"

/*
 * Save data takes the player item, a seed item, and a filename for the new/to-be updated
 * saved games data, and store position, life and money of the player
 * saves the current map seed
 */
int save_data(player* P, int Seed, int game_scr, string fileName, string enemyID, basicenemy* E)
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

	int dataInt;
	if(!filesystem::exists(fileName)){		//se il file non esiste, crea un nuovo file

		ofstream log;
		log.open("logFile.txt");

		log << "savegame not located, writing new file" << endl;

		ofstream saveFile;	//crea variabile di appoggio del file
		saveFile.open(fileName);	//apre (o crea se non esiste) il file

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

		saveFile <<"score#" <<game_scr << endl;

		saveFile << endl;

		saveFile << "-- ENEMY LOG --" << endl;


		string kek;
		kek="lvl#"+to_string(Seed)+"/Enemy#"+enemyID+"/X#"+to_string(E->enemyOutput(1))+"/life#"+to_string(E->enemyOutput(4))+"/";
		saveFile << kek;
		//in questo caso il funzionamento è un po' scuffed, ma funziona
		//in quanto buon informatico, finché funziona, non si tocca

		saveFile.close();
		log.close();
		return 1;
	}else
	{
		copyFile(fileName, "temp.txt");

		//remove(fileName.c_str());		//it works trust me

		enemyDataSave(fileName, "temp.txt", Seed, enemyID, E);

		return 2;
	}
	return -1;
}


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



void changeData_basic(int itemNum, string content)	//cambia il valore di uno specifico dato NO NEMICI
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

int obtain_data(int kek)	//ottieni il valore intero di uno specifico dato NO NEMICI
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

int enemyDataSave (string fileName, string tempFileName,  int seed, string enemyID, basicenemy* E)	//cambia il valore di uno specifico dato NO NEMICI
{
	/*
	 * La funzione deve copiare riga per riga il tempFile, sul nuovo file di salvataggio
	 * La differenza è che analizza le righe una ad una per cercare informazioni sul livello attuale e sul suo nemico
	 * non appena trova una riga corrispondente al livello nel quale siamo, aggiorna le info del nemico con la situazione attuale.
	 * invece di copiare la riga quindi, la modifica
	 * se non viene trovata nessuna riga precedente riguardante il livello attuale, crea una nuova riga
	 */
	ifstream iFile; 	//file dal quale leggo
	ofstream oFile;		//file sul quale scrivo
	iFile.open(tempFileName);
	oFile.open(fileName);
	string lookOut="lvl#"+to_string(seed);
	bool found=false;

	ofstream logFile;
	logFile.open("logFile.txt");

	if(lookOut.compare("")==0)
	{
		logFile << "no lookout in enemyDataSave" << endl;
		//cout << "error,  current lookOut variable is invalid" << endl;
	}else
	{

		logFile << "current lookout is: " << lookOut << endl;

		string kek;
		int linecounter=0;
		int printcounter=0;

		while(!iFile.eof() && linecounter<100)
		{

			getline(iFile,kek);
			linecounter++;

			if( string::npos != (kek.find(lookOut)))
			{
				logFile << "lookout has been found, modifying current line" << endl;

				found = true;
				kek="";
				//azzero per sicurezza
				kek="lvl#"+to_string(seed)+"/Enemy#"+enemyID+"/X#"+to_string(E->enemyOutput(1))+"/life#"+to_string(E->enemyOutput(4))+"/";

				logFile << "modified kek string is: " << kek;
			}
			oFile << kek ;

			if(kek.compare("") != 0)
				oFile << endl;

			printcounter++;
		}

		if(found==false)	//add new line if no previous data exists
		{
			logFile << "having not found the enemy data, a new line of data will be written" << endl;

			kek="lvl#"+to_string(seed)+"/Enemy#"+enemyID+"/X#"+to_string(E->enemyOutput(1))+"/life#"+to_string(E->enemyOutput(4))+"/";
			oFile << kek << endl;

			logFile << "kek:" << kek << endl;
		}

		oFile.close();
		iFile.close();
		logFile.close();
		//elimina vecchio file
		//crea una funzione per la copia di un file
		//richiamala per ricopiare saveGame
		//elimina la copia del file;

		remove(tempFileName.c_str());
	}
	return 0;
}