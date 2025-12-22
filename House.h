#ifndef HOUSE_H
#define HOUSE_H

#include <string>
#include <map>
#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>
#include "Person.h"

class GameData;

using namespace std;

class House{
    private:
        Person* NPC;
        string HouseName;
        string address;
        bool isVisited;
    public:
    House();
    House(Person& NPC, string houseName, string adress);
    void PrintInfo();
    string GetHouseName();
    Person GetPerson();
    bool GetVisitationStatus();
    void WasVisited();
    
    
};
#endif