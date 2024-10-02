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

view::view(GameBoard& board) {
    this->board = &board;
    

}
void view::addSquaresToVector() {
    shapes.clear();
    for (int height = 0; height < 5; height++) {
        for (int width = 0; width < 5; width++) {
            Color c = colorsToColor(board->getColor(width, height));
            shapes.push_back(new Square(height * 200, width * 200, 200, 200, c));
        }
    }
}

Color view::colorsToColor(Colors color) {
    switch (color) {
    case Colors::Red: return RED;
    case Colors::Green: return GREEN;
    case Colors::Blue: return BLUE;
    case Colors::Empty: return WHITE;
    default: return DARKPURPLE;
    }
}

    void view::display() {
        addSquaresToVector();
        for (Square *shape:shapes) {
            shape->draw();
        }
    }