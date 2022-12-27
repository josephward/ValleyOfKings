#pragma once
#include <filesystem>
#include "Engine.h"
using namespace std;

string FILE_NAME;

//Prototype for Areas
void start_new_game(int select);	//Start from the top
void load_save_file(int select);	//Continue previous game
void homebase(bool new_game);			//The waiting area before combat/market
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
	homebase(1); //Once the homebase loop is broken, the game will return to main menu
}

void load_save_file(int select) {
	load_game(select);
	homebase(0); //Once the homebase loop is broken, the game will return to main menu
}

void intro_flavortext() {
	buffered_output("");
	return;
}

void homebase(bool new_game) {

	int status = 0;

	while (status == 0) {
		if (new_game == 1) {
			//Set up the text for the first time you enter home base.
		}
		else {
			//Load in home base for people who have already played.
		}
	}
}

//The function for the main menu, will run continuously until user wants to exit program
void main_menu() {
	while (true) {
		//Splash Screen
		//TODO: Replace with string_manip once there are some options to work with
		vector<string> main_menu_str{
			"=======================================================\n>> Load Game\n   New Game\n   Options [Under Construction]\n   Close Program\n=======================================================",
			"=======================================================\n   Load Game\n>> New Game\n   Options [Under Construction]\n   Close Program\n=======================================================",
			"=======================================================\n   Load Game\n   New Game\n   Options [Under Construction]\n>> Close Program\n======================================================="
		};
		int response = dynamic_input(main_menu_str, title_art());
		
		//Load Game Response
		if (response == 0) {
			
			//Useful variables
			string d_str = "Select which Save File you would like to load.\nTo start a new save file select cancel and then select new file.";
			string temp_str;	//Temp string to build vector

			//Check for valid files, and build string
			//TODO: Add percent of game complete to the each save file that built
			// Example: Save File 1 has 10 out of 20 levels complete, so Save File 1 - 50%
			if (filesystem::exists("Save_File_1.txt") || filesystem::exists("Save_File_2.txt") || filesystem::exists("Save_File_3.txt")) {
				
				if (filesystem::exists("Save_File_1.txt")) {
					temp_str += "   Save File 1\n";
				}
				else {
					temp_str += "   Empty File\n";
				}

				if (filesystem::exists("Save_File_2.txt")) {
					temp_str += "   Save File 2\n";
				}
				else {
					temp_str += "   Empty File\n";
				}

				if (filesystem::exists("Save_File_3.txt")) {
					temp_str += "   Save File 3\n";
				}
				else {
					temp_str += "   Empty File\n";
				}

				temp_str += "   Cancel\n";
			}

			//Iterate through the new string, and build the vector of strings, only valid options are those with files already built
			vector<string> str = string_manip(temp_str, "   S", ">> S");
			clearscreen();

			//Asks for and loads the chosen save file
			if (temp_str.size() != 0) {
				int response2 = dynamic_input(str, d_str);
				clearscreen();

				//Option that loads the game
				if (response2 != 4) {
					FILE_NAME = filenames[response2]; //Sets the active file name
					load_save_file(response2);

				}
				//Option that reloads the main menu function
				else {
					break;
				}
				
			}

			//Option if there are no active save files
			else {
				cout << "There are no valid save files to load. You are being redirected to create a new save file.\n";
				sleep_for(2000ms);
				cout << "Please wait while it loads...";
				sleep_for(2000ms);
				response = 1;
			}			
		}

		//New Game Response
		//TODO: create a catch for if a file is already built
		if (response == 1) {
			clearscreen();
			string str = "   File 1\n   File 2\n   File 3\n   Cancel\n";
			string to_change = "   ";
			string change_to = ">> ";
			string d_str = "Select a save file you would like to create a new game in.";

			vector<string> str_vect = string_manip(str, to_change, change_to);

			int select = dynamic_input(str_vect,d_str);
			clearscreen(); //After getting input clear the screen to execute input

			//If the response is to create a game do so
			if (select != 4) {
				FILE_NAME = filenames[select]; //Sets the active file name
				start_new_game(select);
			}
			//If the response is to cancel redo main menu function
			else {
				break;
			}
			
		}

		//TODO: Insert the options section 'function'. Make sure to change the main_menu_str and the next response to == 3.

		//If response is to close program, end the loop, which will close the program
		if (response == 2) {
			clearscreen();
			return;
		}
	}
}

//The main function for the game
int main() {
	main_menu();
}