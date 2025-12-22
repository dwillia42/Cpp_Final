#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cctype>
#include <vector>
#include <limits>

#include "TicTacToe.h"

using namespace std;


void printBoard(vector<vector<char>> minigameBoard, int& rounds) {
    cout << "   1   2   3\n"
            "1 [" << minigameBoard.at(0).at(0) << "] [" << minigameBoard.at(0).at(1) << "] [" << minigameBoard.at(0).at(2) << "]\n"
            "2 [" << minigameBoard.at(1).at(0) << "] [" << minigameBoard.at(1).at(1) << "] [" << minigameBoard.at(1).at(2) << "]\n"
            "3 [" << minigameBoard.at(2).at(0) << "] [" << minigameBoard.at(2).at(1) << "] [" << minigameBoard.at(2).at(2) << "]\n"
    << endl;
    rounds++;
}

bool WinCheck(vector<vector<char>> minigameBoard, char playerLetter, bool& playerWin) {
    if (minigameBoard.at(0).at(0) == minigameBoard.at(1).at(1) && minigameBoard.at(1).at(1) == minigameBoard.at(2).at(2)) {
        if (minigameBoard.at(0).at(0) == playerLetter) {
            playerWin = true;
        }
        return true;
    }
    if (minigameBoard.at(2).at(0) == minigameBoard.at(1).at(1) && minigameBoard.at(1).at(1) == minigameBoard.at(0).at(2)) {
        if (minigameBoard.at(2).at(0) == playerLetter) {
            playerWin = true;
        }
        return true;
    }
    for (int i = 0; i < 3; i++) {
        if (minigameBoard.at(i).at(0) == minigameBoard.at(i).at(1) && minigameBoard.at(i).at(1) == minigameBoard.at(i).at(2)) {
            if (minigameBoard.at(i).at(0) != ' ') {
                if (minigameBoard.at(i).at(0) == playerLetter) {
                    playerWin = true;
                }
                return true;
            }
        }
        if (minigameBoard.at(0).at(i) == minigameBoard.at(1).at(i) && minigameBoard.at(1).at(i) == minigameBoard.at(2).at(i)) {
            if (minigameBoard.at(0).at(i) != ' ') {
                if (minigameBoard.at(0).at(i) == playerLetter) {
                    playerWin = true;
                }
                return true;
            }
        }
    }
    return false;
}

void EnemyTurn(vector<vector<char>>& minigameBoard, char enemy) {
    int x = rand() % 3,
        y = rand() % 3;
    
    if (minigameBoard.at(x).at(y) == ' ') {
        cout << endl << "* Veris\' move:" << endl;
        minigameBoard.at(x).at(y) = enemy;
    }
    else {
        EnemyTurn(minigameBoard, enemy);
    }
}

void markBoard(vector<vector<char>>& minigameBoard, int x, int y, char player) {
    minigameBoard.at(x).at(y) = player;
}

string startTicTacToe() {
    
    vector<vector<char>> minigameBoard = {
        {' ', ' ', ' '},
        {' ', ' ', ' '},
        {' ', ' ', ' '}
    };
    
    srand(static_cast<unsigned int>(time(0)));
    
    int x = -1,
        y = -1;
    
    const char playerLetter = 'X',
               enemyLetter = 'O';
    
    bool playerWin = 0;
    
    int rounds = 0;
    
    /*for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            minigameBoard[i][j] = ' ';
        }
    }*/
    //not needed i think
    
    minigameBoard.at(1).at(1) = 'O';
    
    //veris too important to go second, also it'd be too easy if player went middle first
    
    cout << "* \"Well, I'm going first, obviously.\"" << endl << endl;
    
    printBoard(minigameBoard, rounds);
    
    while (WinCheck(minigameBoard, playerLetter, playerWin) == false && rounds < 9) {
        cout << "* Type row, then column (separated by a space):" << endl << endl << "> ";
        cin >> x >> y;
        if (cin.fail()) {
            cout << endl << "* \"Hey, no cheating, if I'm not allowed to!\"" << endl << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }
        if (x > 3 || x < 1 || y > 3 || y < 1 || minigameBoard.at(x-1).at(y-1) != ' ') {
            cout << endl << endl << "* Invalid space. Try again." << endl << endl;
            continue;
        }
        markBoard(minigameBoard, x-1, y-1, playerLetter);
        cout << endl << "Player's move:" << endl;
        printBoard(minigameBoard, rounds);
        if (WinCheck(minigameBoard, playerLetter, playerWin) == false) {
            EnemyTurn(minigameBoard, enemyLetter);
            printBoard(minigameBoard, rounds);
        }
    }
    if (WinCheck(minigameBoard, playerLetter, playerWin) == false) {
        cout << endl << "* Its a draw." << endl;
        return "veris_Win";
    }
    else if (playerWin == false) {
        cout << endl <<  "* Veris won." << endl;
        return "veris_Win";
    }
    else {
        cout << endl << "* You won." << endl;
        return "player_Win";
    }

}
