#include <iostream>
#include <ncurses.h>
#include <cstring>
#include <string>
#include <ctime>
#include <fstream>
#include "market.hpp"
using namespace std;

int save_data(player* P, int Seed, string filename);
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

void changeData_basic(int itemNum, string content);

void copyFile(string oldFileName, string newFileName);

int obtain_data(int kek);