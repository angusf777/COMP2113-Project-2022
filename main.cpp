#include <iostream>
#include <iomanip>
#include <cmath>
#include <time.h>
#include <string>
#include "functions.h"
#include <map>
#include <fstream>
#include <vector>
#include <list>
#include <algorithm>

using namespace std;

// ---- func ------ PRINT INVENTORY --------
void printvec(vector<string> player_inventory)       
{   
    for (auto itrv = player_inventory.begin(); itrv != player_inventory.end(); itrv++)               // iterate through vector and print each item.
    {   cout << *itrv;
        if (itrv != player_inventory.end()-1)                                   // if not last item, add comma
            cout << ", ";
        if (itrv == player_inventory.end()-1)                                   // if last item, endline,
            cout << endl;
    }
} 

// generate random integer within range(lowerbound, upperbound)
int randint(int lowerbound, int upperbound)
{
    srand(time(0));
    return lowerbound + (rand() % upperbound);
}

// choose character to play with, each character has different special skill.
void choose_char(game_info &p1) 
{
    if (p1.player_char == "RAY")
    {
        p1.player_skill = "Speed up";
        cout << "You skill is " << p1.player_skill << endl;
        cout << "Add 2 to dice value rolled.";
    }
    else if (p1.player_char == "ANNA")
    {
        p1.player_skill = "Double movement";
        cout << "You skill is " << p1.player_skill << endl;
        cout << "Dice roll value * 2 -1 .";
    }
    else if (p1.player_char == "ANGUS")
    {
        p1.player_skill = "Money boost";
        cout << "You skill is " << p1.player_skill << endl;
        cout << "Pick up 1 coin per dice roll.";
    }
    cout << endl;
}

//takes in game_info p1 and the result of dice draw, return number of steps to move according to the skills the player have
void move_how_much(game_info &p1, int &dice_num, int &total_move, int &spec_dice_num)    
{
    if (p1.player_skill == "Speed up")
    {
        total_move = dice_num + 2;
    }
    else if (p1.player_skill == "Double movement")
    {
        total_move = dice_num * 2 - 1;
    }
    else if (p1.player_skill == "Money boost")
    {
        p1.player_coin += 1;
        total_move = dice_num;
    }
}

// check if the list contains the number (for map structure), player's pos passed here – used while activating the event triggered on certain tile
bool contains(list<int> numlist, game_info &p1)
{
    for (auto itr : numlist)
    {
        if (p1.player_pos == itr)
        {
            return true;
        }
    }
    return false;
}

//function to call minigame according to the game number inputted, then generate outcome according to player performance, reads the game_info p1 and gameno passed, gameno used to call game, game_info to change attributes in outcome function
void minigame(game_info &p1, int gameno)
{
    int outcome = 10;
    while (outcome == 10)
    {
        if (gameno == 1)
        {
            outcome = math_game(p1);
        }
        else if (gameno == 2)
        {
            outcome = doorguest_game(p1);
        }
        else if (gameno == 3)
        {
            outcome = rockpaperscissors_game(p1);
        }
        else if (gameno == 4)
        {
            outcome = defeatthekidnappers_game(p1);
        }
    }
    // above minigame return an integer outcome that corresponds to below function calls.
    if (outcome > 0 )
    {
        goodoutcome(outcome, p1);
    }
    else if (outcome <= 0)
    {
        badoutcome(outcome, p1, player_inventory); // if return is -2, = they quit the game and hence auto bad outcome.
    }
}

