#pragma once
#include <Windows.h>
#include "GameState.h"
#include "Engine.h"

//Prototype for Areas
void start_new_game();	//Start from the top
void homebase();	//The waiting area before combat/market
void market();		//Where you can trade gold for items
void level();		//Handles everything to run the levels
void combat();		//The juicy part of the game
void win_level();	//What happens if you win a level
void lose_level();	//What happens if you lose a level

//The main function for the game, but also the function for the main menu
void main() {
	title_art();
	cout << "\n\n[1] Load Game\n[2] New Game";
	int response = verify_input(1,2);
	
	//Load Game Response
	if (response == 1) {
		cout << "\nSelect which Save File you would like to load" << 
			"\n1. Save File 1\n2. Save File 2\n3. Save File 3\n4. Exit to Main Menu";
		bool check = 0;
		int select = 0;

		//Check for valid input
		while (check == 0) {
			select = verify_input(1, 3);
			ifstream file;
			file.open(filenames[select - 1]);
			if (file) {
				check = 1;
			}
			else {
				cout << "\nInvalid input: the save file is no currently being used." <<
					" Please select another option\n";
			}
		}
		
		//Either Load the game or exit to main menu
		if (select == 4) {
			clearscreen();
			main();
		}
		else {
			load_game(select);
			clearscreen();
			homebase();
		}


	}

	//New Game Response
	else if (response == 2) {
		int select = verify_input(1,3);
		new_game(select);
		clearscreen();
		start_new_game();
	}
}