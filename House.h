#ifndef HOUSE_H
#define HOUSE_H

#include <string>
#include "Person.h"
using namespace std;

class House{
    private:
        Person NPC;
        string HouseName;
        string address;
    public:
    House(const Person& NPC, string houseName, string adress);
    void PrintInfo();
    
    
};
#endif