//trigger event according to the position the player gets to, takes in player's position, coins, and time_count with reference, and call function according to the position of the player
void triggerevent(game_info &p1)
{
    if (contains({2, 3, 6, 9, 13, 15, 19, 21, 24, 28, 30, 32, 33, 38}, p1))
    {
        int ran_num = randint(1, 4);
        minigame(p1, ran_num);
    }
    else if (contains({7, 18, 25, 37}, p1))
    {
        cout << "No enemies are nearby, keep rushing, the professor needs your help!\n";
    }
    // blank tilesca
    else if (contains({1, 16, 23}, p1))
    { // pick up 1-4 coins
        int coin_pickedup = randint(1, 4);
        p1.player_coin += coin_pickedup;
        cout << "Congratulations! You just found " << coin_pickedup << " coins on the ground!\n";
    }

    else if (contains({10, 26, 34}, p1))
    { // pick up 3-6 coins
        int coin_pickedup = randint(3, 6);
        p1.player_coin += coin_pickedup;
        cout << "You're hiding behind a bush and see a goblin drop something. You wait for him to walk further and find a bag of " << coin_pickedup << " coins!\n";
    }

    else if (contains({5, 12, 31}, p1))
    { // go back 10 seconds
        p1.time_count -= 10;
        cout << "You wandered into a small time machine. You push a button and it informed you that time went back 10 seconds!\n";
    }
    else if (contains({14, 22, 36}, p1))
    { // go forwards 10 seconds
        p1.time_count += 10;
        cout << "Oh no! You've just fallen into a trap! You managed to climb your way out, but wasted 10 seconds in it!\n";
    }
    else if (contains({4, 8, 20, 29}, p1))
    { // go back or forward 1-4 tiles
        if (randint(0, 2))
        {
            p1.player_pos += randint(1, 4);
        }
        else
        {
            p1.player_pos -= randint(1, 4);
            cout << "The spatial instability in this realm has caused you to teleport to a nearby tile! you are now at tile " << p1.player_pos << "!\n";
        }
    }
    else if (contains({35, 39}, p1))
    { // go from tile 35/39 to 31
        p1.player_pos = 31;
        cout << "You have fallen into a space-time rift and been teleported back to tile 31, go catch up! You are far behind!\n";
    }
    else if (p1.player_pos == 17)
    { // go from tile 17 to 13
        p1.player_pos = 13;
        cout << "You have fallen into a space-time rift and been teleported back to tile 13, go catch up! You are far behind!\n";
    }
    else if (p1.player_pos == 11)
    { // go from tile 11 to 21
        p1.player_pos = 21;
        cout << "WOW you have found a shortcut along the valley and it lead you to tile 21! You're much closer to saving the professor now!\n";
    }
    else if (p1.player_pos == 27)
    { // go back 20 seconds
        p1.time_count -= 20;
        cout << "Oh my god! You've just discovered the time accelerator developed by Atlantis, and it turned back time to 20 seconds ago!\n";
    }
}

