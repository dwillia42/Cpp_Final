#include <string>
#include <map>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct DialogueOption{
        string choice;
        string nextState;
    };

struct DialogueState{
        string text;
        vector<DialogueOption> choices;
    };




void run_dialogue(const string& startKey, const map<string, DialogueState>& dialogueMap);

int main(){

    map<string, DialogueState> dialogueMap = {
        {"start", {
            
            "Would you like to go into the forest or town?",

            {{"Yes", "choice_Yes"},{"No", "choice_No"}}

        }},

        {"choice_Yes", {
            "You have went into the forest, got eaten, and died.",
            {}
        }},
        {"choice_No", {
            "You have went into town. You got shot by Demarcus, and died.",
            {}
        }}
    };

    run_dialogue("start", dialogueMap);
    
    return 0;
}

void run_dialogue(const string& startKey, const map<string, DialogueState>& dialogueMap){
    //set the current key to the start key
    string currKey = startKey;

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


        //Input validation for choice index
        while (choice_index < 1 || choice_index > currState.choices.size()){
            cout << "Invalid choice. Please enter another choice." << endl;
            cin >> choice_index;
        }

        currKey = currState.choices.at(choice_index - 1).nextState;
    }

}