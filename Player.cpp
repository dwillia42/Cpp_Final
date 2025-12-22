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

void Player::SetCurrentHouse(const House& house){
    currHouse = house;
}

House Player::GetCurrentHouse(){
    return currHouse;
}

void Player::AddVote(){
    votes += 1;
}

void Player::ViewVotes(){
    cout << "Current Votes: " << votes << " out of 7." << endl;
}

int Player::GetVotes(){
    return votes;
}

void Player::ViewInventory(){
    cout << "Your inventory: " << endl;
    cout << "-----------------" << endl;
    for (int i = 0; i < inventory.size(); i++){
        cout << "[" << (i + 1) << "] " << inventory.at(i) << endl;
    }
}

int Player::GetSizeOfInventory(){
    return inventory.size();
}

void Player::AddToInventory(string item){
    inventory.push_back(item);
}

void Player::RemoveFromInventory(string item){
    int itemIndex = 0;
    for (size_t i = 0; i < inventory.size(); i++){
        if (inventory.at(i) == item){
            itemIndex = i;
            break;
        }
    }

    inventory.erase(inventory.begin() + itemIndex);
}

string Player::ChooseFromInventory(){
    int itemNum;
    cout << "\n* Enter -1 if you dont want to choose any item." << endl;
    cin >> itemNum;
    if (itemNum != -1){
        return inventory.at(itemNum - 1);
    }
    else{
        return "nothing";
    }
}

vector<string> Player::GetInventory(){
    return inventory;
}

void Player::InitializeMap(){
    const int NUM_ROADBLOCKS = 4;
    for (int i = 0; i < NUM_ROADBLOCKS; i++){
        House* currPtr = nullptr;
        currPtr = new House[2];
        road.push_back(currPtr);
    }
}

void Player::FillSection(const House& houseLeft, const House& houseRight, int sectionNum){
    House* currSection = road.at(sectionNum);
    currSection[0] = houseLeft;
    currSection[1] = houseRight;

}

void Player::FreeMap(){
    for (size_t i = 0; i < road.size(); i++){
        delete[] road.at(i);
        road.at(i) = nullptr;
    }
}

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


void Player::MovePrompt(){
    #if defined(_WIN32)
    SetConsoleOutputCP(CP_UTF8);
    #endif
    char playerMove;
    cout << "\n";
    cout << "* Section: " << roadLocation << "." << endl;
    cout << "---------------------------------" << endl << endl;
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
    cout << "[H] Houses Visited" << endl;
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
            && tolower(playerMove) != 'i' && tolower(playerMove) != 'v' && tolower(playerMove) != 'm' && tolower(playerMove) != 'h'){ 
                cout << "Input must be an from the given choice options:" << endl << endl;
                cout << "   [W]" << endl;
                cout << "[A][S][D]" << endl << endl;
                cout << "[I] Inventory" << endl;
                cout << "[V] Votes" << endl;
                cout << "[M] Map" << endl;
                cout << "[H] Houses Visited" << endl;
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
                    cout << "Going this far is out of town limits." << endl;
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
                    cout << "Going this far is out of town limits." << endl;
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
                ViewVotes();
                break;
            case 'm':
                cout << "\n";
                cout << "---------------------------------" << endl;
                ViewMap();
                cout << "---------------------------------" << endl;
                break;
            case 'h':
                ViewHousesVisited();
                break;
        }

        if (tolower(playerMove) == 'w' || tolower(playerMove) == 's'){
            cout << "You aren't currently at any buidling." << endl;
            cout <<"\n";
            cout << "* Left is " << road.at(roadLocation)[0].GetHouseName() << endl << endl;
            cout << "* Right is " << road.at(roadLocation)[1].GetHouseName() << endl << endl;
            cout << "What would you like to do?" << endl << endl;
            cout << "---------------------------------" << endl << endl;
            cout << "   [W]" << endl;
            cout << "[A][S][D]" << endl << endl;
            cout << "[I] Inventory" << endl;
            cout << "[V] Votes" << endl;
            cout << "[M] Map" << endl;
            cout << "[H] Houses Visited" << endl;
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
            cout << "What would you like to do?" << endl;
            cout << "\n---------------------------------" << endl << endl;
            cout << "   [W]" << endl;
            cout << "[A][S][D]" << endl << endl;
            cout << "[I] Inventory" << endl;
            cout << "[V] Votes" << endl;
            cout << "[M] Map" << endl;
            cout << "[H] Houses Visited" << endl;
            cout << "\n> ";
            cin >> playerMove;
            }
            else if (tolower(playerMove) == 'v'){
                cout << "\n";
                cout << "\nWhat would you like to do?" << endl;
                cout << "\n---------------------------------" << endl << endl;
                cout << "   [W]" << endl;
                cout << "[A][S][D]" << endl << endl;
                cout << "[I] Inventory" << endl;
                cout << "[V] Votes" << endl;
                cout << "[M] Map" << endl;
                cout << "[H] Houses Visited" << endl;
                cout << "\n> ";
                cin >> playerMove;
            }
            else if (tolower(playerMove) == 'm'){
                cout << "\n\nWhat would you like to do?" << endl;
                cout << "\n---------------------------------" << endl << endl;
                cout << "   [W]" << endl;
                cout << "[A][S][D]" << endl << endl;
                cout << "[I] Inventory" << endl;
                cout << "[V] Votes" << endl;
                cout << "[M] Map" << endl;
                cout << "[H] Houses Visited" << endl;
                cout << "\n> ";
                cin >> playerMove;
            }
            else if (tolower(playerMove) == 'h'){
                cout << "\n\nWhat would you like to do?" << endl;
                cout << "\n---------------------------------" << endl << endl;
                cout << "   [W]" << endl;
                cout << "[A][S][D]" << endl << endl;
                cout << "[I] Inventory" << endl;
                cout << "[V] Votes" << endl;
                cout << "[M] Map" << endl;
                cout << "[H] Houses Visited" << endl;
                cout << "\n> ";
                cin >> playerMove;
            }
        }
    }


void Player::ViewHousesVisited(){
    vector<string> housesVisited;
    vector<string> housesNotVisited;
    const int HOUSES_PER_SECTION = 2;
    for (size_t i = 0; i < road.size(); i++){
        House* currSection = road.at(i);
        for (size_t j = 0; j < HOUSES_PER_SECTION; j++){
            bool visitationStatus = currSection[j].GetVisitationStatus();
            string houseName = currSection[j].GetHouseName();
            if (visitationStatus){
                housesVisited.push_back(houseName);
            }
            else{
                housesNotVisited.push_back(houseName); 
            }
        }
    }
    cout << "Places visited:" << endl;
    cout << " -------------------" << endl;
    for (size_t i = 0; i < housesVisited.size(); i++){
       cout << housesVisited.at(i) << endl;
    }

    cout << endl;

    cout << "Places not yet visited:" << endl;
    cout << " -------------------" << endl;
    for (size_t i = 0; i < housesNotVisited.size(); i++){
       cout << housesNotVisited.at(i) << endl;
    }
}

