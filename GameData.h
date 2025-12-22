#ifndef GAMEDATA_H
#define GAMEDATA_H

#include <string>
#include <map>
#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>
#include <cctype>
#include "Player.h"
using namespace std;


class GameData{
    private:
    //All of the data needed for the game, as well as method to initialize the data.
    vector<Person> people ={Person("Old Terry", 43, "male"),
                            Person("Noel Haviday", 12, "female"),
                            Person("Eri Jinnsen", 24, "female"),
                            Person("Jorimiah Jo", 30, "male"),
                            Person("Clark Woodpecker", 39, "male"),
                            Person("Veris Serket", 16, "female"),
                            Person("Dr. Adias", 35, "male"),
                            Person("Laios Vangrad", 48, "male")};

    vector<House> houses = {House(people.at(0), "Town Hall", "00 West Mayor Street"),
                            House(people.at(1), "The Haviday House", "02 East Mayor Street"),
                            House(people.at(2), "The Adias House", "10 West Mayor Steet"),
                            House(people.at(3), "The Jo House", "12 East Mayor Street"),
                            House(people.at(4), "The Library", "20 West Mayor Street"),
                            House(people.at(5), "The Serket House", "22 East Mayor Street"),
                            House(people.at(6), "The Clinic", "30 West Mayor Street"),
                            House(people.at(7), "The School", "32 East Mayor Street")};
    public:
    Player player;
    void CreateMap();
    void InitializeDialogue();
    void InitializeCharacterDescriptions();
    vector<Person>& GetPeople();
    void SetPersonDialogue(int personIndex, map<string, DialogueState> dialogueMap);
    House GetHouse(int i);
    void SetEndingDialogue();
};

#endif
