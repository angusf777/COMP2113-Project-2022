#include <iostream> 
#include <iomanip>
#include <cmath>
#include <time.h>
#include <string>
#include "functions.h"
#include <map>


using namespace std;

//to define dictionary for math game, by Angus
typedef std::map<int, string> Signs;

//print specific string for specific times, by Angus
void printsign(string str, int n) {for(int x = 0; x < n; x++ ) {cout << str; }}

//read the input, return an integer according to different conditions required by the games, by Angus
int try_stoi(string input){
    float output;
    try{output = stoi(input);}
    catch(exception &err){return -1;}
    if (output < 4 and output > 0){return 2;} //condition for user input in goat behind the door game
    else if (output < 10 and output > 0){return 3;} //condition for user input in defeat the kidnappers
    else if (output > 0){return 1;} //condition for user input in math game
    return -1;
}

//welcoming message, take in game_info p1 to print name in welcoming message, return -2 if player want to quit, return 1 if player is ready, by Angus
int welcoming(string game_name, game_info &p1){
    int refusal = 0; //when refusal reach 2 times, ask if player still want to play
    string response; //player's response
    
    // welcome the player to game 
	printsign("=", p1.player_id.length()+19); cout << endl; 
	printsign(" ", 6); cout << "Hello "<< p1.player_id << "!"; printsign(" ", 6); cout << endl;
	printsign("=", p1.player_id.length()+19); cout << "\n\n";
	cout << "Welcome to " << game_name << "!\n\n";
    
    //ask if the player is ready and let him quit if he wants to (upon several refusals)
    cout << "Are you ready? (Y or N): ";
    cin >> response;
    while (response != "Y"){
        if (refusal == 1) {
            cout << "Come on!! Do you still want to play? Y (yes) or N (no): ";
            cin >> response;
            if 
                (response == "N"){ return -2;}
            else if 
                (response == "Y"){refusal = 0;}
            else 
                refusal++;
            }
        else if (refusal > 1) {
            cout << "Please input P (play) if you'd still like to play or Q (quit) if you'd like to quit: ";
            cin >> response;
            if (response == "Q")
                {cout << "You have successfully quit the game" << endl; return -2;}
            else if 
                (response == "P"){refusal = 0;}
            else 
                refusal++;
            }
        else{
            cout << "Then get ready!!\nOnce again, are you ready? Y (yes) or N (no): ";
            cin >> response;
            refusal++;}
    }
    cout << "Great!!! Let's get started!" << endl;
    return 1; 
}

//math game, take in game_info p1 to print welcoming message, three rounds of randomly generated +/-/x problems, return the performance of the player (-1 to 2), Angus
int math_game(game_info &p1) {
    int performance = -1, A, B, answer, player_answer;
    string response; //player's response
    
    //initialise the sign to print upon generation of different random numbers
    string gamename = "Math Game";    Signs signs; signs[0]=" + "; signs[1]=" x "; signs[2]=" - "; 
    
    if (welcoming(gamename, p1) == -2) 
        {return -2;} // -2 gets passed to 'outcome = -2' in main. = quit game
    for (int i = 1; i < 4; i++){
        srand(time(0));
        int sign = rand()%3;
        if (sign == 0) { //addition while 1 is drawn
            A = rand()%4001+1000;
            B = rand()%4001+1000;
            answer = A+B;}
        if (sign == 1) { //multiplication when 2 is drawn
            A = rand()%10+11;
            B = rand()%5+11;
            answer = A*B;}
        if (sign == 2) { //subtraction when 3 is drawn
            A = rand()%4000+4001;
            B = rand()%3001+1000;
            answer = A-B;}
        cout << "\nQuestion " << i << ": " << A << signs[sign] << B << " = ";
        cin >> response; 
        
        //check if player input is valid, if not ask for another input
        while (try_stoi(response) == -1) {cout << "Please enter a positive number: "; cin >> response;}
        player_answer = int(stoi(response)); 
        
        //output results in accordince to player's answer
        if (i == 3 and player_answer != answer){cout << "Incorrect!!! Game over!" << endl;}
        else if (i == 3 and player_answer == answer){cout << "Correct!!! You have done a great job!" << endl; performance++;}
        else if (player_answer == answer){cout << "Correct!!! Well done" << endl; performance++;}
        else {cout << "Incorrect!!! Do better next time!" << endl;}
    }
    return performance;
}

