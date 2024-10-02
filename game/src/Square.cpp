#include "Square.h";
#include "raylib.h"



Square::Square(int x, int y, int w, int h, Color c) {
	this->x = x;
	this->y = y;
	this->width = w;
	this->height = h;
	this->c = c;
}

void Square::draw() {
	DrawRectangle(x, y, width, height, c);
}