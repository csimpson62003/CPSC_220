#include "view.h"
#include <iostream>
#include "model.h"

using namespace std;

view::view(GameBoard& board) {
    this->board = &board;
}
string colorToString(Colors color) {
    switch (color) {
    case Colors::Red: return "R";
    case Colors::Green: return "G";
    case Colors::Blue: return "B";
    case Colors::Empty: return " ";
    default: return " ";
    }
}

void view::display() {
    cout  << "    ";
    for (int col = 0; col < 5; col++) {
        cout << col << " ";
    }
    cout << endl;
    for (int col = 0; col < 4; col++) {
        cout << "---";
    }
    cout << endl;
    for (int row = 0; row < 5; row++) {
        cout << row << " | ";
        for (int col = 0; col < 5; col++) {
            cout << colorToString(board->getColor(row, col)) << " ";
        }
        cout << endl;
    }
}