//goat behind door game, the goat hide behind one of the three doors, the player make a guess each round, function takes in game_info p1 to print welcoming message, return the performance of player (-1 to 2), Angus
int doorguest_game(game_info &p1) {
    int performance = -1, answer, player_answer;
    string response; //player's response
    string gamename = "the Goat behind the Door Game";
    
    //initialise the door number to be printed upon generation of different random numbers
    Signs door; door[0]=""; door[1]="first"; door[2]="second"; door[3]="third";
    
    if (welcoming(gamename, p1) == -2)
        {return -2;} // -2 gets passed to 'outcome = -2' in main. = quit game
    cout << "In this game the goat will hide behind a different door each round\nYou will have one guess to find the goat per round, good luck!\n";
    for (int i = 1; i < 4; i++){
        srand(time(0));
        answer = rand()%3+1; //position of the goat
        cout << "\nRound " << i << "! The goat has hidden behind one of the doors already, what's your guess? (1/2/3): ";
        cin >> response; 
        
        //check if player input is valid, if not ask for another input
        while (try_stoi(response) != 2) {cout << "Please enter 1/2/3: "; cin >> response;}
        player_answer = int(stoi(response));
        
        if (player_answer != answer){cout << "Oops! The goat is actually hiding behind the " << door[answer] << " door. Better luck next time\n";}
        else if (player_answer == answer and i == 3){cout << "Well done, you are right, the goat is indeed behind door the " << door[answer] << " door. You have completed the game.\n"; performance++;}
        else if (player_answer == answer){cout << "Nice guess, you are right, the goat is indeed behind door the " << door[answer] << " door.\n"; performance++;}
    }
    return performance;
}

//Rock-Paper-Scissors Game, take in game_info p1 to print welcoming message, return the performance of the player (-1 to 2), designed by Anna
int rockpaperscissors_game(game_info &p1){
    string gamename = "Rock Paper Scisscors";
    char UserChoice;    //User's choice
    char CompChoice;    //Computer's choice
    int outcomeval = 0; //User's performance
    
    if (welcoming(gamename, p1) == -2) //welcoming 
        {return -2;} // -2 gets passed to 'outcome = -2' in main. = quit game
        
    cout << "In this game you need to beat the goblin in a classic game of Rock, Paper, Scissors. \nThere will be 3 rounds. The more you win, the better the outcome you get - good luck!\n";
    cout << "Instruction: Enter"  << endl; //instruction
    cout << "r for rock " << endl << "p for paper" << endl << "s for scissors " << endl;
    
    for (int i = 1; i <= 3; i++){
        cout<< "\nRound " << i << "! Your choice: ";
        cin >> UserChoice; //user enter choice
        while (UserChoice!='r' && UserChoice!='p' && UserChoice!='s' ){
            cout << "Please enter one of the following options only. " << endl;
            cout << "r for rock " << endl << "p for paper" << endl << "s for scissors " << endl;
            cin >> UserChoice;
        } //in case user did not answer in the right format
        
        cout << "Your choice is: ";
        if (UserChoice == 'r') cout << "Rock" << endl;
        if (UserChoice == 'p') cout << "Paper" << endl;
        if (UserChoice == 's') cout << "Scissors" << endl;
    
        cout << "The goblin's choice is: ";
        srand(time(0));
        int randnum = rand() % 3 + 1;
        if(randnum==1) CompChoice = 'r';
        if(randnum==2) CompChoice = 'p';
        if(randnum==3) CompChoice = 's';
        
        if (CompChoice == 'r') cout << "Rock" << endl;
        if (CompChoice == 'p') cout << "Paper" << endl;
        if (CompChoice == 's') cout << "Scissors" << endl;        
        
    if (UserChoice == 'r' && CompChoice == 'p') {
        cout << "The goblin won this round! Something bad may happen, good luck!"<< endl;
        outcomeval = outcomeval - 1;
    }
    else if (UserChoice == 'p' && CompChoice == 's') {
        cout << "The goblin won this round! Something bad may happen, good luck!"<< endl;
        outcomeval = outcomeval - 1;
    }
    else if (UserChoice == 's' && CompChoice == 'r') {
        cout << "The goblin won this round! Something bad may happen, good luck!"<< endl;
        outcomeval = outcomeval - 1;
    }
    else if (UserChoice == 'r' && CompChoice == 's') {
        cout << "You won this round! You are one step closer to rescuing the professor!"<< endl;
        outcomeval = outcomeval + 1;
    }
    else if (UserChoice == 'p' && CompChoice == 'r') {
        cout << "You won this round! You are one step closer to rescuing the professor!"<< endl;
        outcomeval = outcomeval + 1;
    }
    else if (UserChoice == 's' && CompChoice == 'p') {
        cout << "You won this round! You are one step closer to rescuing the professor!"<< endl;
        outcomeval = outcomeval + 1;
    }
    else cout << "A tie! Nobody wins this round – keep playing!" << endl;
    }
    if (outcomeval < -1) outcomeval = -1; //control returned value to be between -1 to 2
    else if (outcomeval > 2) outcomeval = 2;
    return outcomeval;
}

