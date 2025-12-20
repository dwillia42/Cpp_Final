#include <string>
#include <map>
#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>

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
            
            "* You decide to knock on the Haviday House"
            "\n* Someone looks through the windows and opens the door slightly"
            "\n* \"Hi, I\'m Noel Haviday, my parents said there was a new neighbor coming and to greet them at the door, are you that person?\"",

            {{"Exit", "choice_exit"},{"Offer", "choice_offer"},
            {"Compliment","choice_compliment"},{"Challenge","choice_challenge"}}

        }},

        {"choice_exit", {
            "* You decide to evacuate the premises.",
            {}
        }},
        {"choice_offer", {
            "You look into your inventory to see what you can offer:",
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
        cout << "-----------\n";

        if (currState.choices.empty() && currKey == "choice_offer"){
            
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
        size_t choice_index;
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

}