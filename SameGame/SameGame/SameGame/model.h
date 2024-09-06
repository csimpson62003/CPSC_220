#ifndef MODEL_H
#define MODEL_H

#include <vector>
using namespace std;

enum Colors;


class GameBoard {

private:
	Colors board[5][5];
	void fillBoard();
	
public:
	
	GameBoard();
	Colors getColor(int row, int col);
	void setColor(int row, int col, Colors color);
	bool isValidHit(int row, int col);
	void remove(int row, int col);
	bool stillFloatingColors();
	bool stillColors();
};


enum Colors {
	Red,
	Green,
	Blue,
	Empty
};


#endif