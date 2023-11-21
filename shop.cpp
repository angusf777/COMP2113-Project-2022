#include <iomanip>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include "functions.h"

using namespace std;

////////////////////////////////////////////////////////////////////////////////////////////////
char Y_or_0;
bool selection_confirmation()              // ---- func ------ TO CONFIRM PURCHASE DECISION OF THE SELECTED ITEM -------- 
{   
    cout << "Enter Y to confirm purchase. Enter 0 to return to the shop menu." << endl;  // asks player to confirm selection or return to menu,
    cin >> Y_or_0;                                                                       // input 
    while (! (Y_or_0 == 'Y' || Y_or_0 == 'y' || Y_or_0 == '0'))     // if the entered keys are not one of the commands
    {
        cin >> Y_or_0;                                              // loop till they enter a command key
    }
    if (Y_or_0 == '0')                                                  // if they dont confirm, quit purchase
        return false;                                                       // func returns false.
    return true;                                                        // confirmed purchase, func returns true.
}
////////////////////////////////////////////////////////////////////////////////////////////////
                                            
                                            // ---- func ------ TO CONFIRM WHETHER SUFFICIENT COINS TO BUY ITEM -------- 
void funds_confirmation(game_info &p1, int item_price, string &item, vector<string> &player_inventory)  
            // INPUTS:(player info, price of item to purchAse, item name, inventory vector )

{   
    if (p1.player_coin < item_price)                                                  // if not enough coins, function informs player. no action taken.
    {
        cout << "Purchase Unsuccessful. Insufficient coins. You will now be returned to the shop menu" << endl;
        //return true;        
    }
    else
    {
        p1.player_coin -= item_price;                                                  // if sufficient coins – purchase goes through. coins deducted.
        player_inventory.push_back(item);   
        //p1.player_inventory.push_back("item");                                                   // append item to inventory vector

        cout << "Purchase Successful!   Remaining Coins: " << p1.player_coin << endl;
        cout << "Remaining Inventory:"; printvec(player_inventory);                                    // print new inventory w printvec()
        cout << "You will now be returned to the shop menu." << endl;
        //return false;
    }
}
////////////////////////////////////////////////////////////////////////////////////////////////

void Shop(game_info &p1, vector<string> &player_inventory)                        // --- MAIN SHOP FUNCTION ---- prints shop menu for player to choose what to buy. (no inputs)
                                                                                   // calls relevant helper functions to confirm purchases
{                                                                                   
    int selection; char Y_or_0;
    string item;
    
    while (selection != 0)
    {   

        cout << endl << "Welcome to the Shop!" << setw(30) << "Available Coins: " << p1.player_coin << endl;
        cout << "Please enter the number of the item you'd like to purchase or learn more about." << endl << endl;      // --- shop menu print ---
        cout <<     
        "      Item             Price"  << endl <<                                          
        "1. Anna Dice          5 Coins" << endl << 
        "2. Ray Dice           7 Coins" << endl << 
        "3. Shield             4 Coins" << endl << endl <<
        "0. Return to Map" << endl;

        cout << endl << "Your Selection: "; cin >> selection;  
        while ( ! (selection >= 0 && selection < 4 ))                       // while selection out of bounds - loop till selection in bounds.
        {
            cout << "Selection not found - please ensure the entered selection is or between 0 and 3." << endl;
            cout << "Your Selection: "; 
            cin >> selection; 
        }

        if (selection != 0 || Y_or_0 != '0')                                // if selection is in bounds:
        {
            if (selection == 1) // SPECIAL DICE                                               // information of selection is printed
            {   
                item = "Anna_Dice";                                                        // declare name of item
                cout << "Item selected: Anna Dice       Price: 5 coins" << endl;
                cout << "Description: Roll outcome = (Roll outcome x2) -1"  << endl; 
                
                if (selection_confirmation())                              // function to confirm choice of item. if not confirmed func prints a statement.
                {
                //below func passes:(playerinfo, price, item, inventory);         // if choice confirm, call func to check if have sufficient coins,
                    funds_confirmation( p1, 5, item, player_inventory);                   // purchase goes through and item is added to inventory
                }
            }
            if (selection == 2) // DOUBLE ROLL                             // same as selection 1's mechanics
            {
                item = "Ray_Dice";
                cout << "Item selected: Ray Dice       Price: 7 coins" << endl;
                cout << "Description: Roll outcome = Roll outcome +6" << endl;
                if (selection_confirmation())
                {
                    funds_confirmation( p1, 7 ,item, player_inventory);
                }
            }
            if (selection == 3) // SHIELD                                  // same as selection 1's mechanics
            {
                item = "Shield";
                cout << "Item selected: Shield        Price: 4 coins" << endl;
                cout << "Description: A single use shield that provides immunity against losses." << endl;
                
                if (selection_confirmation())
                {
                    funds_confirmation( p1, 4 ,item,player_inventory);
                }
            }
        }
    }
}
////////////////////////////////////////////////////////////////////////////////////////////////
//                                                            ---------USE ITEM --------

bool use_item(string item, vector<string>&player_inventory)                 // takes item name and inventory.
{   int* used = new int(0);                           // alloc mem. Counter variable to check whether inventory to contains item
   
    for (int i = 0; i<player_inventory.size(); i++)
    {
        if (player_inventory[i] == item)                                    // if item is in inventory,
        {   *used =1;                                                                  // counter variable is not 0
            player_inventory.erase(player_inventory.begin( ) + i);          // item is "used" and hence erased from inventory.
            
            cout << "Remaining inventory: "; printvec(player_inventory);        // print remaining inventory
            break;                                                              // so not more than 1 of the item is used.
        }
    }   
    if (*used != 0) // item used
    {
        //cout << "if (*used != 0) condition entered" << endl; /////
        cout << item << " activated!" << endl; 
        return true; 
    }
    
    else            // no item used
    {
        cout << "You don't have usable items!" << endl;                     // if variable used = 0, no item was used.
        return false;
    }
    delete used;                                                             // delete variable to free up memory
}

/*
int main()      
{
    cout << "hi";
    class game_info p2;
    p2.player_coin = 15;
    Shop(p2);
}
 */
