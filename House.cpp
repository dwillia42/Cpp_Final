#include "House.h"
#include "GameData.h"
#include <string>
#include <map>
#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>
using namespace std;

//Default constructor for House
//Use of initalizer list since Person didn't have
//a default constructor before
//https://www.geeksforgeeks.org/cpp/when-do-we-use-initializer-list-in-c/
House::House()
: NPC()
{
    this->HouseName = "Unnamed House";
    this->address = "123 main street";
    this->isVisited = false;
}

//Constructor for House
House::House(Person& NPC, string HouseName, string address) 
{
    this->NPC = &NPC;
    this->HouseName = HouseName;
    this->address = address;
    this->isVisited = false;
}

//Changes the value of wasVisited to true when a player goes to 
// a house
void House::WasVisited(){
    isVisited = true;
}


//Gets whether or not a house was visited by the player
bool House::GetVisitationStatus(){
    return isVisited;
}

//Returns the name of the House Object
string House::GetHouseName(){
    return HouseName;
}

//Returns the person who lives in the house
Person House::GetPerson(){
    return *NPC;
}


//Prints the information about the house, and
//potentially information about who lives there too.
void House::PrintInfo(){
    //Users choice to whether or not they want to see the NPC's description
    int ans;

    //Text that tell's the user what house they're at and the address.
    //Ask the user if they want to see the NPC's description
    cout << "\n* The address of this house is: " << address << endl;
    cout << '\n';
    cout << "* Would you like to view a description of " << NPC->GetName() << "?" << endl << endl;
    cout << "[" << 1 << "]" << " Yes" << endl;
    cout << "[" << 2 << "]" << " No" << endl;
    cout << "\n> ";
    
    cin >> ans;

    //Input validation, same as in the dialogue function in Person.cpp
    while(true){
        if (cin.fail()){
            cout << "\n* Expected an integer input. Please try again." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "\n> ";
            cin >> ans;
        }
        else if(ans != 1 && ans != 2){
            cout << "\nInput must be an from the given choice options:" << endl << endl;
            cout << "[" << 1 << "]" << " Yes" << endl;
            cout << "[" << 2 << "]" << " No" << endl;
            cout << "\n> ";
            cin >> ans;
        }
        else{
            break;
        }
    }

    //If the player's choice was yes ([1]), then the description is printed.
    if (ans == 1){
        cout << "\n";
        NPC->PrintDesc();
        cout << "\n* Press Enter to continue..." << endl;
        cout << "\n> ";
        cin.ignore();
        cin.get();
    }
    
}
