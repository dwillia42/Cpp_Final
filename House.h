#ifndef HOUSE_H
#define HOUSE_H

#include <string>
#include "Person.cpp"
using namespace std;

class House{
    private:
        Person NPC;
        string HouseName;
        string address;
        bool isVisited;
    public:
    House();
    House(const Person& NPC, string houseName, string adress);
    void PrintInfo();
    string GetHouseName();
    bool GetVisitationStatus();
    void WasVisited();
    
    
};
#endif