#include <iostream>
#include "functions.h"
using namespace std;


void goodoutcome(int &outcomeval, int &player_coin, int &player_pos){ //
    string UserOutcomePick;
    
    cout<< "Congrats, you beat the guard at the minigame! Choose your reward! << endl << Enter c to win a bag of coins or f to move forwards:";
    cin >> UserOutcomePick;
    
    while (UserOutcomePick!= "c" && UserOutcomePick!= "f"){
            cout << "Please enter one of the following options only. " << endl;
            cout << "|||| c for coins |||| f for move forward ||||" << endl;
            cin >> UserOutcomePick;
        } //in case user did not answer in the right format
        
    
    srand(time(0));
    int randomgoodluck = rand() % 3 + 1; //bonus points is 1-3
    
    int combined_points = randomgoodluck + outcomeval;
    
    if(combined_points >= 4) {
        if (UserOutcomePick ==  "c"){
            player_coin += 5;
            cout << "You've been rewarded with a bag of 5 coins!" << endl;}
        else if (UserOutcomePick ==  "f"){
            player_pos += 5;
            cout << "You've been teleported 5 tiles forwards!" << endl;}
    }
    else if(combined_points>= 2) {
        if (UserOutcomePick ==  "c"){
            player_coin += 3;
            cout << "You've been rewarded with a bag of 3 coins!" << endl;}
        else if (UserOutcomePick ==  "f"){
            player_pos += 3;
            cout << "You've been teleported 3 tiles forwards!" << endl;}
    }
    else if(combined_points >= 0){
        if (UserOutcomePick ==  "c"){
            player_coin += 2;
            cout << "You've been rewarded with a bag of 2 coins!" << endl;}
        else if (UserOutcomePick ==  "f"){
            player_pos += 2;
            cout << "You've been teleported 2 tiles forwards!" << endl;}
    }
} 
    

void badoutcome(int &outcomeval, int &player_coin, int &player_pos){
    if (use_item("Shield", player_inventory) == false)  // if no shield in inventory, execute badoutcome. (shield protects, hence badoutcome not xcute.)
    {                                                   // if true (yes shield), badoutcome() body bypassed.
        string UserOutcomePick;

        cout<< "Unfortunate!, you lsot to the guard at the minigame. Choose your penalty! << endl << Enter c to lose coins or f to move backwards:";
        cin >> UserOutcomePick;

        while (UserOutcomePick!="c" && UserOutcomePick!= "b"){
                cout << "Please enter one of the following options only. " << endl;
                cout << "|||| c for coins |||| b for move backwards ||||" << endl;
                cin >> UserOutcomePick;
            } //in case user did not answer in the right format


        srand(time(0));
        int randombadluck = (rand() % 3 + 1)*(- 1); //bonus penalty is -1 to -3

        int combined_points = randombadluck + outcomeval;

        if(combined_points <= -4) {
            if (UserOutcomePick ==  "c"){
                player_coin += 5;
                cout << "You lost 5 coins to the goblin." << endl;}
            else if (UserOutcomePick ==  "b"){
                player_pos += 5;
                cout << "The goblin pushed you 5 steps backwards..." << endl;}
        }
        else if(combined_points<= -2) {
            if (UserOutcomePick ==  "c"){
                player_coin += 3;
                cout << "You lost 3 coins to the goblin." << endl;}
            else if (UserOutcomePick ==  "b"){
                player_pos += 3;
                cout << "The goblin pushed you 3 steps backwards..." << endl;}
        }
        else if(combined_points <= 0){
            if (UserOutcomePick ==  "c"){
                player_coin -= 2;
                cout << "You lost 2 coins to the goblin." << endl;}
            else if (UserOutcomePick ==  "b"){
                player_pos -= 2;
                cout << "The goblin pushed you 2 steps backwards..." << endl;}
        }
    }
    else    // if func returns true, ie. there is shield in inventory
    { 
        cout << "you used a shield to protect yourself! You didn't lose any of your belongings.";
    }
        
} 
 
