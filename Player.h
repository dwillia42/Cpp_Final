#ifndef PLAYER_H
#define PLAYER_H

#include "House.h"
#include <string>
#include <map>
#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>

class GameData;

using namespace std;
class Player{
    private:
    vector<House*> road;
    vector<string> inventory = {};
    int votes;
    int roadLocation;
    House currHouse;
    vector<string> PlayerChar;
    map<string, string> PersonChar;
    public:
    Player();
    void SetCurrentHouse(const House& house);
    House GetCurrentHouse();
    void AddVote();
    void InitializeMap();
    void FillSection(const House& houseLeft, const House& houseRight, int sectionNum);
    void FreeMap();
    void ViewCurrentLocation();
    void ViewVotes();
    void ViewMap();
    void ViewInventory();
    void AddToInventory(string item);
    vector<string> GetInventory();
    int GetSizeOfInventory();
    string ChooseFromInventory();
    void MovePrompt();
    void ViewHousesVisited();
    void SetPlayerChar(char move);
    void VoteSecured(string name);
    int GetVotes();

};
#endif
