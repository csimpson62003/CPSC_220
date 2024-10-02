#ifndef VIEW_H
#define VIEW_H

#include "model.h"
#include <iostream>
#include "model.h"
#include "view.h"
#include "raylib.h"
#include "Square.h"
#include <vector>
#include <string>
#include <cstdlib>  // For rand()
#include <ctime>    // For seeding rand()
using namespace std;
class view {
private:
	GameBoard *board;
	vector<Square*>shapes;
public:
	view(GameBoard& gb);
	void display();
	void addSquaresToVector();
	Color view::colorsToColor(Colors color);
};


#endif