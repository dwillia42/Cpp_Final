#include <string>
#include <map>
#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>
#include <cctype>
#include "GameData.h"

using namespace std;

//Function that creates map
void GameData::CreateMap(){
    player.InitializeMap();
    player.FillSection(houses.at(0), houses.at(1), 0);
    player.FillSection(houses.at(2), houses.at(3), 1);
    player.FillSection(houses.at(4), houses.at(5), 2);
    player.FillSection(houses.at(6), houses.at(7), 3);


}

void GameData::InitializeDialogue(){       
        map<string, DialogueState> introDialogue = {
            {"start", {
                "* Your name is Player and you have a DREAM!"
                "\n"
                "\n* And that DREAM is to become MAYOR of Village Town."
                "\n"
                "\n* You decide to go to the house labelled \"TOWN HALL\" to start your journey."
                "\n"
                "\n* As you walk up to the counter a tall, lanky man greets you."
                "\n"
                "\n* \"Hello, Player. What? Surprised I knew your name? Just a perk of being "
                "\nMAYOR. Heh heh.\""
                "\n"
                "\n* \"Anyways, welcome to TGMTEL! I suppose it's your turn to undertake the "
                "\nburden of becoming the new MAYOR.\"",

                {{"Inquire further.","choice_inquire"}}

            }},

            {"choice_inquire",{
                "* You ask Old Terry for exactly what this journey ENTAILS."
                "\n"
                "\n* \"This means confirming VOTEs Player!\""
                "\n"
                "\n* \"How do you get VOTEs? Easy! Just go house-to-house and talk to people with"
                "\nyour ACTs. You may need to do a simple Compliment, Offer something from your"
                "\nINVENTORY, or even Challenge the person.\""
                "\n"
                "\n* \"Though beware that some people have a spine and will take on your "
                "\nchallenge.\""
                "\n"
                "\n* \"So, are you up for the task?\"",

                {{"Accept.", "challenge_accepted"}}

            }},

            {"challenge_accepted", {
                "* \"I hope you considered your choice well. Good luck, Player. I\'m sure"
                "\nthis\'ll be your chair soon. Now get out there already! P.S. my kid\'s in the"
                "\nhouse across, try talking to her, it\'d be good practice for ACTing.\""
                "\n"
                "\n* You leave with HOPE in your heart. You stand on the road now, feeling the"
                "\nbreeze of Village Town on your very soul.",

                {}
            }}


        };

        map<string, DialogueState> havidayDialogue = {
            {"start", {
                "* You knock on The Haviday House door."
                "\n* A child looks through the window before slowly opening the door. The both of"
                "\nyou awkwardly waited for a few seconds before the child spoke up first."
                "\n"
                "\n* \"Hi, I'm Noel Haviday, my parents said th-there was a person coming and to"
                "\ngr-greet them at the door, that\'s you, right?\""
                "\n"
                "\n* You nod, it must be Old Terry\'s kid."
                "\n"
                "\n* \"Oh ok. Th-then nice to see you, I guess? You should try an act, wait it\'s"
                "\nactually called ACT, right?\"",

                {{"Compliment.", "choice_compliment"}, {"Offer. (" + to_string(player.GetSizeOfInventory()) + " item(s))", "choice_offer"},
                {"Challenge.","choice_challenge"}}

            }},

            {"choice_compliment", {
                "* You told Noel that she was ok to talk with, today."
                "\n"
                "\n* Noel breathes a sigh of relief, waves and closes the door."
                "\n"
                "\n* You have secured Noel Haviday\'s vote.",

                {{"Leave", "choice_leave"}}
            }},

            {"choice_challenge", {
                "* You made fun of Noel for how she messed up the terminology of diegetic game"
                "\nmechanics."
                "\n"
                "\n* \"Haha, I don\'t really get it but I s-suppose you\'re right...\""
                "\n"
                "\n* You have secured Noel Haviday\'s vote.",

                {{"Leave", "choice_leave"}}
            }},

            {"choice_offer", {
                "* You look for something to offer...",

                {}
            }},

            {"null_offer", {
                "* \"Were you trying to g-give me something? Th-thanks for the thought, I"
                "\nsuppose.\""
                "\n"
                "\n* You have secured Noel Haviday\'s vote.",

                {{"Leave", "choice_leave"}}
            }},

            {"choice_leave", {
                "* You have left " + houses.at(1).GetHouseName() + ".",

                {}
            }}
        };

        map<string, DialogueState> eriDialogue = {
            {"start", {
                "* You knock on The Adias House door."
                "\n"
                "\n* You hear a loud sigh and a broom being set down. The door opens to what "
                "\nseems like a tired maid."
                "\n"
                "\n* \"Greetings... this is The Adias Have... Do you have a message you\'d like me "
                "\nto giv- Oh wait you\'re Player, that MAYOR candidate. You can\'t see the Adias\',"
                "\n right now. I\'m Eri Jinnsen, their maid.\"",
    
                {{"Compliment.", "choice_compliment"}, {"Offer. (" + to_string(player.GetSizeOfInventory()) + " item(s))", "choice_offer"},
                {"Challenge.","choice_challenge"}}
            }},

            {"choice_tryAgain", {
                "* You decide to give convincing Eri Jinnsen another try...",
                
                {{"Compliment.", "choice_compliment"}, {"Offer. (" + to_string(player.GetSizeOfInventory()) + " item(s))", "choice_offer"},
                {"Challenge.","choice_challenge"}}

            }},

            {"choice_compliment", {
                "* You commented on all the hard work the maid has done for this family, "
                "\nand that under your policies that surely it\'d be more noticed."
                "\n"
                "\n* \"Oh, wow, some actual appreciation for all I do, I suppose I should vote for "
                "\nyou."
                "\n"
                "\n* You have secured Eri Jinnsen\'s vote.",
                
                {{"Leave", "choice_leave"}}
            }},

            {"choice_challenge", {
                "* You told Eri that it was a waste of time to come here if you couldn\'t get a "
                "\nvote out of it."
                "\n"
                "* \"Gee, you seem like a greeaaat MAYOR candidate.\""
                "\n"
                "* You have not secured Eri Jinnsen\'s vote.",
                
                {{"Try again.", "choice_tryAgain"}, {"Leave","choice_leave"}}
            }},

            {"choice_offer", {
                "* You look for something to offer...",

                {}
            }},

            {"null_offer", {
                "* \"What? I guess you can come back later?.\""
                "\n"
                "\n* You have not secured Eri Jinnsen\'s vote.",

                {{"Try again.", "choice_tryAgain"}, {"Leave.","choice_leave"}}
            }},

            {"Quiz Paper_choice", {
                "* You feel that you need to save this item for someone else.",

                {{"Compliment.", "choice_compliment"}, {"Offer. (" + to_string(player.GetSizeOfInventory()) + " item(s))", "choice_offer"},
                {"Challenge.","choice_challenge"}}
            }},

            {"Health Curriculum_choice",{
                "* You feel that you need to save this item for someone else.",

                {{"Compliment.", "choice_compliment"}, {"Offer. (" + to_string(player.GetSizeOfInventory()) + " item(s))", "choice_offer"},
                {"Challenge.","choice_challenge"}}
            }},

            {"choice_leave", {
                "* You have left " + houses.at(2).GetHouseName() + ".",

                {}
            }}
        };

        map<string, DialogueState> joDialogue = {
            {"start", {
                "* You knock on The Jo House door."
                "\n"
                "\n* Through the door you hear some music playing. As the door opens it gets louder. A well-dressed man appears."
                "\n"
                "\n* \"Hey, what\'s up. You\'re Player, right? They call me Jorimiah Jo. Letting "
                "\nyou know I\'m not voting for an uncultured nobody to be MAYOR. Got "
                "\nsomething to say about that?\"",

                {{"Compliment.", "choice_compliment"}, {"Offer. (" + to_string(player.GetSizeOfInventory()) + " item(s))", "choice_offer"},
                {"Challenge.","choice_challenge"}}
            }},

            {"choice_tryAgain", {
                "* You decide to give convincing Jorimiah Jo another try...",
                
                {{"Compliment.", "choice_compliment"}, {"Offer. (" + to_string(player.GetSizeOfInventory()) + " item(s))", "choice_offer"},
                {"Challenge.","choice_challenge"}}

            }},

            {"choice_compliment", {
                "* You said that you thought the music sounded really cool."
                "\n"
                "\n* \"Well yeah it should, it\'s part of Village Town\'s history, do you even know "
                "\nthat much?\""
                "\n"
                "\n* You have not secured Jorimiah Jo\'s vote.",
                
                {{"Try again.", "choice_tryAgain"}, {"Leave.","choice_leave"}}
            }},

            {"choice_challenge", {
                "* You asked Jorimiah Jo what culture has to do with being a MAYOR."
                "\n"
                "\n* \"Seriously?\""
                "\n"
                "* You have not secured Jorimiah Jo\'s vote.",
                
                {{"Try again.", "choice_tryAgain"}, {"Leave.","choice_leave"}}
            }},

            {"choice_offer", {
                "* You look for something to offer...",

                {}
            }},

            {"null_offer", {
                "* \"Get out, already. Wasting my time here. Go to the Library or something,"
                "\nfirst.\""
                "\n"
                "\n* You have not secured Jorimia Jo\'s vote.",

                {{"Try again.", "choice_tryAgain"}, {"Leave.","choice_leave"}}
            }},

            {"Health Curriculum_choice",{
                "* You feel that you need to save this item for someone else.",

                {{"Compliment.", "choice_compliment"}, {"Offer. (" + to_string(player.GetSizeOfInventory()) + " item(s))", "choice_offer"},
                {"Challenge.","choice_challenge"}}
            }},

            {"Quiz Paper_choice", {
                "* You thought that you should give the \"Quiz Paper\" to Jorimiah Jo."
                "\n"
                "\n* \"Wait, hold on... You want me to quiz you? You might not be that"
                "\nuncultured after all.\""
                "\n"
                "\n* \"Welp, the first question is: Who was the first MAYOR and when were they"
                "\nelected?\"",

                {{"Toreor in the Spring of 2029.", "choice_Toreor29"},
                 {"Nasuto in the Spring of 2030.", "choice_Nasuto30"},
                 {"Nasuto in the Winter of 2029.", "choice_Nasuto29"}}
            }},

            {"choice_q1redo", {
                "* Who was the first MAYOR and when were they elected?",

                {{"Toreor in the Spring of 2029.", "choice_Toreor29"},
                 {"Nasuto in the Spring of 2030.", "choice_Nasuto30"},
                 {"Nasuto in the Winter of 2029.", "choice_Nasuto29"}}
            }},

            {"choice_Toreor29", {
                "* Jorimiah sighs, you got it wrong, try again?",

                {{"Try Again.", "choice_q1redo"}}
            }},

            
            {"choice_Nasuto30", {
                "* Jorimiah sighs, you got it wrong, try again?",

                {{"Try Again.", "choice_q1redo"}}
            }},

            {"choice_Nasuto29", {
                "\"Okay... Now: What was the worst part of the surviving forces of evil?\"",

                {{"They were more powerful.", "choice_powerful"},
                 {"They had aligned their goals.", "choice_goals"},
                 {"They were more intelligent.", "choice_intelligent"}}
            }},

            {"choice_q2redo", {
                "What was the worst part of the surviving forces of evil?",

                {{"They were more powerful.", "choice_powerful"},
                 {"They had aligned their goals.", "choice_goals"},
                 {"They were more intelligent.", "choice_intelligent"}}
            }},

            {"choice_powerful", {
                "* Jorimiah sighs, you got it wrong, try again?",

                {{"Try Again.", "choice_q2redo"}}
            }},

            {"choice_intelligent", {
                "* Jorimiah sighs, you got it wrong, try again?",

                {{"Try Again.", "choice_q2redo"}}
            }},

            {"choice_goals", {
                "\"Yep, so, last question: What was the hero\'s favorite festival song?\"",

                {{"\"Chance.\"", "choice_chance"},
                 {"\"Chase.\"", "choice_chase"}}
            }},

            {"choice_q3redo", {
                "What was the hero\'s favorite festival song?",

                {{"\"Chance.\"", "choice_chance"},
                 {"\"Chase.\"", "choice_chase"}}
            }},

            {"choice_chance", {
                "* Jorimiah sighs, you got it wrong, try again?",

                {{"Try Again.", "choice_q3redo"}}
            }},
            
            {"choice_chase", {
                "* \"I guess, this is sufficient evidence to me that you\'ve been trying to" 
                "\nlearn about Village Town\'s culture. Don\'t waste my vote.\""
                "\n"
                "\n* You have secured Jorimiah Jo\'s vote.",


                {{"Leave.", "choice_leave"}},
            }},

            {"choice_leave", {
                "* You have left " + houses.at(3).GetHouseName() + ".",

                {}
            }}
            
        };

        map<string, DialogueState> clarkDialogue = {
            {"start", {
                "* You push the Library double doors open and enter."
                "\n"
                "\n* A broad-shouldered man notices you from his counter, he looks a little "
                "\nbored. He was probably expecting you."
                "\n"
                "\n* \"Geez, didn\'t expect it to take that long for a person to realize they" 
                "\nshould probably learn about the town they wanna be the MAYOR of. Name\'s Clark "
                "\nWoodpecker, by the way.\""
                "\n"
                "\n* \"Here, I got a book here for you, you\'re probably in a rush so you can just "
                "\nskim the sections I highlighted. I\'m counting on you winning.\""
                "\n"
                "\n* \"Village Town: The Last Town\""
                "\n"
                "\n* You notice a BLUE bookmark marked \"the founding\""
                "\n"
                "\n* And the other is a LILAC one labelled \"party\"",


                {{"BLUE.", "choice_founding"},
                {"LILAC.","choice_party"}}
            }},

            {"choice_founding", {
                "* Now reading \"the founding\""
                "\n"
                "\n* Okay, so what you\'ve learned is that decades ago reality broke or whatever. "
                "\nBack in 2029, without permission, each and every humans\' single greatest HOPE "
                "\nwas granted, and the contradictions messed stuff up (among other things). and "
                "\nthe WORLD you live in now is the amalgamation of that, Village Town was formed "
                "\nas a refuge for the especially fictionalized people (whatever that means). The "
                "\nfirst MAYOR was Nasuto, around the winter of 2029.",

                
                {{"Check out \"LILAC\".","choice_party2"}}
            }},

            {"choice_party", {
                "* Now reading \"party\""
                "\n"
                "\n* Hm, so, like a few years ago, the FIGHT between all the great evils ended "
                "\nand although the forces of evil were reduced and tired, the entities left "
                "\nstanding were of the most powerful, of the most intelligent, and of the most "
                "\ndangerous. What\'s worse was that these evils chose to align their goals, it "
                "\nwas truly the sign of something insurmountable. And yet the Hero, with her "
                "\nparty, stopped them all. "
                "\n"
                "\n* A great festival was hosted in Village Town, and the Hero still lives here "
                "\nnow, the Hero said her favorite song was \"Chase.\"",

                
                {{"Check out \"BLUE\".", "choice_founding2"}}
            }},

            {"choice_founding2", {
                "* Now reading \"the founding\""
                "\n"
                "\n* Okay, so what you\'ve learned is that decades ago reality broke or whatever. "
                "\nBack in 2029, without permission, each and every humans\' single greatest HOPE "
                "\nwas granted, and the contradictions messed stuff up (among other things). and "
                "\nthe WORLD you live in now is the amalgamation of that, Village Town was formed "
                "\nas a refuge for the especially fictionalized people (whatever that means). The "
                "\nfirst MAYOR was Nasuto, around the winter of 2029.",

                
                {{"Check out \"LILAC\" again.","choice_party2"}, {"Tell Clark you\'re done.","choice_finished"}}
            }},

            {"choice_party2", {
                "* Now reading \"party\""
                "\n"
                "\n* Hm, so, like a few years ago, the FIGHT between all the great evils ended "
                "\nand although the forces of evil were reduced and tired, the entities left "
                "\nstanding were of the most powerful, of the most intelligent, and of the most "
                "\ndangerous. What\'s worse was that these evils chose to align their goals, it "
                "\nwas truly the sign of something insurmountable. And yet the Hero, with her "
                "\nparty, stopped them all. "
                "\n"
                "\n* A great festival was hosted in Village Town, and the Hero still lives here "
                "\nnow, the Hero said her favorite song was \"Chase.\"",

                
                {{"Check out \"BLUE\" again.", "choice_founding2"}, {"Tell Clark you\'re done.","choice_finished"}}
            }},

            {"choice_finished", {
                "* Clark gets a soft smile and hands you the \"Quiz Paper.\""
                "\n"
                "\n* \"Do this when you have to really impress a certain someone in this town.\"",

                {{"Leave.", "choice_leave"}},
            }},

            {"choice_leave", {
                "* You have left " + houses.at(4).GetHouseName() + ".",

                {}
            }}
        };
        
        map<string, DialogueState> verisDialogue = {
            {"start", {
                "* You knock on The Serket House door."
                "\n"
                "\n* This house looks noticeably more fancy than the rest, you also had to knock "
                "\nfor a while before you heard someone run down the stairs."
                "\n"
                "\n* A lady in a coat looks at you with one eye, the other covered by an "
                "\neyepatch. She seems unimpressed and you think she probably has better things "
                "\nto do."
                "\n"
                "\n* \"Hey, you must be Player. Nice to meet you, I\'m Veris. Look, I know you\'re "
                "\ntrying to be the MAYOR and all that but I\'m in the middle of making sure my "
                "\nfriends don\'t screw over the game we\'re playing while I\'m in charge. So could "
                "\nyou hurry this up?\"",


                {{"Compliment.", "choice_compliment"}, {"Offer. (" + to_string(player.GetSizeOfInventory()) + " item(s))", "choice_offer"},
                {"Challenge.","choice_challenge"}}
            }},

            {"choice_tryAgain", {
                "* You decide to give convincing Veris Serket another try...",
                
                {{"Compliment.", "choice_compliment"}, {"Offer. (" + to_string(player.GetSizeOfInventory()) + " item(s))", "choice_offer"},
                {"Challenge.","choice_challenge"}}

            }},

            {"choice_compliment", {
                "* You told Veris that she seems like a very important person."
                "\n"
                "\n* \"I really don\'t need YOU of all people to tell me that. Don\'t think you can get "
                "\nme to vote for you with petty compliments like that.\""
                "\n"
                "\n* You have not secured Veris Serket\'s vote.",
                
                {{"Try again.", "choice_tryAgain"}, {"Leave.","choice_leave"}}
            }},

            {"choice_challenge", {
                "* You asked Veris if she\'d be up for a game of TIC-TAC-TOE, and the winner was "
                "\nwas obviously the better leader."
                "\n"
                "\n* \"Huh? What does that have to do with leading? Wait, where do you think "
                "\nyou\'re going, we\'re gonna play this game and I\'m gonna win.\"",

                {{"Start game.", "start_Minigame"}}
            }},

            {"start_Minigame", {
                "",

                {}
            }},

            {"veris_Win", {
                "* You couldn't win."
                "\n"
                "\n* \"Wow, you\'re not very good at this, but a person like you would be fine as "
                "\na MAYOR while I do my actually important things.\""
                "\n"
                "\n* You have secured Veris Serket\'s vote.",

                {{"Leave", "choice_leave"}}
            }},

            {"player_Win", {
                "* You\'ve won."
                "\n"
                "\n* \"Well, I was in a hurry. And usually I\'m a lot more lucky. Go ahead and win "
                "\nthat MAYOR thing already, I guess........\""
                "\n"
                "\n* You have secured Veris Serket\'s vote.",


                {{"Leave", "choice_leave"}}
            }},

            {"choice_offer", {
                "* You look for something to offer...",

                {}
            }},

            {"null_offer", {
                "\n* \"Look even if you did have anything to offer, I\'m not exactly starved for "
                "\nstuff.\""
                "\n"
                "\n* You have not secured Veris Serket\'s vote.",

                {{"Try again.", "choice_tryAgain"}, {"Leave.","choice_leave"}}
            }},

            {"Quiz Paper_choice", {
                "* You feel that you need to save this item for someone else.",

                {{"Compliment.", "choice_compliment"}, {"Offer. (" + to_string(player.GetSizeOfInventory()) + " item(s))", "choice_offer"},
                {"Challenge.","choice_challenge"}}
            }},

            {"Health Curriculum_choice",{
                "* You feel that you need to save this item for someone else.",

                {{"Compliment.", "choice_compliment"}, {"Offer. (" + to_string(player.GetSizeOfInventory()) + " item(s))", "choice_offer"},
                {"Challenge.","choice_challenge"}}
            }},

            {"choice_leave", {
                "* You have left " + houses.at(5).GetHouseName() + ".",

                {}
            }}
        };

        map<string, DialogueState> adiasDialogue = {
            {"start", {
                "* You enter through the glass doors of the Clinic."
                "\n"
                "\n* A man with a shaved head gets up from his desk and prepares a chair for you."
                "\n"
                "\n* The both of you sit down."
                "\n"
                "\n* \"Player, welcome to our town, you\'ve gotten to meet some people so far, "
                "\nright? Regardless, I\'m Dr. Adias. Nice to meet you.\""
                "\n"
                "\n* \"I\'ll just skip to the point: This clinic\'s too small to handle how the "
                "\nkids seem to get themselves bruised or sick as often as they do.\""
                "\n"
                "\n* \"Now, you\'ve already got my vote, since I trust Terry with this kind of "
                "\nstuff, but-\""
                "\n"
                "\n* \"In return, I want you to take this book I wrote and give it to the school "
                "\nnext door. To teach them y\'know? Just so the kids stop troubling me so much.\""
                "\n"
                "\n* Dr. Adias hands you his \"Health Curriculum\" and you put it in your" 
                "\ninventory."
                "\n"
                "\n* \"Great working with you.\"",

                {{"Leave.", "choice_leave"}}
            }},

            {"choice_leave",{
                "* You have left " + houses.at(6).GetHouseName() + ".",

                {}
            }}
        };
        
        map<string, DialogueState> laiosDialogue = {
            {"start", {
                "* You click on the bell for the School doors and a few seconds later you hear "
                "\na buzzing noise. Someone is telling you to come in."
                "\n"
                "\n* As you enter, you see a suited man walk over, his hair in a bun. He flips "
                "\nthrough his clipboard a bit before paying attention to you again."
                "\n"
                "\n* \"Hey, it\'s you! Our maybe-soon-to-be-MAYOR Player I\'ve been hearing about! "
                "\nMy name\'s Laios Vangrad. I\'m a teacher here in Village Town and my "
                "\nstudents...\""
                "\n"
                "\n* \"My students... are too smart! They don\'t come to school as often and they "
                "\nalways complain about my work being too boring. It feels like there\'s always "
                "\none kid who knows what I\'m talking about more than me.\""
                "\n"
                "\n* \"Sorry, I\'m busy looking through the curriculum for things I could do "
                "\nbetter. Got anything you wanna say?\"",


                {{"Compliment.", "choice_compliment"}, {"Offer. (" + to_string(player.GetSizeOfInventory()) + " item(s))", "choice_offer"},
                {"Challenge.","choice_challenge"}}

            }},

            {"choice_tryAgain", {
                "* You decide to give convincing Laios Vangrad another try...",
                
                {{"Compliment.", "choice_compliment"}, {"Offer. (" + to_string(player.GetSizeOfInventory()) + " item(s))", "choice_offer"},
                {"Challenge.","choice_challenge"}}

            }},

            {"choice_compliment", {
                "* You told Laios that he should be proud that his teaching made his students "
                "\nsmart."
                "\n"
                "\n* \"I\'m flattered, but some of my students skip very often and still do great on "
                "\ntheir tests! I don\'t think you get the scope of my problem...\""
                "\n"
                "\n* You have not secured Laios Vangrad\'s vote.",


                {{"Try again.", "choice_tryAgain"}, {"Leave.","choice_leave"}}
            }},

            {"choice_challenge", {
                "* You asked Laios to consider taking up a different job."
                "\n"
                "\n* \"But, I still like teaching. I\'m not much good at anything else.\""
                "\n"
                "\n* You have not secured Laios Vangrad\'s vote.",

                {{"Try again.", "choice_tryAgain"}, {"Leave.","choice_leave"}}
            }},

            {"choice_offer", {
                "* You look for something to offer...",

                {}
            }},

            {"null_offer", {
                "* But, you had nothing to offer..."
                "\n"
                "\n* \"Oh. I was hoping you\'d have something I could add to the curriculum but "
                "\nyou just put your arms out for nothing. Maybe you should go to the Clinic if "
                "\nyou\'re feeling out of it.\""
                "\n"
                "\n* You have not secured Laios Vangrad\'s vote.",

                {{"Try again.", "choice_tryAgain"}, {"Leave.","choice_leave"}}

            }},

            {"Health Curriculum_choice", {
                "* You thought that you should give the \"Health Curriculum\" to Laios Vangrad."
                "\n"
                "* \"Wait, did you get this from Dr. Adias? This is just what I needed! Thanks!\""
                "\n"
                "\n* You have secured Laios Vangrad\'s vote.",

                {{"Leave.","choice_leave"}}
            }},

            {"Quiz Paper_choice",{
                "* You feel that you need to save this item for someone else.",

                {{"Compliment.", "choice_compliment"}, {"Offer. (" + to_string(player.GetSizeOfInventory()) + " item(s))", "choice_offer"},
                {"Challenge.","choice_challenge"}}
            }},

            {"choice_leave", {
                "* You have left " + houses.at(6).GetHouseName() + ".",

                {}
            }}
        };

        map<string, DialogueState> exitDialogue = {
            {"start", {
                "* Your journey is nearly over, you\'ve talked to all those people and maybe "
                "\n"
                "something can come out of it now."
                "\n* You turn the door knob, and it\'s unlocked."
                "\n"
                "\n* As you enter the Town Hall you think about all the people you\'ve met."
                "\n"
                "\n* Veris, Dr. Adias, Jorimiah, Noel, Eri, Clark, Laios, and even Old Terry."
                "\n"
                "\n* You hope they follow through and vote for you."
                "\n"
                "\n* You don\'t see Old Terry but there\'s shuffling sounds behind the counter."
                "\n"
                "\n* \"Hi Player, great job out there, I\'m just in the back getting the town\'s "
                "\nvotes online. Just wait a bit and I\'ll have the results soon.\""
                "\n"
                "\n* It took a few minutes but he came back with a piece of paper he just printed "
                "\nwith the results."
                "\n"
                "\n* \"What\'s with the confused look? Didn\'t you think more people lived here than "
                "\nyou saw? Well I\'m reading the results and..."
                "\n"
                "\n* by a very close margin, you won!\""
                "\n"
                "\n* Wait, really? You completed your one true goal!"
                "\n"
                "\n* \"Surprising how close it was when I specifically asked everyone to let me "
                "\nretire already. Though, in all honesty, what do you know about MAYORing, "
                "\nanyways?\""
                "\n"
                "\n* You thought the point was to become MAYOR?"
                "\n"
                "\n* \"Ehh, I suppose it doesn\'t matter anyways.\""
                "\n"
                "\n* \"Good Game, Player.\"",


                {{"GAME OVER.", "choice_over"}}
            }},

            {"choice_over",{
                "Thanks for playing :]",

                {}
            }}
        };

        SetPersonDialogue(0, introDialogue);
        SetPersonDialogue(1, havidayDialogue);
        SetPersonDialogue(2, eriDialogue);
        SetPersonDialogue(3, joDialogue);
        SetPersonDialogue(4, clarkDialogue);
        SetPersonDialogue(5, verisDialogue);
        SetPersonDialogue(6, adiasDialogue);
        SetPersonDialogue(7, laiosDialogue);

}