//print board for the defeat the kidnapper game, takes in the kidnapper no. and the 2d array of the board, then print it out, by Angus
void display_board(int kidnappers, char board[3][3]){
    if (kidnappers == 0){ //print original board
        string input;
        cout<<"\nPosition 1 to 9 are: \n";
        cout<<"     |     |     \n";
        cout<<"  1  |  2  |  3  \n";
        cout<<"_____|_____|_____\n";
        cout<<"     |     |     \n";
        cout<<"  4  |  5  |  6  \n";
        cout<<"_____|_____|_____\n";
        cout<<"     |     |     \n";
        cout<<"  7  |  8  |  9  \n";
        cout<<"     |     |     \n";
        cout<<"Enter any character to start the game: "; cin>>input;}
    else{ //print board with kidnappper in one of the slots 
        cout<<"\n   Kidnapper " << kidnappers << endl;
        cout<<" KIDNAPPER at X\n";
        cout<<"     |     |     \n";
        cout<<"  "<<board[0][0]<<"  |  "<<board[0][1]<<"  |  "<<board[0][2]<<"  \n";
        cout<<"_____|_____|_____\n";
        cout<<"     |     |     \n";
        cout<<"  "<<board[1][0]<<"  |  "<<board[1][1]<<"  |  "<<board[1][2]<<"  \n";
        cout<<"_____|_____|_____\n";
        cout<<"     |     |     \n";
        cout<<"  "<<board[2][0]<<"  |  "<<board[2][1]<<"  |  "<<board[2][2]<<"  \n";
        cout<<"     |     |     \n";}
}

//defeat the kidnapper game, defeat all 5 kidnappers as quick as possible, take in game_info p1 to print welcoming message, return 3 after the player pass the game, Angus
int defeatthekidnappers_game(game_info &p1) {
    int kidnappers = 1, answer, player_answer;
    string response;
    string gamename = "Defeat the Kidnappers Game";
    char board[3][3] = {{' ',' ',' '},{' ',' ',' '},{' ',' ',' '}}; //initialise board to be printed
    
    if (welcoming(gamename, p1) == -2) 
        {return -2;} // -2 gets passed to 'outcome = -2' in main. = quit game
        
    cout << "The kidnappers just showed up, defeat them before it gets too late!\nThe professor's destiny lies in your hands, don't disappoint him!\n";
    cout << "You will have to defeat all five enemies in 1v1, by shooting the position they are at, be quick!!!\n";
    display_board(0, board); //display the original board
    
    while (kidnappers != 6){
        srand(time(0));
        answer = rand()%9+1; //position of the goat
        board[(answer-1)/3][(answer-1)%3] = 'X';
        display_board(kidnappers, board);
        cin >> response; 
        
        //check if player input is valid, if not ask for another input
        while (try_stoi(response) < 2) {cout << "Please enter a number between 1-9: "; cin >> response;}
        player_answer = int(stoi(response));
        
        if (player_answer != answer){cout << "Oops! You missed your shot, try again. You must defeat all 5 kidnappers to save the professor!\n";}
        else if (player_answer == answer and kidnappers == 5){cout << "Well done, you have defeated all 5 kidnappers!\n"; kidnappers++;}
        else if (player_answer == answer){cout << "Nice shot! Keep it up!\n"; kidnappers++;}
        board[(answer-1)/3][(answer-1)%3] = ' '; //intialise the baord again after each round
    }
    return 3;
}
