#ifndef PLAYER_H
#define PLAYER_H

#include "House.cpp"
#include <vector>

class Player{
    private:
    vector<House*> road;
    vector<string> inventory = {};
    int votes;
    int roadLocation;
    House currHouse;
    map<int, char> PlayerChar;
    map<string, char> PersonChar;
    public:
    Player();
    void SetCurrentHouse(const House& house);
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

};
#endif
