#ifndef PERSON_H
#define PERSON_H

#include <string>
#include <map>
#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>

class GameData;

using namespace std;

//Two structs DialogueOption and DialogueState.
//Needed in order for the dialogue to work properly
struct DialogueOption{
        string choice;
        string nextState;
    };

struct DialogueState{
        string text;
        vector<DialogueOption> choices;
    };
class Person{
    private:
        map<string, DialogueState> dialogueMap;
        string name;    
        string gender;
        string description;
        int age;
        bool voteSecured = false;
    public:
        Person();
        Person(string name, int age, string gender);
        void SetDesc(string description);
        void PrintDesc();
        void SetName(string name);
        string GetName() const;
        string GetGender() const;
        int GetAge();
        vector<string> Dialogue(GameData& game);
        map<string, DialogueState> GetDialogue();
        void SetDialogue(map<string, DialogueState> dialogueMap);
        void HasVoted();
        bool VoteStatus();


};
#endif