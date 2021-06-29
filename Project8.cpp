#include <iostream>
#include <random>
#include <stdlib.h>
#include <chrono>
#include "Functions.h"

using namespace std;

void inline clearScr()
{
	system("cls");
};

int main()
{
	Field f;
	initField (f);
	clearScr();
	printField(f);
	do {
		if (f.turn % 2 == 0)
		{	
			Coord c = getHumanCoord(f);
			f.ppField[c.y][c.x] = f.Human;
		}
		else 
		{
			Coord c = getAICoord(f);
			f.ppField[c.y][c.x] = f.aI;
		}

		f.turn++;

		clearScr();
		printField(f);
		f.progress = getWon(f);
	} while(f.progress==IN_PROGRESS);

	grats(f.progress);

	deinitField(f);
	return 0;
}
