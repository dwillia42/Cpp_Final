#include <string>
#include <map>
#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>

using namespace std;

#include "Person.h"

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

 /*Idea to use a map from: ZyBooks: 14.4 
 How to use an iterator from ZyBooks: 14.2
 Implementation method had assitance from MathGPT*/
string Person::Dialogue(){
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
            cout << "The key you entered is invalid." << endl;
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
        
        /*If there are no other choices, then the dialogue is over, and the loop 
        breaks
        */

        if (currState.choices.empty()){
            cout << "--- Dialogue Ended ---" << endl;\
            break;
        }

        /*Give the user available choice options*/

        for (size_t i = 0; i < currState.choices.size(); i++){
            cout << "Choice " << (i + 1) << ": " << currState.choices.at(i).choice << endl;    
        }

        //initializes and reads user input
        size_t choice_index = -1;
        cin >> choice_index;

        /*Revised Input Validation (wrong data type validation from:GeeksForGeeks)
        https://www.geeksforgeeks.org/cpp/how-to-handle-wrong-data-type-input-in-cpp/
        */
        while(true){
            if (cin.fail() || (choice_index < 1 || choice_index > currState.choices.size())){
                if (cin.fail()){
                    cout << "Expected an integer input. Please try again." << endl;
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cin >> choice_index;
                }
                else if (choice_index < 1 || choice_index > currState.choices.size()){
                    cout << "Input must be an from the given choice options:" << endl;
                    for (size_t i = 0; i < currState.choices.size(); i++){
                        cout << "[" << (i + 1) << "] " << currState.choices.at(i).choice << endl;    
                    }
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


 /*THIS IS WHERE YOU CREATE THE DIALOGUE FOR
    THE NPC. In the map, each element is an ordered
    pair of a key and a dialogue corresponding to the key.
    The dialogue is paired with a vector in a struct with the possible
    user choices.*/

    /*For instance, the program starts with the key "start". The NPC dialogue asking
    whether the user wants to go into the forest or town. The user will enter there choice, and the
    second part of the Dialogue Option struct, either "choice_Forest" or "choice_Town" will
    cause the dialogue to go either way. To end the dialogue, make an empty vector({}) after the
    NPC dialogue.*/

    /*map<string, DialogueState> dialogueMap = {
        {"start", {
            
            "Would you like to go into the forest or town?",

            {{"Forest", "choice_Forest"},{"Town", "choice_Town"}}

        }},

        {"choice_Forest", {
            "You have went into the forest, got eaten, and died.",
            {}
        }},
        {"choice_Town", {
            "You have went into town. You got shot by Demarcus, and died.",
            {}
        }},

       /* {"EXAMPLE KEY", {
            "AN EXAMPLE SENTENCE FROM THE NPC WHERE YOU HAVE TO MAKE A CHOICE",

            {{"EXAMPLE CHOICE RESPONSE 1", "CORRESPONDING KEY FOR CHOICE 1"},
             {"EXAMPLE CHOICE RESPONSE 2", "CORRESPONDING KEY FOR CHOICE 2"}}
        }},*/
    
