#include "Person.h"
#include "GameData.h"
#include "TicTacToe.h"

#include <string>
#include <map>
#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>

using namespace std;


Person::Person(){
    this->name = "Unnamed";
    this->age = -1;
    this->gender = "Male";
}

Person::Person(string name, int age, string gender){
    this->name = name;
    this->age = age;
    this->gender = gender;
}

void Person::SetDesc(string description){
    this->description;
}

void Person::PrintDesc(){
    cout << description << endl;
}

void Person::SetName(string name){
   this->name = name;
}

string Person::GetName() const{
   return name;
}
 
string Person::GetGender() const{
   return gender;
}

int Person::GetAge(){
   return age;
}

void Person::SetDialogue(const map<string, DialogueState> dialogueMap){
    this->dialogueMap = dialogueMap;
}

map<string, DialogueState> Person::GetDialogue(){
    return dialogueMap;
}

 /*Idea to use a map from: ZyBooks: 14.4 
 How to use an iterator from ZyBooks: 14.2
 Implementation method had assitance from MathGPT*/
string Person::Dialogue(GameData& game){
   //set the current key to the start key
    string currKey = "start";

    while(true){

    //declares the iterator (like a pointer almost) 
    map<string, DialogueState>::const_iterator iter;
    //sets the iterator to the location of the start key
    iter = dialogueMap.find(currKey);

    /*Checks to see if the iterator points to the end of the map
    if it does, then the argument key is invalid, and the function 
    terminates.
    */

        if (iter == dialogueMap.end()){
            cout << "\n* The key you entered is invalid." << endl;
            break;
        }

        /*If the loop doesn't break, then get the current state
        of dialogue from getting the second item in the corresponding
        pair of the map
        */
        
        const DialogueState& currState = iter->second;

        /*formats and prints out the text at the current stage of dialogue*/
        cout << "\n-----------\n";
        cout << currState.text << "\n";
        cout << "\n-----------\n";

        /*if the player chooses to offer, then a list of things in the inventory
        will be shown, and the player will choose an item. If the inventory is empty,
        then the appropiate message is shown. */

        if (currKey == "choice_offer"){
            //if the player has no items:
            if(game.player.GetInventory().size() == 0){
                cout << "* But you have nothing to offer..." << endl;
                currKey = "null_offer";
                continue;
            }
            else{
                game.player.ViewInventory();
                string chooseObj = game.player.ChooseFromInventory();
                if (chooseObj == "nothing"){
                    currKey = "null_offer";
                    continue;
                }
                string objectKey = chooseObj + "_choice";
                currKey = objectKey;
                continue;
            }
        }

        if (currKey == "startMinigame"){
            //hmmm i will work on this seperately for a bit
        }
        
        /*If there are no other choices, then the dialogue is over, and the loop 
        breaks
        */

        if (currState.choices.empty()){
            cout << "--- Dialogue Ended ---" << endl;\
            break;
        }

        /*Give the user available choice options*/

        for (size_t i = 0; i < currState.choices.size(); i++){
            cout << "[" << (i + 1) << "] " << currState.choices.at(i).choice << endl;    
        }

        //initializes and reads user input
        size_t choice_index = -1;
        cout << "\n> ";
        cin >> choice_index;

        /*Revised Input Validation (wrong data type validation from:GeeksForGeeks)
        https://www.geeksforgeeks.org/cpp/how-to-handle-wrong-data-type-input-in-cpp/
        */
        while(true){
            if (cin.fail() || (choice_index < 1 || choice_index > currState.choices.size())){
                if (cin.fail()){
                    cout << "\n* Expected an integer input. Please try again." << endl;
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "\n> ";
                    cin >> choice_index;
                }
                else if (choice_index < 1 || choice_index > currState.choices.size()){
                    cout << "\n* Input must be an from the given choice options:" << endl;
                    for (size_t i = 0; i < currState.choices.size(); i++){
                        cout << "[" << (i + 1) << "] " << currState.choices.at(i).choice << endl;    
                    }
                    cout << "\n> ";
                    cin >> choice_index;
                }
            }
            else{
                break;
            }
        }

        currKey = currState.choices.at(choice_index - 1).nextState;
    }

    //Returns key so we can add/subtract points based on the final state of dialogue
    return currKey;
}


 
