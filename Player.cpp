#if defined(__CYGWIN__) || defined(_WIN32)
#define  NOMINMAX
#define  _HAS_STD_BYTE 0
#include <windows.h>
#endif
// https://stackoverflow.com/questions/41591846/ifdef-win32-not-getting-detected
#include <string>
#include <map>
#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>
#include <cctype>
#include "Player.h"
#include "GameData.h"

using namespace std;

//Default Constructor for Player.
//Sets each characters respective status to X
//at the beginning of the game to change over time.
Player::Player(){
    this->votes = 0;
    this->roadLocation = 0;

    PlayerChar = {"±", " ", "│", " "};

    PersonChar.emplace("Noel Haviday", "X");
    PersonChar.emplace("Eri Jinnsen","X");
    PersonChar.emplace("Jorimiah Jo","X");
    PersonChar.emplace("Clark Woodpecker","X");
    PersonChar.emplace("Veris Serket","X");
    PersonChar.emplace("Dr. Adias","X");
    PersonChar.emplace("Laios Vangrad","X");
}


//Sets the current House (latest house that was visited by player)
void Player::SetCurrentHouse(const House& house){
    currHouse = house;
}

//returns the current House (latest house that was visited by player)
House Player::GetCurrentHouse(){
    return currHouse;
}

//When a vote from a person is secured,
//the vote count increases by +1
void Player::AddVote(){
    votes += 1;
}

//The players option the view how many votes they have out of 7
//while not at a house (on the road).
void Player::ViewVotes(){
    cout << "* Current Votes: " << votes << " out of 7.";
}

//Returns the amount of votes recieved so far
int Player::GetVotes(){
    return votes;
}


//The players option to view their inventory while not
//at a house (on the road).
void Player::ViewInventory(){
    cout << "---------------------------------" << endl << endl;
    cout << "* Your Inventory: \n" << endl;
    for (int i = 0; i < inventory.size(); i++){
        cout << "[" << (i + 1) << "] " << inventory.at(i) << endl;
    }
}

//Returns the size of the inventory
int Player::GetSizeOfInventory(){
    return inventory.size();
}

//When someone in the game gives the player an item,
//that item is added to their inventory.
void Player::AddToInventory(string item){
    inventory.push_back(item);
}

//Removes the item from the player's inventory.
void Player::RemoveFromInventory(string item){
    int itemIndex = 0;

    //Finds the index the item is at
    for (size_t i = 0; i < inventory.size(); i++){
        if (inventory.at(i) == item){
            itemIndex = i;
            break;
        }
    }

    //deletes the item at that index (popped method into google)
    inventory.erase(inventory.begin() + itemIndex);
}


//Let's the player choose from the inventory when they Offer.
string Player::ChooseFromInventory(){
    int itemNum;
    
    //if the player enters negative one (or if their inventory is empty),
    //they don't offer anything. Otherwise, the item they offer is returned.
    cout << "\n* Enter -1 if you dont want to choose any item." << endl;
    cout << "\n> ";
    cin >> itemNum;
    if (itemNum != -1){
        return inventory.at(itemNum - 1);
    }
    else{
        return "nothing";
    }
}

//Returns the player's inventory
vector<string> Player::GetInventory(){
    return inventory;
}

//Creates the map, but doesn't add everything
void Player::InitializeMap(){

    //number of pointers to arrays of size 2
    const int NUM_ROADBLOCKS = 4;

    //creates each pointer to an array of houses,
    //and adds them to road.
    for (int i = 0; i < NUM_ROADBLOCKS; i++){
        House* currPtr = nullptr;
        currPtr = new House[2];
        road.push_back(currPtr);
    }
}

//Fills a element of road with 2 houses
//Ex: passing Town Hall and The Haviday houses, and 0 gives
//the first pointer in road pointing to [Town Hall, The Haviday House]
void Player::FillSection(const House& houseLeft, const House& houseRight, int sectionNum){
    House* currSection = road.at(sectionNum);
    currSection[0] = houseLeft;
    currSection[1] = houseRight;

}

//After the game finishes, free's the memory on the heap
void Player::FreeMap(){
    for (size_t i = 0; i < road.size(); i++){
        delete[] road.at(i);
        road.at(i) = nullptr;
    }
}

