#ifndef MAP_H
#define MAP_H

#include "House.h"
#include <vector>

class Player{
    private:
    vector<House*> road;
    vector<string> inventory;
    int votes;
    int roadLocation;
    House currHouse;
    public:
    void AddVote();
    void InitializeMap();
    void FillSection(const House& houseLeft, const House& houseRight, int sectionNum);
    void FreeMap();
    void ViewCurrentLocation();
    void ViewVotes();
    void ViewMap();
    void ViewInventory();
    string ChooseFromInventory();
    void MovePrompt();
    void ViewHousesVisited();

               

};
#endif
