#include <string>
#include <map>
#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>
#include <cctype>
#include "GameData.h"

using namespace std;

void StartGame(GameData& game){
    vector<Person> people = game.GetPeople();
    people.at(0).Dialogue(game);
    
    game.player.MovePrompt();

    House currentHouse;

    while(true){
        currentHouse = game.player.GetCurrentHouse();
        if (currentHouse.GetHouseName() != "The Haviday House" && !game.GetHouse(1).GetVisitationStatus()){
            cout << "\n* Old Terry suggested you talk to his daughter first to the right of Town Hall."
                    "\n"
                    "\n* You guess you could go to this place after..."
                    "\n"
                    "\n* You have left " << currentHouse.GetHouseName() << "."
                << endl;
            game.player.MovePrompt();
        }
        else{
            break;
        }
    }
    currentHouse.PrintInfo();
    string lastKey = people.at(1).Dialogue(game);

    if (lastKey == "choice_leave"){
        game.player.VoteSecured("Noel Haviday");
        game.player.AddVote();
    }

    while(true){
        game.player.MovePrompt();
        currentHouse = game.player.GetCurrentHouse();
        lastKey = currentHouse.GetPerson().Dialogue(game);
    }
}

int main(){
    GameData game;
    game.CreateMap();
    game.InitializeDialogue();
    StartGame(game);

    cout << "Press Enter to exit..." << endl;
    cin.ignore();
    cin.get();
    return 0;
}

