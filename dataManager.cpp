#include "dataManager.hpp"

/*
 * Save data takes the player item, a seed item, and a filename for the new/to-be updated
 * saved games data, and store position, life and money of the player
 * saves the current map seed
 */


/*
 * ERROR LIST
 *
 * -1: error in savedata when updating an already existing file
 * -2: error in obtainData, the wanted data from player does not exist
 * -3: error in newEnemyDataSave, something went wrong
 * -4: error in obtainData: the lookout (palyer) could not bet correctly resolved
 * -5: free of usage
 * -6_ error in obrainData, the corresponding enemy line does not contain the searched value
 * -7: error in obtainData, the wanted data does not exist
 * -8: error in obtainData, the lookout (enemy) could not be correctly resolved
 * -9: free of usage
 *
 * */




int save_data(player* P, int Seed, int game_scr, string fileName, basicenemy* E)
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
		kek="lvl#"+to_string(Seed)+"/Enemy#"+(char) (E->enemyOutput(8))+"/X#"+to_string(E->enemyOutput(1))+"/life#"+to_string(E->enemyOutput(4))+"/";
		saveFile << kek;
		//in questo caso il funzionamento è un po' scuffed, ma funziona
		//in quanto buon informatico, finché funziona, non si tocca

		saveFile.close();
		log.close();
		return 1;
	}else
	{
		copyFile(fileName, "temp.txt");

		remove(fileName.c_str());

		ofstream saveFile;
		saveFile.open(fileName);

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
		//remove(fileName.c_str());		//it works trust me

		ifstream supportFile;
		supportFile.open("temp.txt");
		return newEnemyDataSave(saveFile, supportFile, Seed, E);

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
		string kek = "";
		int sus=-1;
		while(!File.eof() && kek.compare("-- ENEMY LOG --") != 0)
		{
			getline(File,kek);
			sus=kek.find(lookOut);
			if(sus != (int)string::npos)
			{

				kek.replace(sus+lookOut.length(), string::npos, content);

			}
			oFile << kek << endl;
		}

		while(!File.eof())
		{
			getline(File,kek);
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

int obtain_data(int kek, int map)	//ottieni il valore intero di uno specifico dato
{


	string lookOut;

	if(map==-1){
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
			return -2;
		else
			return stoi(uwu);

		}
	else{	//caso in cui sono stati inseriti i dati relativi alla classe enemy, si andrà a cercare i suoi dati
		switch(kek){
		case 0:
			lookOut = "yLoc#";
			break;
		case 1:
			lookOut = "xLoc#";
			break;
		case 2:
			lookOut = "life#";
			break;
		case 3:
			lookOut = "money#";
			break;
		case 4:
			lookOut = "Enemy#";
			break;
		default:
			return -8;
			break;
		}	//lookout tiene conto del dato da cercare

		ifstream file;
		file.open("savegame.txt");
		string ostia;

		do{
			getline(file, ostia);
		}while(ostia.compare("-- ENEMY LOG --") != 0);	//scorre fino a superare la parte di file con solo dati del player

		bool found = false;

		string tmp = "";
		do{
			getline(file, ostia);
			if(ostia.find("lvl#" + to_string(map)) != string::npos){

				int mhenz = ostia.find(lookOut); //posizione della parola cercata

				if((int)string::npos != mhenz)
				{
					tmp = ostia.substr(mhenz + lookOut.length());

					found = true;

					tmp = tmp.substr(0, tmp.find('/') );
				}else
				{
					return -6;
				}
			}
		}while(!file.eof() || !found);

		if(found)
		{
			if(tmp.length() == 1 ){
				char pain = tmp.at(0);
				//cout << "pain" << endl;
				return (int)pain;
			}
			else
				return stoi(tmp);
		}else
			return -6;
	}
	return -7;
}
/*
int enemyDataSave (string fileName, string tempFileName,  int seed, string enemyID, basicenemy* E)	//cambia il valore di uno specifico dato NO NEMICI
{
	ifstream iFile; 	//file dal quale leggo
	ofstream oFile;		//file sul quale scrivo
	iFile.open(tempFileName);
	oFile.open(fileName);
	string lookOut="lvl#"+to_string(seed);
	bool found=false;
	ofstream logFile;
	logFile.open("logFile.txt");
	string kek = "";
	do{
		getline(iFile, kek);
	}while(string::npos != (kek.find("-- ENEMY LOG --")));
	if(lookOut.compare("")==0)
	{
		logFile << "no lookout in enemyDataSave" << endl;
		//cout << "error,  current lookOut variable is invalid" << endl;
	}else
	{
		logFile << "current lookout is: " << lookOut << endl;
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
}*/

int newEnemyDataSave (ofstream &mainFile, ifstream &supportFile,  int seed, basicenemy* E)
{

	string kek = "";


	do{
		getline(supportFile, kek);

	}while(string::npos == (kek.find("-- ENEMY LOG --")));	//scorre il file copiato fino alla parte dei nemici

	kek = "";

	string lookOut="lvl#"+to_string(seed);

	bool found = false;

	if(lookOut.compare("")==0)
	{
		return -2;
		//cout << "error,  current lookOut variable is invalid" << endl;
	}else
	{
		while(!supportFile.eof())
		{

			getline(supportFile,kek);

			if( string::npos != (kek.find(lookOut)))
			{
				found = true;
				kek="";
				//azzero per sicurezza
				kek = "lvl#" + to_string(seed) + "/Enemy#" + (char)(E->enemyOutput(8)) + "/X#" + to_string(E->enemyOutput(1)) + "/life#" + to_string(E->enemyOutput(4)) + "/" ;

			}
			mainFile << kek ;

			if(kek.compare("") != 0)
				mainFile << endl;
		}

		if(found==false)	//add new line if no previous data exists
		{
			kek = "lvl#" + to_string(seed) + "/Enemy#" + (char)(E->enemyOutput(8)) + "/X#" + to_string(E->enemyOutput(1)) + "/life#" + to_string(E->enemyOutput(4)) + "/";
			mainFile << kek << endl;
		}

		mainFile.close();
		supportFile.close();
		return 2;
	}
	return -3;
}