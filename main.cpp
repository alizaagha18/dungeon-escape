#include "../headers/headers.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <stack>
int main() {
    string playerName;
    cout << "Enter your name: ";
    cin >> playerName;
    Player player(playerName);

    Dungeon dungeon;
    dungeon.displayRules();

    char choice;
    while (player.getHealth() >= 20 && player.getMoves() > 0) {
        cout << "\nHealth: " << player.getHealth() << " | Moves: " << player.getMoves() << endl;
        cout << "Press R to go to next room, L to backtrack, or Q to quit: ";
        cin >> choice;
        if (choice == 'R' || choice == 'r') {
            dungeon.enterRoom(player);
        } else if (choice == 'L' || choice == 'l') {
            dungeon.backtrack(player);
        } else if (choice == 'Q' || choice == 'q') {
            break;
        }
    }

    // Game over
    if (player.getHealth() < 20) {
        cout << "\nGame Over! Your health dropped below 20.\n";
    } else if (player.getMoves() == 0) {
        cout << "\nGame Over! You ran out of moves.\n";
    } else {
        cout << "\nCongratulations! You escaped the dungeon!\n";
    }

    // Display ranking
    dungeon.displayRanking(player);

    // Play again option
    cout << "\nPlay again? (Y/N): ";
    cin >> choice;
    if (choice == 'Y' || choice == 'y') {
        main(); // Restart the game
    }

}