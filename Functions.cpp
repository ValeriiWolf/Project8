#include <iostream>
#include <random>
#include <stdlib.h>
#include <chrono>
#include "Functions.h"

using namespace std;


int32_t getRundomNum(size_t min, size_t max)
{
	const static auto seed = chrono::system_clock::now().time_since_epoch().count();
	static mt19937_64 generator(seed);
	uniform_int_distribution<int32_t> dis(min, max);
	return dis(generator);
};

void initField(Field& r)
{
	r.ppField = new Cell * [r.SIZE];
	for (size_t i = 0; i < r.SIZE; i++)
		r.ppField[i] = new Cell[r.SIZE];
	for (size_t y = 0; y < r.SIZE; y++)
		for (size_t x = 0; x < r.SIZE; x++)
			r.ppField[y][x] = Empty;

	if (getRundomNum(0, 1000) > 500)
	{
		r.Human = Krest;
		r.aI = Zero;
		r.turn = 0;
	}
	else
	{
		r.Human = Zero;
		r.aI = Krest;
		r.turn = 1;
	}
};

void printField(const Field& r)
{
	cout << endl << "     ";
	for (size_t x = 0; x < r.SIZE; x++)
		cout << x + 1 << "   ";
	cout << endl;
	for (size_t y = 0; y < r.SIZE; y++)
	{
		cout << " " << y + 1 << " |";
		for (size_t x = 0; x < r.SIZE; x++)
			cout << " " << static_cast <char> (r.ppField[y][x]) << " |";
		cout << endl;
	}
	cout << endl << "Human: " << static_cast <char>(r.Human) << endl;
	cout << "   AI: " << static_cast <char>(r.aI) << endl << endl;
};

void deinitField(Field& r)
{
	for (size_t i = 0; i < r.SIZE; i++)
		delete[] r.ppField[i];

	delete[] r.ppField;
	r.ppField = nullptr;
};

int getIntNumber(char x)
{
	while (true)
	{
		int num;
		cout << "Enter integer " << x << " (ot 1 do 3) : ";
		cin >> num;
		if (num < 1 || num > 3 || cin.fail())
		{
			cout << "Error. Please enter an integer number ot 1 do 3!" << endl;
			cin.clear();
			cin.ignore(32767, '\n');
		}
		else
		{
			return num;
		}
	}
};

Coord getHumanCoord(Field& f)
{
	char x = 'x', y = 'y';
	Coord c;
	do
	{
		c.x = getIntNumber(x);
		c.y = getIntNumber(y);
		if (f.ppField[c.y - 1][c.x - 1] != Empty)
		{
			cout << "Error! This cell busy!" << endl;
		}
	} while (f.ppField[c.y - 1][c.x - 1] != Empty);
	c.x--;
	c.y--;
	return c;
};
Progress getWon(const Field& f);
Coord getAICoord(Field& f)
{
	for (size_t y = 0; y < f.SIZE; y++)
	{
		for (size_t x = 0; x < f.SIZE; x++)
		{
			if (f.ppField[y][x] == Empty)
			{
				f.ppField[y][x] = f.aI;
				if (getWon(f) == WON_AI)
				{
					f.ppField[y][x] = Empty;
					return { y, x };
				}
				f.ppField[y][x] = Empty;
			}
		}
	}
	for (size_t y = 0; y < f.SIZE; y++)
	{
		for (size_t x = 0; x < f.SIZE; x++)
		{
			if (f.ppField[y][x] == Empty)
			{
				f.ppField[y][x] = f.Human;
				if (getWon(f) == WON_HUMAN)
				{
					f.ppField[y][x] = Empty;
					return { y, x };
				}
				f.ppField[y][x] = Empty;
			}
		}
	}
	if (f.ppField[1][1] == Empty)
	{
		return{ 1, 1 };
	}
	const size_t DLI = 4;
	Coord arrUg[DLI] = { 0 };
	size_t num = 0;
	if (f.ppField[0][0] == Empty)
	{
		arrUg[num++] = { 0, 0 };
	}
	if (f.ppField[0][2] == Empty)
	{
		arrUg[num++] = { 0, 2 };
	}
	if (f.ppField[2][0] == Empty)
	{
		arrUg[num++] = { 2, 0 };
	}
	if (f.ppField[2][2] == Empty)
	{
		arrUg[num++] = { 2, 2 };
	}

	if (num > 0)
	{
		const size_t index = getRundomNum(0, 1000) % num;
		return arrUg[index];
	}
	num = 0;
	if (f.ppField[0][1] == Empty)
	{
		arrUg[num++] = { 0, 1 };
	}
	if (f.ppField[1][2] == Empty)
	{
		arrUg[num++] = { 1, 2 };
	}
	if (f.ppField[2][1] == Empty)
	{
		arrUg[num++] = { 2, 1 };
	}
	if (f.ppField[1][0] == Empty)
	{
		arrUg[num++] = { 1, 0 };
	}

	if (num > 0)
	{
		const size_t index = getRundomNum(0, 1000) % num;
		return arrUg[index];
	}
	return{ 0, 0 };

};

Progress getWon(const Field& f)
{
	for (size_t y = 0; y < f.SIZE; y++)
	{
		if (f.ppField[y][0] == f.ppField[y][1] && f.ppField[y][0] == f.ppField[y][2])
		{
			if (f.ppField[y][0] == f.aI)
			{
				return WON_AI;
			}
			else if (f.ppField[y][0] == f.Human)
			{
				return WON_HUMAN;
			}
		}
	}
	for (size_t x = 0; x < f.SIZE; x++)
	{
		if (f.ppField[0][x] == f.ppField[1][x] && f.ppField[1][x] == f.ppField[2][x])
		{
			if (f.ppField[0][x] == f.aI)
			{
				return WON_AI;
			}
			else if (f.ppField[0][x] == f.Human)
			{
				return WON_HUMAN;
			}
		}
	}
	if (f.ppField[0][0] == f.ppField[1][1] && f.ppField[1][1] == f.ppField[2][2] || f.ppField[2][0] == f.ppField[1][1] && f.ppField[1][1] == f.ppField[0][2])
	{
		if (f.ppField[1][1] == f.aI)
		{
			return WON_AI;
		}
		else if (f.ppField[1][1] == f.Human)
		{
			return WON_HUMAN;
		}
	}
	bool draw = true;
	for (size_t y = 0; y < f.SIZE; y++)
	{
		for (size_t x = 0; x < f.SIZE; x++)
		{
			if (f.ppField[y][x] == Empty)
			{
				draw = false;
				break;
			}
		}
		if (!draw)
		{
			break;
		}
	}
	if (draw)
	{
		return DRAW;
	}
	return IN_PROGRESS;
};

void grats(Progress progress)
{
	if (progress == WON_HUMAN)
	{
		cout << "Human won!" << endl;
	}
	else if (progress == WON_AI)
	{
		cout << "Computer won!" << endl;
	}
	else if (progress == DRAW)
	{
		cout << "Draw!=/" << endl;
	}
};
