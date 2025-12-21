#ifndef TICTACTOE_H
#define TICTACTOE_H

using namespace std;

void printBoard(vector<vector<char>> minigameBoard, int& rounds);
bool WinCheck(vector<vector<char>> minigameBoard, char playerLetter, bool& playerWin);
void EnemyTurn(vector<vector<char>>& minigameBoard, char enemy);
void markBoard(vector<vector<char>>& minigameBoard, int x, int y, char player);
string startTicTacToe();

#endif