#ifndef VIEW_H
#define VIEW_H

#include "model.h"

class view {
private:
	GameBoard *board;
public:
	view(GameBoard& gb);
	void display();
};


#endif