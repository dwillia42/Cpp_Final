#include "House.h"
#include <iostream>
#include <string>
using namespace std;

House::House(const Person& NPC, string HouseName, string address) 
: NPC(NPC)
{
    this->HouseName = HouseName;
    this->address = address;
}

void House::PrintInfo(){
    cout << "This is " << NPC.GetName() << "\'s" << HouseName << "." << endl;
    cout << "The address of this house is: " << address << endl;
    cout << '\n';
    NPC.PrintDesc();
}