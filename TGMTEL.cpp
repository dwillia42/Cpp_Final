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

    //creates a vector called people and sets it to people
    vector<Person> people = game.GetPeople();

    //defines prevIndex as the index of the key vector that contains the 
    //key before the final key when the dialogue ends. Sometimes the second to last
    //or last keys need to be tested to secure a vote.
    int prevIndex = 0;
    int lastIndex = 1;
    
    //used as a condition for something to not happen twice
    bool alreadyWon = false;
    
    //Runs Old Terry's first dialogue.
    people.at(0).Dialogue(game);
    
    //Makes the player move, view inventory, etc.
    game.player.MovePrompt();

    //Initliazes a house object that keeps track of the current (latest) house.
    House currentHouse;


    //This loop makes it so that the player is forced to go visit The Haviday House first
    while(true){
        //Sets currentHouse to the current (latest) House
        currentHouse = game.player.GetCurrentHouse();

        //Checks if the current house the player is at isn't THe Haviday House and if The Haviday House wasn't visited
        //breaks the loop otherwise
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
    
    //Prints the info about the house. Within is the option to print a
    //brief description of the person.
    currentHouse.PrintInfo();

    //Runs the dialogue of Noel Haviday
    vector<string> lastKey = people.at(1).Dialogue(game);

    //If the last key before the dialogue ends is "choice_leave",
    //Then the player gets a vote, and there vote is secured,
    if (lastKey.at(lastIndex) == "choice_leave"){
        game.player.VoteSecured("Noel Haviday");
        game.player.AddVote();
        people.at(1).HasVoted();
    }

    //After visiting The Haviday House, the user has freedom to travel where ever
    //they want, but the game doesnt end until all 7 votes are secured.
    //For every house, there info is printed with the option to see a brief description of
    //The person living there.
    while(true){
        game.player.MovePrompt();
        currentHouse = game.player.GetCurrentHouse();
        currentHouse.PrintInfo();
        if (currentHouse.GetHouseName() == "The Adias House"){
            //input validation if the player already secured the vote.
            if (people.at(2).VoteStatus()){
                cout << "\n* You have already secured " << currentHouse.GetPerson().GetName() << "\'s vote.";
            }
            else{
                //runs the dialogue, and determines what changes bases on
                //last/second to last state as needd.
                lastKey = people.at(2).Dialogue(game);
                if(lastKey.at(prevIndex) == "choice_compliment"){
                    game.player.VoteSecured("Eri Jinnsen");
                    game.player.AddVote();
                    people.at(2).HasVoted();
                }
            }
        }
        else if (currentHouse.GetHouseName() == "The Jo House"){
            //input validation if the player already secured the vote.
            if(people.at(3).VoteStatus()){
                cout << "\n* You have already secured " << currentHouse.GetPerson().GetName() << "\'s vote." << endl;
                cout << "\n";
            }
            else{
                //runs the dialogue, and determines what changes bases on
                //last/second to last state as needd.
                lastKey = people.at(3).Dialogue(game);
                if(lastKey.at(prevIndex) == "choice_chase"){
                    game.player.VoteSecured("Jorimiah Jo");
                    game.player.AddVote();
                    people.at(3).HasVoted();
                    game.player.RemoveFromInventory("Quiz Paper");
                }
            }
        }
        else if (currentHouse.GetHouseName() == "The Library"){
            //input validation if the player already secured the vote.
            if(people.at(4).VoteStatus()){
                cout << "\n* You have already secured " << currentHouse.GetPerson().GetName() << "\'s vote." << endl;
                cout << "\n";
            }
            else{
                //runs the dialogue, and determines what changes bases on
                //last/second to last state as needd.
                lastKey = people.at(4).Dialogue(game);
                if(lastKey.at(prevIndex) == "choice_finished"){
                    game.player.VoteSecured("Clark Woodpecker");
                    game.player.AddVote();
                    game.player.AddToInventory("Quiz Paper");
                    people.at(4).HasVoted();
                }
            }
        }
        else if (currentHouse.GetHouseName() == "The Serket House"){
            //input validation if the player already secured the vote.
            if(people.at(5).VoteStatus()){
                cout << "\n* You have already secured " << currentHouse.GetPerson().GetName() << "\'s vote." << endl;
                cout << "\n";
            }
            //uses the key returned by the minigame
            else{
                //runs the dialogue, and determines what changes bases on
                //last/second to last state as needed.
               lastKey = people.at(5).Dialogue(game);
                if(lastKey.at(prevIndex) == "veris_Win" || lastKey.at(prevIndex) == "player_Win") {
                    game.player.VoteSecured("Veris Serket");
                    game.player.AddVote();
                    people.at(5).HasVoted();
                } 
            }  
        }
        else if (currentHouse.GetHouseName() == "The Clinic"){
            //input validation if the player already secured the vote.
            if (people.at(6).VoteStatus()){
                cout << "\n* You have already secured " << currentHouse.GetPerson().GetName() << "\'s vote." << endl;
                cout << "\n";
            }
            else{
                //runs the dialogue, and determines what changes bases on
                //last/second to last state as needed.
                lastKey = people.at(6).Dialogue(game);
                if (lastKey.at(lastIndex) == "choice_leave"){
                    game.player.VoteSecured("Dr. Adias");
                    game.player.AddVote();
                    game.player.AddToInventory("Health Curriculum");
                    people.at(6).HasVoted();
                }
            }  
        }
        else if (currentHouse.GetHouseName() == "The School"){
            //input validation if the player already secured the vote.
            if(people.at(7).VoteStatus()){
                cout << "\n* You have already secured " << currentHouse.GetPerson().GetName() << "\'s vote.";
                cout << "\n";
            }
            else{
                //runs the dialogue, and determines what changes bases on
                //last/second to last state as needed.
                lastKey = people.at(7).Dialogue(game);
                if (lastKey.at(prevIndex) == "Health Curriculum_choice"){
                    game.player.VoteSecured("Laios Vangrad");
                    game.player.AddVote();
                    people.at(7).HasVoted();
                    game.player.RemoveFromInventory("Health Curriculum");
                }
            }
        }
        //input validation if the player already secured the vote.
        else if (currentHouse.GetHouseName() == "The Haviday House"){
            cout << "\n* You have already secured " << currentHouse.GetPerson().GetName() << "\'s vote.";
            cout << "\n";
        }
        else if (currentHouse.GetHouseName() == "Town Hall"){
            //Accesses Old Terry's new dialogue if the player
            //got all 7 votes
            if (game.player.GetVotes() == 7){
                game.GetPeople().at(0).Dialogue(game);
                break;
            }
            //if the player tries to go to town hall before
            //obtaining all 7 votes
            else{
                cout << "* You try to go to Town Hall, but"
                        "\ndon\'t have enough votes..." << endl;
            }
        }
        //condition that is checked after every house visit.
        if(game.player.GetVotes() == 7 && alreadyWon == false){
            alreadyWon = true;
            cout << "* Congratulations! You now have everyones vote." << endl;
            cout << "\n* Go Back to Town Hall to talk to Old Terry." << endl;
            
            //Sets Old Terry's new dialogue
            game.SetEndingDialogue();
        }
    }
}

int main(){
    //Creates a game object, initializes everything, and then runs the game
    GameData game;
    game.CreateMap();
    game.InitializeDialogue();
    game.InitializeCharacterDescriptions();
    StartGame(game);

    //When the game is over, free's the dynamically allocated memory.
    game.player.FreeMap();

    //lets the user press enter to exit the game.
    //Taken from MATHGPT
    cout << "\n* Press Enter to exit..." << endl;
    cin.ignore();
    cin.get();
    return 0;
}

