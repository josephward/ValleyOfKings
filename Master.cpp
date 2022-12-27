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
	bool exit = 0;
	while (exit == 0) {

		//Splash Screen
		title_art();
		vector<string> main_menu_str{
			">> Load Game\n   New Game\n   Options\n",
			"   Load Game\n>> New Game\n   Options\n"
		};
		int response = dynamic_input(main_menu_str);

		//Load Game Response
		if (response == 1) {
			
			string d_str = "Select which Save File you would like to load.";
			vector<string> str;

			string temp_str;
			//Check for valid files
			//Add each valid file option, and then add empty files
			//Ex: Save File 1\n   Empty File\n  Save File 3\n

			//Option if there is not a valid option
			if (str.size() == 0) {
				response = 2;
			}
			//Option for all the valid options
			else {
				int response2 = dynamic_input();

				//Option that returns to main menu
				if (response2 == 4) {
					//Reload the main menu function
				}
				//Option that loads the game
				else {
					clearscreen();
					load_game(response2);
					homebase();
				}
			}
			
			/*
			//Dynamically add options based on which files are avaliable
			vector<string> str;
			if (filesystem::exists("Save_File_1.txt")) {
				str.push_back("   Save File 1");
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
			*/
			
		}

		//New Game Response
		if (response == 2) {
			exit = 1;
			vector<string> str{
				">> Save File 1\n   Save File 2\n   Save File 3\n",
				"   Save File 1\n>> Save File 2\n   Save File 3\n",
				"   Save File 1\n   Save File 2\n>> Save File 3\n"
			};

			int select = dynamic_input(str);
			clearscreen();
			start_new_game(select);
		}
	}
}

//The main function for the game
void main() {
	main_menu();
	clearscreen();
	cout << "You shouldn't ever see this message.";
}