//replaces the road section you’re going to with your player symbol, 
//and replaces the one before or after (based on movement key given) with empty space if it's odd, or a “|" if it's even so it looks like a road
void Player::SetPlayerChar(char playerMove) {
    if (toupper(playerMove) == 'W') {
        PlayerChar.at(roadLocation) = "±";
        if ((roadLocation + 1) % 2 == 0) {
            PlayerChar.at(roadLocation + 1) = "│";
        }
        else {
            PlayerChar.at(roadLocation + 1) = " ";
        }
    }
    if (toupper(playerMove) == 'S') {
        PlayerChar.at(roadLocation) = "±";
        if ((roadLocation - 1) % 2 == 0) {
            PlayerChar.at(roadLocation - 1) = "│";
        }
        else {
            PlayerChar.at(roadLocation - 1) = " ";
        }
    }
}

void Player::VoteSecured(string name) {
    PersonChar.at(name) = "@";
    
}

//Shows the map 
//splitted the map at the parts with variable chars with npc & symbols(both changed to string because chars weren't big enough for some symbols) 
void Player::ViewMap(){
    cout << "┌──────┬───┬──────┐\n"
            "│/¯¯¯\\ ║   ║ /¯¯¯\\│\n"
            "││ T │═╣ " << PlayerChar.at(0) << " ╠═│ " << PersonChar.at("Noel Haviday") << " ││\n"
            "│└───┘ ║   ║ └───┘│\n"
            "│/¯¯¯\\ ║ │ ║ /¯¯¯\\│\n"
            "││ " << PersonChar.at("Eri Jinnsen") << " │═╣ " << PlayerChar.at(1) << " ╠═│ " << PersonChar.at("Jorimiah Jo") << " ││\n"
            "│└───┘ ║ │ ║ └───┘│\n"
            "│/¯¯¯\\ ║   ║ /¯¯¯\\│\n"
            "││ " << PersonChar.at("Clark Woodpecker") << " │═╣ " << PlayerChar.at(2) << " ╠═│ " << PersonChar.at("Veris Serket") << " ││\n"
            "│└───┘ ║   ║ └───┘│\n"
            "│/¯¯¯\\ ║ │ ║ /¯¯¯\\│\n"
            "││ " << PersonChar.at("Dr. Adias") << " │═╣ " << PlayerChar.at(3) << " ╠═│ " << PersonChar.at("Laios Vangrad") << " ││\n"
            "│└───┘ ║ │ ║ └───┘│\n"
            "└──────┴───┴──────┘\n";
    
}


