#ifndef PERSON_H
#define PERSON_H

using namespace std;

class Person{
    private:

    struct DialogueOption{
        string choice;
        string nextState;
    };

    struct DialogueState{
        string text;
        vector<DialogueOption> choices;
    };
        map<string, DialogueState> dialogueMap;
        string name;    
        string gender;
        int age;
    public:
        Person(string name, int age, string gender);
        void PrintDesc();
        void Dialogue();
        void SetDialogueMap(const map<string, DialogueState>& dialogueMap){
            this->dialogueMap = dialogueMap;
        }


};
#endif