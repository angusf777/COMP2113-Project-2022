#include <iostream>
#include "functions.h"
using namespace std;

/*Outcome Rules:
-2 for quitting the game
-1 for default performance (bad performance)
0 to 2 for good performance (add one point if the player wins one round)
3 for no outcome
*/

 // contains special items eg. shield to protect players if they encountered bad outcomes

//generate good outcome accoording to the performance score inputted to the function
void goodoutcome(int outcomeval, game_info &p1){ 
    string UserOutcomePick;
    
    if (outcomeval == 3){                                                                            //this means no good or bad outcome will occur as the player might performed neutral in the game
        cout << "Congrats on completing the game with peace, neither good or bad outcome happened!"<< endl;
    }
    else {                                                                                           //this means the player performed good in the mini games, and the player will now choose to be awarded by coins or by steps
        cout<< "Congrats, you beat the goblin at the minigame! Choose your reward!" << endl;  
        cout << "Enter c to win a bag of coins or f to move forwards:";                              //player will enter their options
        cin >> UserOutcomePick;
        
        while (UserOutcomePick!= "c" && UserOutcomePick!= "f"){                                             
                cout << "Please enter one of the following options only. " << endl;
                cout << "|||| c for coins |||| f for move forward ||||" << endl;
                cin >> UserOutcomePick;
            }                                                                                        //in case user did not answer in the right format
            

        
        if (outcomeval == 2) {                                                                      // this is the best outcome that the player could achieve in the mini games
            if (UserOutcomePick ==  "c"){                                                                 // if the player chooses to be awarded with coins
                p1.player_coin += 5;
                cout << "You've been rewarded with a bag of 5 coins!" << endl;}
            else if (UserOutcomePick ==  "f"){                                                             //if the player chooses to be awarded with steps
                p1.player_pos += 5;
                cout << "You've been teleported 5 tiles forwards!" << endl;}
        }
        else if(outcomeval == 1) {                                                                 // another good outcome
            if (UserOutcomePick ==  "c"){
                p1.player_coin += 3;
                cout << "You've been rewarded with a bag of 3 coins!" << endl;}
            else if (UserOutcomePick ==  "f"){
                p1.player_pos += 3;
                cout << "You've been teleported 3 tiles forwards!" << endl;}
        }
        else if(outcomeval == 0){                                                                 // another good outcome
            if (UserOutcomePick ==  "c"){
                p1.player_coin += 2;
                cout << "You've been rewarded with a bag of 2 coins!" << endl;}
            else if (UserOutcomePick ==  "f"){
                p1.player_pos += 2;
                cout << "You've been teleported 2 tiles forwards!" << endl;}
        }
    
    } 
}

//generate bad outcome accoording to the performance score inputted to the function
void badoutcome(int outcomeval, game_info &p1, vector<string>&player_inventory){
    string item = "Shield";
    if (use_item(item, player_inventory) == false)                                                // if no shield in inventory, execute badoutcome. (shield protects, hence badoutcome not xcute.)
    {                                                                                             // if true (yes shield), badoutcome() body bypassed.
        string UserOutcomePick;

        cout<< "Unfortunately, you quit or lost to the goblin at the minigame. Choose your penalty!" << endl;
        cout << "Enter c to lose coins or b to move backwards: ";                                // choose coins or steps as a penalty
        cin >> UserOutcomePick;

        while (UserOutcomePick!="c" && UserOutcomePick!= "b"){
                cout << "Please enter one of the following options only. " << endl;
                cout << "|||| c for coins |||| b for move backwards |||| " << endl;
                cin >> UserOutcomePick;
            } //in case user did not answer in the right format

        if(outcomeval == -1){
            if (UserOutcomePick ==  "c"){                                                         //the worst bad outcome
                p1.player_coin -= 2;
                cout << "You lost 2 coins to the goblin." << endl;}
            else if (UserOutcomePick ==  "b"){
                p1.player_pos -= 2;
                cout << "The goblin pushed you 2 steps backwards..." << endl;}
        }
        else if(outcomeval == -2){                                                               //this is the situation when the player chooses to quit the game without playing it
            cout << "Sorry to hear you are quitting this game... The goblin grabbed your coins and pushed you backwards directly." << endl;
            p1.player_coin -= 1;
            cout << "You lost 1 coins to the goblin." << endl;
            p1.player_pos -= 1;
            cout << "The goblin pushed you 1 steps backwards..." << endl;
        }
    }
    else                                                                                        // if func returns true, ie. there is shield in inventory
    { 
        cout << "you used a shield to protect yourself! You didn't lose any of your belongings." << endl;
    }
        
} 
 
