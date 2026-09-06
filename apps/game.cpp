#include "../edora.h"
#include "game.h"

#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

void game()
{
    srand(static_cast<unsigned int>(time(nullptr)));

    int secret = rand() % 100 + 1;
    int guess;
    int attempts = 0;

    cout << "\n";
    cout << "============================================\n";
    cout << "              EDORA GAME\n";
    cout << "============================================\n";
    cout << "Guess the number from 1 to 100.\n";
    cout << "Type 0 to exit.\n";
    cout << "--------------------------------------------\n";

    while (true)
    {
        cout << "Guess: ";
        cin >> guess;

        if (guess == 0)
        {
            cin.ignore(10000, '\n');
            cout << "Game exited.\n";
            return;
        }

        attempts++;

        if (guess < secret)
        {
            cout << "Too low.\n";
        }
        else if (guess > secret)
        {
            cout << "Too high.\n";
        }
        else
        {
            cout << "\n";
            cout << "YOU WIN!\n";
            cout << "Number: " << secret << "\n";
            cout << "Attempts: " << attempts << "\n";

            cin.ignore(10000, '\n');
            return;
        }
    }
}