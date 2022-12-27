#pragma once
#include <filesystem>
#include "Engine.h"
using namespace std;

string FILE_NAME;

//Prototype for Areas
void start_new_game(int select);	//Start from the top
void homebase();			//The waiting area before combat/market
void market();						//Where you can trade gold for items
void level();						//Handles everything to run the levels
void combat();						//The juicy part of the game
void win_level();					//What happens if you win a level
void lose_level();					//What happens if you lose a level
void intro_flavortext();				//The Introduction to the Game
void tutorial();

void start_new_game(int select) {
	new_game(select);
	intro_flavortext();
	homebase();
}

void homebase() {

	//Read in the Game state data to see if the player has played before.
	ifstream input;
	input.open(FILE_NAME);
	int garb, GAME_STATE;
	input >> garb >> GAME_STATE;
	input.close();
	
	int status = 0;

	while (status == 0) {
		if (GAME_STATE == 1) {
			//Set up the text for the first time you enter home base.
		}
		else {

		}
	}
	
	

	return;
}

void intro_flavortext() {
	return;
}

//The function for the main menu, uses a while loop to build it
void main_menu() {
	while (exit == 0) {

		//Splash Screen
		title_art();
		cout << "[1] Load Game\n[2] New Game\n";
		int response = verify_input(1, 2);
		bool exit = 0;

		//Load Game Response
		if (response == 1) {
			cout << "\nSelect which Save File you would like to load";

			//Dynamically add options based on which files are avaliable
			string str = "";
			if (filesystem::exists("Save_File_1.txt")) {
				str += "\n[1] Save File 1";
				FILE_NAME = "Save_File_1.txt";
			}
			if (filesystem::exists("Save_File_2.txt")) {
				str += "\n[2] Save File 2";
				FILE_NAME = "Save_File_2.txt";
			}
			if (filesystem::exists("Save_File_3.txt")) {
				str += "\n[3] Save File 3";
				FILE_NAME = "Save_File_3.txt";
			}
			if (str != "") {
				str += "\n[4] Exit to Main Menu\n";
			}
			if (str == "") {
				str += "There are no valid files to choose from. A new game will be generated.\nOne moment please...";
			}

			cout << str;

			bool check = 0;
			int select = 0;

			//If there are no valid save files, start a new save file
			if (str == "There are no valid files to choose from. A new game will be generated.\nOne moment please...") {
				sleep_for(milliseconds(1000));
				clearscreen();
				goto jump;
			}

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
				//Doesn't change the exit state, meaning the function repeats
				clearscreen();
			}
			else {
				exit = 1;
				clearscreen();
				load_game(select);
				homebase();

			}

			//Start a save file 
			if (false) {
			jump:
				exit = 1;
				start_new_game(1);
			}
		}

		//New Game Response
		else if (response == 2) {
			exit = 1;
			cout << "\n[1] Save File 1\n[2] Save File 2\n[3] Save File 3\n";
			int select = verify_input(1, 3);
			clearscreen();
			start_new_game(select);
		}
	}
}

//The main function for the game
void main() {	
	string str = "This is some buffered output";
	buffered_output(str);
	
	main_menu();
	clearscreen();
	cout << "You shouldn't ever see this message.";
}