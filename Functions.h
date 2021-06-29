#pragma once

enum Cell {
	Krest = 'X',
	Zero = 'O',
	Empty = '_'
};

enum Progress {
	IN_PROGRESS,
	WON_HUMAN,
	WON_AI,
	DRAW
};

struct Coord {
	size_t y;
	size_t x;
};

#pragma pack(push, 1)
struct Field {
	const size_t SIZE = 3;
	Cell** ppField = nullptr;
	Cell Human = Empty;
	Cell aI = Empty;
	size_t turn = 0;
	Progress progress = IN_PROGRESS;
};
#pragma pack(pop)

int32_t getRundomNum(size_t min, size_t max);
void initField(Field& r);
void printField(const Field& r);
void deinitField(Field& r);
int getIntNumber(char x);
Coord getHumanCoord(Field& f);
Coord getAICoord(Field& f);
Progress getWon(const Field& f);
void grats(Progress progress);