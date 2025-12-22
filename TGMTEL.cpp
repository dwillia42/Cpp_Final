#include <string>
#include <map>
#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>
#include <cctype>
#include "GameData.h"
#include "TicTacToe.h"

using namespace std;

void StartGame(GameData& game){
    vector<Person> people = game.GetPeople();
    int prevIndex = 0;
    int lastIndex = 1;
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
    vector<string> lastKey = people.at(1).Dialogue(game);

    if (lastKey.at(lastIndex) == "choice_leave"){
        game.player.VoteSecured("Noel Haviday");
        game.player.AddVote();
    }

    while(true){
        game.player.MovePrompt();
        currentHouse = game.player.GetCurrentHouse();
        currentHouse.PrintInfo();
        if (currentHouse.GetHouseName() == "The Adias House"){
            if (people.at(2).VoteStatus()){
                cout << "* You have already secured " << currentHouse.GetPerson().GetName() << "\'s vote.";
            }
            else{
                lastKey = people.at(2).Dialogue(game);
                if(lastKey.at(prevIndex) == "choice_compliment"){
                    game.player.VoteSecured("Eri Jinnsen");
                    game.player.AddVote();
                    currentHouse.GetPerson().HasVoted();
                }
            }
        }
        else if (currentHouse.GetHouseName() == "The Jo House"){
            if(people.at(3).VoteStatus()){
                cout << "You have already secured " << currentHouse.GetPerson().GetName() << "\'s vote.";
            }
            else{
                lastKey = people.at(3).Dialogue(game);
                if(lastKey.at(prevIndex) == "choice_chase"){
                    game.player.VoteSecured("Jorimiah Jo");
                    game.player.AddVote();
                    currentHouse.GetPerson().HasVoted();
                }
            }
        }
        else if (currentHouse.GetHouseName() == "The Library"){
            if(people.at(4).VoteStatus()){
                cout << "You have already secured " << currentHouse.GetPerson().GetName() << "\'s vote.";
            }
            else{
                lastKey = people.at(4).Dialogue(game);
                if(lastKey.at(prevIndex) == "choice_finished"){
                    game.player.VoteSecured("Clark Woodpecker");
                    game.player.AddVote();
                    game.player.AddToInventory("Quiz Paper");
                    currentHouse.GetPerson().HasVoted();
                }
            }
        }
        else if (currentHouse.GetHouseName() == "The Serket House"){
            if(people.at(5).VoteStatus()){
                cout << "You have already secured " << currentHouse.GetPerson().GetName() << "\'s vote.";
            }
            else{
               lastKey = people.at(5).Dialogue(game);
                if(lastKey.at(prevIndex) == "veris_Win" || lastKey.at(prevIndex) == "player_Win") {
                    game.player.VoteSecured("Veris Serket");
                    game.player.AddVote();
                    currentHouse.GetPerson().HasVoted();
                } 
            }  
        }
        else if (currentHouse.GetHouseName() == "The Clinic"){
            if (people.at(6).VoteStatus()){
                cout << "You have already secured " << currentHouse.GetPerson().GetName() << "\'s vote.";
            }
            else{
                lastKey = people.at(6).Dialogue(game);
                if (lastKey.at(lastIndex) == "choice_leave"){
                    game.player.VoteSecured("Dr. Adias");
                    game.player.AddVote();
                    game.player.AddToInventory("Health Curriculum");
                    currentHouse.GetPerson().HasVoted();
                }
            }  
        }
        else if (currentHouse.GetHouseName() == "The School"){
            if(people.at(7).VoteStatus()){
                cout << "You have already secured " << currentHouse.GetPerson().GetName() << "\'s vote.";
            }
            else{
                lastKey = people.at(7).Dialogue(game);
                if (lastKey.at(prevIndex) == "Health Curriculum_choice"){
                    game.player.VoteSecured("Laios Vangrad");
                    game.player.AddVote();
                    currentHouse.GetPerson().HasVoted();
                }
            }
        }
        
        if(game.player.GetVotes() == 7){
            cout << "Congratulations! You now have everyones vote." << endl;
            cout << "\nGo Back to Town Hall to talk to Old Terry." << endl;
            break;
        }
    }
}

int main(){
    GameData game;
    game.CreateMap();
    game.InitializeDialogue();
    game.InitializeCharacterDescriptions();
    StartGame(game);

    cout << "\n* Press Enter to exit..." << endl;
    cin.ignore();
    cin.get();
    return 0;
}

