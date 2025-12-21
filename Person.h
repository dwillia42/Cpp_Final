#ifndef PERSON_H
#define PERSON_H

class GameData;

using namespace std;

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
    public:
        Person();
        Person(string name, int age, string gender);
        void SetDesc(string description);
        void PrintDesc();
        void SetName(string name);
        string GetName() const;
        string GetGender() const;
        int GetAge();
        void Dialogue(GameData& game);
        void SetDialogue(const map<string, DialogueState>& dialogueMap);


};
#endif