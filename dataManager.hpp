#include <iostream>
#include <ncurses.h>
#include <cstring>
#include <string>
#include <ctime>
#include <fstream>
#include "market.hpp"
#include "basicEnemy.hpp"
#include <filesystem>
using namespace std;


int save_data(player* P, int Seed, int game_scr, string fileName, basicenemy* E);
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


//void read_data(){}

int enemyDataSave (string fileName, string tempFileName, int seed, string enemyID, basicenemy* E);

void changeData_basic(int itemNum, string content);

void copyFile(string oldFileName, string newFileName);

int obtain_data(int kek, int map=-1);

int newEnemyDataSave (ofstream &mainFile, ifstream &supportFile,  int seed, basicenemy* E);