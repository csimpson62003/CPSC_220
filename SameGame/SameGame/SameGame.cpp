// SameGame.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "model.h"
#include "view.h"

using namespace std;

void play();

int main()
{
    play();

}

void play() {
    GameBoard gb;
    view view(gb);
   int numberOfMoves = 0;
    cout << "Welcome to the Same Game!... Where the goal is to remove all of the colors. Lets get started!\n\n" << endl;
    while (1) {
        view.display();
        cout << "Enter the Row of the color you want to hit" << endl;
        int rowInput;
        cin >> rowInput;
        cout << "Enter the Column of the color you want to hit" << endl;
        int colInput;
        cin >> colInput;
        if (!gb.isValidHit(rowInput, colInput)) {
            cout << "You entered in invalid coordinates. Try again" << endl;
            continue;
        }

        else {
            gb.remove(rowInput, colInput);
            while (gb.stillFloatingColors()) {
                gb.stillFloatingColors();
                cout << "hello" << endl;
            }

            numberOfMoves++;
        }
        if (gb.stillColors() == false) {
            cout << "Your done! It took you " << numberOfMoves << " tries!" << endl;
            return;
        }
    }


}



  
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
