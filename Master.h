#pragma once

//Global Variables
extern string FILE_NAME;

void load_vars();
void start_new_game(int select);	//Start from the top
void load_save_file(int select);	//Continue previous game
void intro_flavortext();			//The Introduction to the Game
void tutorial();					//Tutorial for the game
void homebase(bool new_game);		//The waiting area before combat/market
void market();						//Where you can trade gold for items
void level(int select = 0);			//Handles everything to run the levels
bool combat(int select);			//The juicy part of the game
void check_combat();
bool monster_turn();
bool character_turn();
void win_level();					//What happens if you win a level
void lose_level();					//What happens if you lose a level