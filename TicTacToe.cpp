#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cctype>
#include <vector>
#include <limits>

#include "TicTacToe.h"

using namespace std;

//prints board and increments rounds
void printBoard(vector<vector<char>> minigameBoard, int& rounds) {
    cout << "   1   2   3\n"
            "1 [" << minigameBoard.at(0).at(0) << "] [" << minigameBoard.at(0).at(1) << "] [" << minigameBoard.at(0).at(2) << "]\n"
            "2 [" << minigameBoard.at(1).at(0) << "] [" << minigameBoard.at(1).at(1) << "] [" << minigameBoard.at(1).at(2) << "]\n"
            "3 [" << minigameBoard.at(2).at(0) << "] [" << minigameBoard.at(2).at(1) << "] [" << minigameBoard.at(2).at(2) << "]\n"
    << endl;
    rounds++;
    //rounds++ makes sure that the board stops being asked to be filled up even if noone wins and the board is full
    //better than using for loops to check that nobody wins
}

//checks every condition of a win to return whether someone won and also who specifically won
bool WinCheck(vector<vector<char>> minigameBoard, char playerLetter, bool& playerWin) {
    if (minigameBoard.at(0).at(0) == minigameBoard.at(1).at(1) && minigameBoard.at(1).at(1) == minigameBoard.at(2).at(2)) {
        if (minigameBoard.at(0).at(0) == playerLetter) {
            playerWin = true;
        }
        //player always playerLetter, only need to check one
        return true;
    }
    //checks down diagonal win
    if (minigameBoard.at(2).at(0) == minigameBoard.at(1).at(1) && minigameBoard.at(1).at(1) == minigameBoard.at(0).at(2)) {
        if (minigameBoard.at(2).at(0) == playerLetter) {
            playerWin = true;
        }
        return true;
    }
    //up diagonal
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
    //any horizontal and vertical win condition
    return false;
}

void EnemyTurn(vector<vector<char>>& minigameBoard, char enemy) {
    int x = rand() % 3,
        y = rand() % 3;
    //picks random between 0-2
    
    if (minigameBoard.at(x).at(y) == ' ') {
        cout << endl << "* Veris\' move:" << endl;
        minigameBoard.at(x).at(y) = enemy;
    }
    else {
        EnemyTurn(minigameBoard, enemy);
    }
    //only uses coordinaes if space isnt alr empty, if it is then redo function (recursive)
}

void markBoard(vector<vector<char>>& minigameBoard, int x, int y, char player) {
    minigameBoard.at(x).at(y) = player;
}

//both markbing board function uses reference variable to update the minigameBoard for future uses

string startTicTacToe() {
    
    vector<vector<char>> minigameBoard = {
        {' ', ' ', ' '},
        {' ', ' ', ' '},
        {' ', ' ', ' '}
    };
    //originally used a 2D matrix of chars but reference (&) wasn't working to update the char, also i thought .at was safer than [ ]
    
    srand(static_cast<unsigned int>(time(0)));
    //using static cast to match the type of value time(0) makes with what srand() uses to seed random with
    //time() emulates random better between sessions
    
    int x = -1,
        y = -1;
    //x is the row and y is the column for tictactoe board
    
    const char playerLetter = 'X',
               enemyLetter = 'O';
    
    //these have no reason to change, so i used const

    bool playerWin = 0;
    
    int rounds = 0;

    //these will be useful later
    
    /*for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            minigameBoard[i][j] = ' ';
        }
    }*/
    //i just decided to initialize with empty spaces, this is a relic from when i used a 2d matrix
    
    minigameBoard.at(1).at(1) = 'O';
    
    //veris too important to go second, also it'd be too easy if player went middle first
    
    cout << "* \"Well, I'm going first, obviously.\"" << endl << endl;

    
    printBoard(minigameBoard, rounds);
    
    //rounds condition prevents them from get stuck in a loop of looking for empty spaces
    while (WinCheck(minigameBoard, playerLetter, playerWin) == false && rounds < 9) {
        cout << "* Type row, then column (separated by a space):" << endl << endl << "> ";
        cin >> x >> y;
        //below is a trick dwann found, and is linked and commented on earlier
        //instead of using more variables and a while loop i just made it redo the loop from start with continue
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
        //checks range and if a spot is already taken
        markBoard(minigameBoard, x-1, y-1, playerLetter);
        cout << endl << "Player's move:" << endl;
        printBoard(minigameBoard, rounds);
        if (WinCheck(minigameBoard, playerLetter, playerWin) == false) {
            EnemyTurn(minigameBoard, enemyLetter);
            printBoard(minigameBoard, rounds);
        }
        //prevents Veris from playing after the player wins
    }
    if (WinCheck(minigameBoard, playerLetter, playerWin) == false) {
        cout << endl << "* Its a draw." << endl;
        return "veris_Win";
    }
    //if nobody wins but we proceed regardless outve loop than it must be a draw
    else if (playerWin == false) {
        cout << endl <<  "* Veris won." << endl;
        return "veris_Win";
    }
    else {
        cout << endl << "* You won." << endl;
        return "player_Win";
    }
    //returns strings to be used as key for Veris' dialogue map

}