House GameData::GetHouse(int i){
    return houses.at(i);
}

vector<Person>& GameData::GetPeople(){
    return people;
}

void GameData::SetPersonDialogue(int personIndex, map<string, DialogueState> dialogueMap){
        this->people.at(personIndex).SetDialogue(dialogueMap);
}

void GameData::InitializeCharacterDescriptions(){
    string OldTerryDesc = "The current mayor of the town."
                          "\nHe\'s looking to retire at the ripe age of " + to_string(GetPeople().at(0).GetAge()) + ".";
    string havidayDesc = "The " + to_string(GetPeople().at(1).GetAge()) + "-year-old daughter of the Havidays."
                         "\nOften hanging out with the neighborhood kid her age.";
    string eriDesc = "Maid working to tend the Adias home."
                     "\nIs thinking about moving out.";
    string joDesc = "Has previously tried to be mayor."
                    "\nHe's usually home making videos.";
    string clarkDesc = "Old Terry's friend from way back."
                       "\nHe likes volunteering at the library.";
    string verisDesc = "Her family's relatively wealthy."
                       "\nAnd at only " + to_string(GetPeople().at(5).GetAge()) + " she's playing a way harder game than you.";
    string adiasDesc = "He runs a small local clinic."
                       "\nHe expected being a doctor would be cooler.";
    string laiosDesc = "He's been teaching for 15 years."
                       "\nHis students prefer the library.";

    this->people.at(0).SetDesc(OldTerryDesc);
    this->people.at(1).SetDesc(havidayDesc);
    this->people.at(2).SetDesc(eriDesc);
    this->people.at(3).SetDesc(joDesc);
    this->people.at(4).SetDesc(clarkDesc);
    this->people.at(5).SetDesc(verisDesc);
    this->people.at(6).SetDesc(adiasDesc);
    this->people.at(7).SetDesc(laiosDesc);


}
