#include <string>
#include <map>
#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>
#include <cctype>

#include "Player.h"

using namespace std;

Player::Player(){
    this->votes = 0;
    this->roadLocation = 0;

    PlayerChar.emplace(0, '±');
    PlayerChar.emplace(1, ' ');
    PlayerChar.emplace(2, '│');
    PlayerChar.emplace(3, ' ');

    PersonChar.emplace("Noel Haviday", 'X');
    PersonChar.emplace("Eri Jinnsen",'X');
    PersonChar.emplace("Jorimiah Jo",'X');
    PersonChar.emplace("Clark Woodpecker",'X');
    PersonChar.emplace("Veris Serket",'X');
    PersonChar.emplace("Dr. Adias",'X');
    PersonChar.emplace("Laios Vangrad",'X');
}

void Player::SetCurrentHouse(const House& house){
    currHouse = house;
}

void Player::AddVote(){
    votes += 1;
}

void Player::ViewVotes(){
    cout << "Current Votes: " << votes << endl;
}

void Player::ViewInventory(){
    cout << "Your inventory: " << endl;
    cout << "-----------------" << endl;
    for (int i = 0; i < inventory.size(); i++){
        cout << "[" << (i + 1) << "]" << inventory.at(i) << endl;
    }
}

int Player::GetSizeOfInventory(){
    return inventory.size();
}

void Player::AddToInventory(string item){
    inventory.push_back(item);
}

string Player::ChooseFromInventory(){
    int itemNum;
    cout << "Enter -1 if you dont want to choose any item." << endl;
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
    for (int i = 0; i < road.size(); i++){
        delete[] road.at(i);
        road.at(i) = nullptr;
    }
}

void Player::SetPlayerChar(char move) {
    if (toupper(move) == 'W') {
        PlayerChar.at(roadLocation) = '±';
        if ((roadLocation + 1) % 2 == 0) {
            PlayerChar.at(roadLocation + 1) = '│';
        }
        else {
            PlayerChar.at(roadLocation + 1) = ' ';
        }
    }
    if (toupper(move) == 'S') {
        PlayerChar.at(roadLocation) = '±';
        if ((roadLocation - 1) % 2 == 0) {
            PlayerChar.at(roadLocation - 1) = '│';
        }
        else {
            PlayerChar.at(roadLocation + 1) = ' ';
        }
    }
}

void Player::VoteSecured(string name) {
    PersonChar.at(name) = 'ü';
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
            "└──────┴───┴──────┘\n"
    << endl;
}

void Player::ViewCurrentLocation(){
    currHouse.PrintInfo();
}

void Player::MovePrompt(){
    char move;
    cout << "You are currently in section " << roadLocation << "." << endl;
    cout << "To your left is " << road.at(roadLocation)[0].GetHouseName() << endl;
    cout << "To your right is " << road.at(roadLocation)[1].GetHouseName() << endl;
    cout << "Where would you like to go?" << endl;
    cout << "[W] Up the road" << endl;
    cout << "[A] To the left towards" << road.at(roadLocation)[0].GetHouseName() << endl;
    cout << "[S] Down the road" << endl;
    cout << "[D] To the right towards" << road.at(roadLocation)[1].GetHouseName() << endl;

    while(true){
    cin >> move;

        while(true){
            if (cin.fail()){
                cout << "Expected a character input. Please try again." << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cin >> move;
            }
            else if(tolower(move) != 'w' || tolower(move) != 'a' || tolower(move) != 's' || tolower(move) != 'd'){
                cout << "Input must be an from the given choice options:" << endl;
                cout << "   [W]" << endl;
                cout << "[A][S][D]" << endl;
                cin >> move;
            }
            else{
                break;
            }
        }

        switch (move){
            case 'W':
                roadLocation--;
                cout << "You are now in section " << roadLocation << "." << endl;
                SetPlayerChar(move);
                break;
            case 'S':
                roadLocation++;
                cout << "You are now in section " << roadLocation << "." << endl;
                SetPlayerChar(move);
                break;
            case 'A':
                currHouse = road.at(roadLocation)[0];
                cout << "You are now at " << currHouse.GetHouseName() << endl;
                currHouse.WasVisited();
                break;
            case 'D':
                currHouse = road.at(roadLocation)[1];
                cout << "You are now at " << currHouse.GetHouseName() << endl;
                currHouse.WasVisited();
                break;
        }

        if (tolower(move) == 'w' || tolower(move) == 's'){
            cout << "You aren't currently at any buidling." << endl;
            cout << "Press [W] if you like to move up a section again, and [S] if you would like to move down a section again." << endl; 
            cout << "Press [A] to go to " << road.at(roadLocation)[0].GetHouseName() << ", or [D] to go to " << road.at(roadLocation)[1].GetHouseName() << endl;
        }
        else if (tolower(move) == 'a' || tolower(move) == 'd'){
            break;
        }
    }
}

void Player::ViewHousesVisited(){
    vector<string> housesVisited;
    vector<string> housesNotVisited;
    const int HOUSES_PER_SECTION = 2;
    for (int i = 0; i < road.size(); i++){
        House* currSection = road.at(i);
        for (int j = 0; j < HOUSES_PER_SECTION; i++){
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
    for (int i = 0; i < housesVisited.size(); i++){
       cout << housesVisited.at(i) << endl;
    }

    cout << endl;

    cout << "Places not yet visited:" << endl;
    cout << " -------------------" << endl;
    for (int i = 0; i < housesNotVisited.size(); i++){
       cout << housesNotVisited.at(i) << endl;
    }
}

