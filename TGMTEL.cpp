#include "Player.h"
#include <string>
#include <map>
#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>
#include <cctype>

using namespace std;

/*The creation of the dialogue maps*/
struct DialogueOption{
        string choice;
        string nextState;
    };

struct DialogueState{
        string text;
        vector<DialogueOption> choices;
    };

map<string, DialogueState> mayorDialogue1 = {
    {start, {
        "* Your name is Player and you have a DREAM!"
        
    }}
}

int main(){
    return 0;
}

