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
    string GetCurrentLocation();
    void ViewVotes();
    void ViewMap();
    void ViewInventory();
    void MovePrompt();
    void ViewHousesVisited();

               

};
#endif