//give player the ability to move across the map and
//view there inventory, votes, and map.
void Player::MovePrompt(){
    //See above for where this comes from
    #if defined(_WIN32)
    SetConsoleOutputCP(CP_UTF8);
    #endif
    char playerMove;
    cout << "\n";
    cout << "---------------------------------" << endl;
    cout << "* Section: " << roadLocation << "." << endl;
    ViewMap();
    cout << "---------------------------------" << endl << endl;
    cout << "* Left is " << road.at(roadLocation)[0].GetHouseName() << endl << endl;
    cout << "* Right is " << road.at(roadLocation)[1].GetHouseName() << endl << endl;
    cout << "* Up and Down to walk on the road." << endl << endl;
    cout << "* What would you like to do?" << endl << endl;
    cout << "---------------------------------" << endl << endl;
    cout << "   [W]" << endl;
    cout << "[A][S][D]" << endl << endl;
    cout << "[I] Inventory" << endl;
    cout << "[V] Votes" << endl;
    cout << "[M] Map" << endl;
    cout << "\n> ";

    cin >> playerMove;
    while(true){
        while(true){
            if (cin.fail()){
                cout << "Expected a character input. Please try again." << endl;
                cin.clear();
                cin.ignore((numeric_limits<streamsize>::max)(), '\n');
                cin >> playerMove;
            }
            else if(tolower(playerMove) != 'w' && tolower(playerMove) != 'a' && tolower(playerMove) != 's' && tolower(playerMove) != 'd' 
            && tolower(playerMove) != 'i' && tolower(playerMove) != 'v' && tolower(playerMove) != 'm'){ 
                cout << "Input must be an from the given choice options:" << endl << endl;
                cout << "   [W]" << endl;
                cout << "[A][S][D]" << endl << endl;
                cout << "[I] Inventory" << endl;
                cout << "[V] Votes" << endl;
                cout << "[M] Map" << endl;
                cout << "\n> ";
                cin >> playerMove;
            }
            else{
                break;
            }
        }

        switch (tolower(playerMove)){
            case 'w':
                if (roadLocation == 0){
                    cout << "\n* Going this far is out of town limits." << endl;
                    break;
                }
                else{
                    roadLocation--;
                    cout << "\n";
                    cout << "* You are now in section " << roadLocation << "." << endl;
                    SetPlayerChar(playerMove);
                    break;
                }
                
            case 's':
                if(roadLocation == 3){
                    cout << "\n* Going this far is out of town limits." << endl;
                    break;
                }
                else{
                    roadLocation++;
                    cout << "\n";
                    cout << "* You are now in section " << roadLocation << "." << endl;
                    SetPlayerChar(playerMove);
                    break;
                }
            case 'a':
                currHouse = road.at(roadLocation)[0];
                cout << "\n";
                cout << "* You are now at " << currHouse.GetHouseName() << endl;
                currHouse.WasVisited();
                break;
            case 'd':
                currHouse = road.at(roadLocation)[1];
                cout << "\n";
                cout << "* You are now at " << currHouse.GetHouseName() << endl;
                currHouse.WasVisited();
                break;
            case 'i':
                cout << "\n";
                ViewInventory();
                break;
            case 'v':
                cout << "\n";
                cout << "---------------------------------\n" << endl;
                ViewVotes();
                break;
            case 'm':
                cout << "\n";
                cout << "---------------------------------" << endl;
                ViewMap();
                cout << "---------------------------------";
                break;
        }

        if (tolower(playerMove) == 'w' || tolower(playerMove) == 's'){
            cout << endl << "* You aren't currently at any buidling." << endl;
            cout <<"\n";
            cout << "* Left is " << road.at(roadLocation)[0].GetHouseName() << endl << endl;
            cout << "* Right is " << road.at(roadLocation)[1].GetHouseName() << endl << endl;
            cout << "* What would you like to do?" << endl << endl;
            cout << "---------------------------------" << endl << endl;
            cout << "   [W]" << endl;
            cout << "[A][S][D]" << endl << endl;
            cout << "[I] Inventory" << endl;
            cout << "[V] Votes" << endl;
            cout << "[M] Map" << endl;
            cout << "\n> ";
            cin >> playerMove;
        }
        else if (tolower(playerMove) == 'a' || tolower(playerMove) == 'd'){
            break;
        }
        else if (tolower(playerMove) == 'i'){
            if (GetSizeOfInventory() == 0){
                cout << "* Your inventory is empty." << endl;
            }
            cout <<"\n";
            cout << "* What would you like to do?" << endl;
            cout << "\n---------------------------------" << endl << endl;
            cout << "   [W]" << endl;
            cout << "[A][S][D]" << endl << endl;
            cout << "[I] Inventory" << endl;
            cout << "[V] Votes" << endl;
            cout << "[M] Map" << endl;
            cout << "\n> ";
            cin >> playerMove;
            }
            else if (tolower(playerMove) == 'v'){
                cout << "\n";
                cout << "\n* What would you like to do?" << endl;
                cout << "\n---------------------------------" << endl << endl;
                cout << "   [W]" << endl;
                cout << "[A][S][D]" << endl << endl;
                cout << "[I] Inventory" << endl;
                cout << "[V] Votes" << endl;
                cout << "[M] Map" << endl;
                cout << "\n> ";
                cin >> playerMove;
            }
            else if (tolower(playerMove) == 'm'){
                cout << "\n\n* What would you like to do?" << endl;
                cout << "\n---------------------------------" << endl << endl;
                cout << "   [W]" << endl;
                cout << "[A][S][D]" << endl << endl;
                cout << "[I] Inventory" << endl;
                cout << "[V] Votes" << endl;
                cout << "[M] Map" << endl;
                cout << "\n> ";
                cin >> playerMove;
            }
        }
    }