////////////////////////////////////////////////////////////////-------------------MAIN -----------------------------------
int main()
{

// user command for game move on
    int counter = 0, dice_num, spec_dice_num, total_move;
    string line, s, temp_item;
    string response;    // user command for game move on
    game_info p1; // player class
    
    p1.time_count = 0;
    p1.player_pos = 0;

    ifstream infile;
    infile.open("player_status.txt");
    // read and ready to store the status of the player

    cout << "We checked you start the game already. "<< endl;;
    cout << "Enter:  " << endl;
    cout << "1. CON    to continue game status" << endl;
    cout << "2. ANY KEY    to open a new game save  " << endl;
    cin >> response;

    if (response == "CON")  // player choose to CONTINUE previous saved game
    {
        int a = 0;

        while (getline(infile, s))      // load previous gameinfo from playet.txt saved file/
        {
            cout << endl;
            cout << endl;

            if (a == 0)
            {
                p1.player_id = s;
            }
            else if (a == 1)
            {
                p1.player_pos = stoi(s);
            }
            else if (a == 2)
            {
                p1.player_char = s;
            }
            else if (a == 3)
            {
                p1.player_skill = s;
            }
            else if (a == 4)
            {
                p1.player_coin = stoi(s);
            }
            else if (a == 5)
            {
                p1.time_count = stoi(s);
            }
            s = "";
            a = a + 1;
        }

    }
    else      // if choose OPEN NEW SAVE
    {
        cout << "Welcome in a new save  " << endl;
        cout << "Enter your name: ";
        cin >> p1.player_id;
        p1.player_pos = 0;
        p1.player_coin = 0;

        cout << "Welcome " << p1.player_id << endl;
        cout << "Type:  " << endl;
        cout << "1. RAY" << endl;
        cout << "2. ANGUS" << endl;
        cout << "3. ANNA" << endl;
        cout << "Choose your character: ";
        
        cin >> p1.player_char;
        while (p1.player_char!= "RAY" && p1.player_char!= "ANNA" && p1.player_char!= "ANGUS")
        {
            cout << "Please enter one of the following options only. " << endl;
            cout << "   RAY   ANNA   ANGUS" << endl;
            cin >> p1.player_char;
        }
        choose_char(p1);
        cout << endl;
    }

    cout << "id : "<< p1.player_id << endl;
    cout << "Position : "<< p1.player_pos << endl;
    cout << "Char : "<< p1.player_char << endl;
    cout << "Skills : "<< p1.player_skill << endl;
    cout << "Coin : " << p1.player_coin << endl;
    cout << "Timecount : " << p1.time_count << endl;
    cout << endl;

    ofstream outfile;

    outfile.open("player_status.txt");


    cout << p1.player_id << "! You must be here for the professor. You've come just in time. The professor has been captured by the Goblin Kingdom and ";
    cout << "they've teleported into an unknown space, filled with dangerous space-time rifts and traps! I was captured along with him, but I ";
    cout << "managed to escape my cell and hide on the supply ship, but I couldn't find the professor in time. We were held at zone 40. You just ";
    cout << "have to follow the trail of tiles and it will lead you there! You've got to go save him! You'll encounter challenges along the way, ";
    cout << "but these may grant you rewards and there will be people at the shop willing to trade you coins for special items that will help you." <<endl;
    cout << "Enter any key to begin" << endl;

 
    time_t game_start_time, game_end_time, current_game_time; //start timing now
    cout << setprecision(0) << fixed; // final time set precision to 2 decimal places
    time(&game_start_time); //set game starting time
    ios_base::sync_with_stdio(false);
    //string temp_item;

    for (;;)
    {
        if (p1.player_pos == 40) // tile 40! end of game
        {
            cout << endl;

            cout << R"(
            ▄              ▄
            ▌▒█           ▄▀▒▌
            ▌▒▒█        ▄▀▒▒▒▐
        ▐▄█▒▒▀▀▀▀▄▄▄▀▒▒▒▒▒▐
        ▄▄▀▒▒▒▒▒▒▒▒▒▒▒█▒▒▄█▒▐
    ▄▀▒▒▒░░░▒▒▒░░░▒▒▒▀██▀▒▌
    ▐▒▒▒▄▄▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▀▄▒▌
    ▌░░▌█▀▒▒▒▒▒▄▀█▄▒▒▒▒▒▒▒█▒▐
    ▐░░░▒▒▒▒▒▒▒▒▌██▀▒▒░░░▒▒▒▀▄▌
    ▌░▒▒▒▒▒▒▒▒▒▒▒▒▒▒░░░░░░▒▒▒▒▌
    ▌▒▒▒▄██▄▒▒▒▒▒▒▒▒░░░░░░░░▒▒▒▐
    ▐▒▒▐▄█▄█▌▒▒▒▒▒▒▒▒▒▒░▒░▒░▒▒▒▒▌
    ▐▒▒▐▀▐▀▒▒▒▒▒▒▒▒▒▒▒▒▒░▒░▒░▒▒▐
    ▌▒▒▀▄▄▄▄▄▄▒▒▒▒▒▒▒▒░▒░▒░▒▒▒▌
    ▐▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒░▒░▒▒▄▒▒▐
    ▀▄▒▒▒▒▒▒▒▒▒▒▒▒▒░▒░▒▄▒▒▒▒▌
        ▀▄▒▒▒▒▒▒▒▒▒▒▄▄▄▀▒▒▒▒▄▀
        ▀▄▄▄▄▄▄▀▀▀▒▒▒▒▒▄▄▀
            ▀▀▀▀▀▀▀▀▀▀▀▀
            )"
                << '\n';

        cout << "You look down and notice that the trail of tiles has ended. You look into the distance and see a man tied up at the entrance of a cave. ";
        cout << "It's the professor! You walk up to him and he's rejoiced to see you. You untie him and you two escape together. Congratulations on saving the professor!" << endl;
        cout << endl;
        
        //Finish the game and finish timing now
        time(&game_end_time);// record end time
        p1.time_count = p1.time_count + double(game_end_time - game_start_time);

        int minutes;
        minutes = p1.time_count / 60;


        cout << "Total time used: "  ;
        cout << int(minutes%60) << " minutes " << (int(p1.time_count)%60) << " seconds." <<endl;


        break;


        }

        
        cout << endl;

        cout << "Enter number of one of the following actions  " << endl;
        cout << "1. ROLL    to roll your dice" << endl;
        cout << "2. POS     to check your position  " << endl;
        cout << "3. SHOP    to open the shop  " << endl;
        cout << "4. INVE    to check your inventory  " << endl;
        cout << "5. STAT    to check player status  " << endl;
        cout << "6. QUIT    to save and quit the game  " << endl;
        cout << "    (if you quit, the inventory will be cleared.)" << endl;

        cout << "Your Selection: ";

        cin >> response;
        cout << endl;

        if (response == "1") // player choose to ROLL the dice
        {
            // for each move, output a log with time specified in the log file
            while (p1.player_pos < 40)
            {
                dice_num = randint(1, 6); // can change to if conditions for character skills

                if (temp_item == "Anna_Dice")
                {
                    dice_num = dice_num*2+1;
                }
                if (temp_item == "Ray_Dice")
                {
                    dice_num = dice_num+6;
                }

                move_how_much(p1, dice_num, total_move, spec_dice_num);

                temp_item = "NULL";  // clear temp_item to refresh for next use.

                if ((40 - p1.player_pos) <= total_move)
                {
                    total_move = 40 - p1.player_pos; // if number drawn larger than the distance between the player and the destination, change the move into the distance between
                }

                p1.player_pos += total_move;
                cout << "You have moved " << total_move << " steps forward!" << endl;
                
                
                triggerevent(p1);
                break;
            }
        }

        else if (response == "2") // tell the current game POSITION of the player
        {
            cout << endl;
            cout << "You are at Position:  " << p1.player_pos << endl;
        }

        else if (response == "3") // open the SHOP for the player
        {   
            cout << endl;
            Shop(p1,player_inventory);               // call shop function.
        }

        else if (response == "4") // open player INVENTORY - for checking and using items
        {   
            string item;
            string inven_resp;
            bool use_item_return;
            
            cout << "Inventory: "; printvec(player_inventory);     // print inventory
            cout << endl;
            cout << "Would you like to use an item? It will be activated and used on the next turn. (Y or N)" << endl;
            cin >> inven_resp;
            if ( inven_resp == "Y")
            {
                cout << "item: ";
                cin >> item;

                use_item_return = use_item(item, player_inventory);
                while (item != "0"  &&  use_item_return == false)
                {  cout << "Enter 0 to exit inventory" << endl;
                    cin >> item;
                } 
                if (use_item_return == true)
                {
                    temp_item = item;
                } 
                
                cout << endl;
            }

        }
        
        else if (response == "5") // PLAYER STATUS
        {
            int min, temp;
            time(&current_game_time);
            temp = p1.time_count + double(current_game_time - game_start_time);
            min = temp/60;

            cout << "id : " << p1.player_id << endl;
            cout << "Position : " << p1.player_pos << endl;
            cout << "Char : " << p1.player_char << endl;
            cout << "Skills : " << p1.player_skill << endl;
            cout << "Coins : " << p1.player_coin << endl;
            cout << "Timecount : " << int(min%60) << " minutes " << (int(temp)%60) << " seconds." <<endl;
            cout << endl;
        }

        else if (response == "6") // QUIT the game and record current game status of the player
        {   
            // Finish the game and finish timing now
            time(&game_end_time);// record end time

            //cout << "penalty/reward: " << p1.time_count <<endl;
            //cout << "timer: " << double(game_end_time - game_start_time) <<endl;
            
            p1.time_count = p1.time_count + double(game_end_time - game_start_time) ;
            
            int minutes;
            minutes = p1.time_count / 60;
            cout << "Total time used: "  ;
            cout << int(minutes%60) << " minutes " << (int(p1.time_count)%60) << " seconds." <<endl;

            outfile << p1.player_id << endl;
            outfile << p1.player_pos << endl;
            outfile << p1.player_char << endl;
            outfile << p1.player_skill << endl;
            outfile << p1.player_coin << endl;
            outfile << p1.time_count << endl;
        
            cout << endl;
            cout << "Your progress has been saved. Bye!" << endl;
            break;
        }
    }


    outfile.close();
    infile.close();
    return 0;
}
