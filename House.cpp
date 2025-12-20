#include "House.h"
#include <iostream>
#include <string>
using namespace std;

House::House()
: NPC()
{
    this->HouseName = "Unnamed House";
    this->address = "123 main street";
    this->isVisited = false;
}

House::House(const Person& NPC, string HouseName, string address) 
: NPC(NPC)
{
    this->HouseName = HouseName;
    this->address = address;
    this->isVisited = false;
}

void House::WasVisited(){
    isVisited = true;
}

bool House::GetVisitationStatus(){
    return isVisited;
}

string House::GetHouseName(){
    return HouseName;
}

void House::PrintInfo(){
    //Users choice to whether or not they want to see the NPC's description
    int ans;

    //Text that tell's the user what house they're at and the address.
    //Ask the user if they want to see the NPC's description
    cout << "This is " << HouseName << "." << endl;
    cout << "The address of this house is: " << address << endl;
    cout << '\n';
    cout << "Would you like to view a description of " << NPC.GetName() << "?" << endl;
    cout << "[" << 1 << "]" << " Yes" << endl;
    cout << "[" << 2 << "]" << " No" << endl;
    
    cin >> ans;

    //Input validation, same as in the dialogue function in Person.cpp
    while(true){
        if (cin.fail()){
            cout << "Expected an integer input. Please try again." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin >> ans;
        }
        else if(ans != 1 || ans != 2){
            cout << "Input must be an from the given choice options:" << endl;
            cout << "[" << 1 << "]" << " Yes" << endl;
            cout << "[" << 2 << "]" << " No" << endl;
            cin >> ans;
        }
        else{
            break;
        }
    }

    //If the player's choice was yes ([1]), then the description is printed.
    if (ans == 1){
        NPC.PrintDesc();
    }
    
}