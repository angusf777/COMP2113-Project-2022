//functions.h

#ifndef FUNCTIONS_H
#define FUNCTIONS_H

// #include <iostream>
// #include <iomanip>
// #include <cmath>
// #include <time.h>
#include <string>
#include "functions.h"
// #include <map>
// #include <fstream>
#include <vector>
// #include <list>
// #include <algorithm>

//using namespace std;
class game_info
{
public:
   
    std::string player_id;
    std::string player_char;
    std::string player_skill;
    int player_pos; // player positions
    int player_coin;
    // int map_choice;
    // string bonus_skill;
    // int skillcount (round countdown);
    int time_count;
};
////////////////////////////////////////////////////////////////////////////////////////////////
static std::vector<std::string> player_inventory;
static std::vector<std::string>::iterator itrv; // contains special items eg. shield


//minigames
int math_game(game_info &p1);

int doorguest_game(game_info &p1);

int rockpaperscissors_game(game_info &p1);

int defeatthekidnappers_game(game_info &p1);

//outcomes
void goodoutcome(int outcomeval, game_info &p1);

void badoutcome(int outcomeval, game_info &p1, std::vector<std::string> &player_inventory);

//shop / inventory
void Shop(game_info &p1, std::vector<std::string> &player_inventory);

int main();

bool use_item(std::string item, std::vector<std::string>& player_inventory) ;

void printvec(std::vector<std::string>player_inventory); 

#endif