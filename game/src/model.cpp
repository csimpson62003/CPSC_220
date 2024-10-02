#include "model.h"
#include <vector>
#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;


GameBoard::GameBoard() {
	fillBoard();
}

Colors GameBoard::getColor(int row, int col) {
	Colors c = board[row][col];
	return c;
}

void GameBoard::fillBoard() {
	srand(time(NULL));
	for (int row = 0; row < 5; row++) {
		for (int col = 0; col < 5; col++) {
			int colorOption = rand() % 3+1;
			switch (colorOption)
			{
			case 1:
				board[row][col] = Colors::Red;
				break;
			case 2:
				board[row][col] = Colors::Blue;
				break;
			case 3:
				board[row][col] = Colors::Green;
				break;

			default:
				board[row][col] = Colors::Empty;
				break;
			}
		}
	}
}

void GameBoard::setColor(int row, int col, Colors color) {
	board[row][col] = color;
}

bool GameBoard::isValidHit(int row, int col)
{
	if (row > 4 || col > 4) {
		return false;
	}
	if (board[row][col] != Colors::Empty) {
		return true;
	}
	return false;
}

void GameBoard::remove(int row, int col)
{
	Colors squareColor = board[row][col];
	board[row][col] = Colors::Empty;
	if (row > 0){
		if (board[row - 1][col] == squareColor) {
			remove(row - 1, col);
		}
	}
	if (row < 4) {
		if (board[row + 1][col] == squareColor) {
			remove(row + 1, col);
		}
	}
	if (col > 0) {
		if (board[row][col - 1] == squareColor) {
			remove(row, col - 1);
		}
	}
			if (col < 4) {
				if (board[row][col + 1] == squareColor) {
					remove(row, col + 1);
				}
			}
		}

bool GameBoard::stillFloatingColors() {
	for (int col = 0; col < 5; col++) {
		bool foundColor = false;
		for (int row = 0; row < 5; row++) {
			if (!foundColor && board[row][col] != Colors::Empty) {
				foundColor = true;
				continue;
			}
			if (foundColor && board[row][col] == Colors::Empty) {
				if (row != 0) {
					board[row][col] = board[row - 1][col];
					board[row - 1][col] = Colors::Empty;
					return true;
				}
			}
		}
	}
	return false;
}
bool GameBoard::stillColors() {
	for (int row = 0; row < 5; row++) {
		for (int col = 0; col < 5; col++) {
			if (Colors::Empty != board[row][col]) {
				return true;
			}
		}
	}
	return false;
}
