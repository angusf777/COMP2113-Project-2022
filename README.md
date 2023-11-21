COMP2113_ENGG1340 Programming technologies and Computer programming II [Section 1A] [2022]
Group 45 Read Me File:

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

▪ Identification of the team members.

Fong Natalie Hau Yue 3035663277
Fung Angus 3035926966
Tam Yung Yip 3035571876
Hu Anna 3035731660

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

▪ A description of your game and introduce the game rules.

The game is Save the Professor, where the professor has been kidnapped by the Goblin Kingdom, and the goal of the game is to traverse the kingdom to find the professor and escape with him. 

The structure is as follows:
1. The map is constructed of 40 tiles, and the professor is confined by kidnappers at the 40th block in this mysterious world. The player can serve as one of the three characters, and march towards our dearest professor to save him
2. As the game begins, the player can either start a new game or reload the progress of an unended game to continue where they left off.
3. The number of tiles moved is dictated by a dice roll at the start of every round (1 to 4)
4. Every round, the player can choose to roll dice, check their position, buy special items from the shop (to help advance in game play), check their inventory, check their status (eg. character, inventory, coins), or save their progress and quit.
5. Each tile has a different event such as minigames, picking up coins, being teleported to a different tile etc. Details may refer to https://connecthkuhk-my.sharepoint.com/:x:/g/personal/angusf77_connect_hku_hk/EQl2JrVDWMZPpEGj5Jdky2kBFF1vkJL6kjUBrde5Mwqc0A?e=iXDDiw
6. Once the 40th tile is reached, the game ends.
7. The performance of the player is accessed through a time count to see how long it takes the player to reach the 40th tile and hence the professor.

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

▪ List of features that you've implemented, and explain how coding elements 1 to 5 under the coding requirements aforementioned support your features.

----------------------------------------------------------------------------------------------------
• Generation of random game sets or events: 
- The game uses a random number for the dice roll in every round.
- The game uses a random number to select a minigame when the player lands on a minigame tile. 
- The game uses a random number to determine how many tiles the player moves (forwards/backwards) when they land on such tiles.
- The minigames also use random numbers to generate random outcomes for the player. For example, the goat game uses random numbers to determine which door the goat is hiding behind; the rock paper scissor game uses random numbers to determine the goblin’s choice on rock, paper or scissor. 
----------------------------------------------------------------------------------------------------
• Data structures for storing game status 
- The game used “struct game_info” to store the player's ID(name), character selected, skills, position on the map, coins, and inventory(which contains items). The “struct game_info” is used in many aspects of the game, and facilitated great efficiency while calling functions in a function. 
----------------------------------------------------------------------------------------------------
• Dynamic memory management 
- The game made use of STL vectors in player_inventory, which allows the player to buy the items from the shop and use the items while playing. For example, the player could buy a shield in the shop, the shield will be automatically used when the player encounters bad outcomes. 
- The game made use of new and delete pointers in use_item() from inventory to inform whether an item has been used. For example, when the inventory includes a shield, the use_item() will return true and the item will be used to waive the bad outcomes.
----------------------------------------------------------------------------------------------------
• File input/output (e.g., for loading/saving game status) 
- Use of playerstatus.txt I/O in main cpp. 
playerstatus.txt holds the player data (eg. player character choice, run time of the game, the coins that the player has) are saved in a file when the player chooses the save and quit the game before finishing it. The player may choose to reload the progress of before (which takes input from playerstatus.txt) or start a new game .
----------------------------------------------------------------------------------------------------
• Program codes in multiple files 
- There are codes in multiple files, including main.cpp (main), shop.cpp (holds shop function and relevant helper functions), goodbadoutcomes.cpp (holds outcome functions), minigames.cpp (holds the codes of the minigames), and functions.h.

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

▪ A list of non-standard C/C++ libraries, if any, that are used in your work and integrated to your code repo. Please also indicate what features in your game are supported by these libraries. 
- Not applicable.

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

▪ Compilation and execution instructions. This serves like a "Quick start" of your game. The teaching team will follow your instructions to compile and run your game. 

1. As a makefile is made, simply enter “make main” and then “./main” then the game starts.
2. Enter any key to start a new game, type CON unless you have previous record on the game.
3. Enter your name.
4. Pick a character out of 3 available choices (“RAY”, “ANGUS”, “ANNA”), then the skills available for the character will be shown.
5. The game has started and you will fall into a loop of choosing 6 actions every round, you could enter number 1 to 6 for their respective functions. Random events will be generated after you roll your dice(s). 
6. Follow the instructions given in each round to navigate gameplay
7. The game will end when you reach the 40th tile (40 steps from the beginning).
