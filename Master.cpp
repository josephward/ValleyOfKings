#pragma once
#include <filesystem>
#include "Engine.h"
#include "Master.h"
using namespace std;

//Global Variables
string FILE_NAME;

//Functions

void load_vars() {
	ifstream input;
	string garb;
	int trash;
	input.open(FILE_NAME);
	input >> garb >> DIFFICULTY_LEVEL >> garb >> trash
		>> garb >> LEVEL_BEATEN >> garb >> trash;
}

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
	string str;

	buffered_output("If you know you could get rich quick, would you do it?\n", 75);
	Sleep(1000);
	buffered_output("Welcome to your team of four fantastic fighters.\n");

	str	+=	string("Quintus: a veteran of the Gallic Wars, and Roman Civil War between Caesar and Pompey. Having done his tour of duty") +
			string(" he was supposed to retire to his plot of land in North Africa, but he could make himself settle down.") +
			string(" So he got a loan and started up a group of adventurers to keep the dream going.");
	
	buffered_output(str);
	str.clear();

	str +=	string("\nIcarion: an auxiliary fighter and camp follower on one of the Gallic campaigns. He left the service after Gaul and ") +
			string("returned to his homeland in Athens. To recover from the horrors of the campaign he entered into the mysteries and ") +
			string("learned powerful secrets. When Quintus came into town to visit, he could not say no to another adventure.");

	buffered_output(str);
	str.clear();
	
	str += string("\nGanna: is a druid from one of the tribes of the Belgae. With all of the upheaval from Caesar’s conquest in Gaul she ") +
		string("tried to find a better life by migrating to Rome. To find better work she joined with Quintus’s group. ") +
		string("She plans to take the gold she gets and return to Gallia Belgica to help support her people.");

	buffered_output(str);
	str.clear();
		
	str += string("\nPaltibaal: is a Carthaginian doctor following the tradition of the school of Cnidus and a long line of doctors and surgeons. ") +
		string("His family had a practice that was destroyed during the Punic Wars. Understandably, he has some beef with Romans. ") +
		string("In spite of that Quintus managed to convince him to join their group because of potential for profit.");

	buffered_output(str);
	str.clear();

	str += string("After meeting up at Alexandria in the lower Nile, the group acquired supplies and chartered a boat down the Nile with a stop in Thebes. ") +
		string("Using the map Quintus acquired they set up a base camp on the outskirts of the **Valley of Kings**.");

	Sleep(10000);
}

void market() {
	return;
}

//TODO: Continue this
void homebase(bool new_game) {

	int status = 0;

	while (status == 0) {
		if (new_game == 1) {
			//Set up the text for the first time you enter home base.
		}
		else {
			//Load in home base for people who have already played.
			vector<string> str = string_manip("   Go to Market\n   Raid Next Tomb\n   Level Select\n", "   ", ">> ");
			vector<string> vstr = { "Travel to the encampment outside Thebes to visit the markets.\nThis will take a day of travel each way.", "Begin the next avaliable level.", "Select which level to start."};
			int response = dynamic_input(str, "Please select an option.", vstr);

			//Market
			if (response == 1) {
				status = 1;
				market();
			}
			//Next Level
			else if (response == 2) {
				status = 1;
				level(LEVEL_BEATEN+1);
			}
			//Level Select
			else {
				status = 1;
				level();
			}
		}
	}
}

//Governs the execution of levels
void level(int select) {
	
	string generic_victory_text = "You have defeated all monsters!\nAs you leave you find something buried in the rubble from your fight.";
	string generic_lose_text = "You have";

	//Switch statement for each level, or if you want to replay a level
	//for none zero cases, the for loops start at the desired section and end at the last one
	switch (select) {
		//Option if user wants to replay a level
		case 0: {
			//string str;
			//for(int i = 0; i < LEVEL_BEATEN; i++) {...
			//str += "   Level " + i;
			//str_manpi(str, "   ", ">> ");
			//dynamic_input(str);
		}
		//Level 1
		case 1: {
			//Run through all of the combat
			for (int i = 3; i <= 4; i++) {
				bool exit = combat(i);
				
				//If combat ends, then end the loop 
				if (exit == 1) {
					i = 5;
				}
			}



			//

			//End of level flavor text
		}
		//Level 2
		case 2: {
			for (int i = 5; i <= 7; i++) {
				bool exit = combat(i);
				if (exit == 1) {
					i = 8;
				}
			}
			//End of level flavor text
		}
		//Level 3 - Boss 1
		case 3: {
			for (int i = 8; i <= 10; i++) {
				bool exit = combat(i);
				if (exit == 1) {
					i = 11;
				}
			}
			//End of level flavor text
		}
	}
}

//Function imported from version 1.0
bool monster_turn(vector<shared_ptr<Being>> monst_turn_order) {
	clearscreen();

	//If the monster goes below 0 hitpoints delete from vector and pass the turn
		//Then end skip the monster

	for (int i = 0; i < monst_turn_order.size(); i++) {
		if (monst_turn_order[i]->get_HP() < 1) {
			monst_turn_order.erase(monst_turn_order.begin() + i);
			i -= 1;
		}
	}

	//If all the monsters are dead, end the function.
	if (monst_turn_order.size() == 0) {
		return 0;
	}

	std::cout << "The Monsters attack!" << endl << endl;
	//this_thread::sleep_for(milliseconds(2500)); //Adds a time delay

	//For each monster select a valid target then conduct an attack
	for (int i = 0; i < monst_turn_order.size(); i++) {
		//Set up variables
		shared_ptr<Being> current_monst = monst_turn_order[i];
		int attack_select = rand() % 5;						//Choose a random attack
		int char_select = rand() % characterVect.size();	//Choose a random cast member as a target
		int temp_target = char_select;
		int x = 0;

		//Search through the cast list and find a valid target
		//Used rand instead of just going to next cast member so that chance to hit stays the same for all characters
		bool valid_target = 0;
		while (valid_target == 0) {
			//If the current character has HP > 0 choose them
			if (characterVect[char_select]->get_HP() != 0) {
				temp_target = char_select;
				valid_target = 1;
			}
			//Else choose a random other character
			//Choose random characters 30 times, if they still cannot find a match then just pass
			else {
				char_select = rand() % 4;
				//There is a 0.018% chance that this loop will not find a match
				if (x > 30) {
					return 1;
				}
			}
			x++;
		}

		//Run through the cast list and find the one with the lowest HP
		//If all characters are equal, defaults to the first nonQuintus character
		int temp_weak_target = 0;
		for (int j = 1; j < characterVect.size(); j++) {
			//If the jth indice has a smaller value, replace the weak_target
			if (characterVect[temp_weak_target]->get_HP() < characterVect[j]->get_HP() && characterVect[j]->get_HP() > 0) {
				temp_weak_target = j;
			}
		}

		//Set up pointers for the target character and the weakest character
		shared_ptr<Being> target_Ptr = characterVect[temp_target];
		shared_ptr<Being> weak_target_Ptr = characterVect[temp_weak_target];

		//If the monster is stunned, unstun them and pass the turn
		if (current_monst->is_stunned == 1) {
			std::cout << current_monst->get_name() << " is stunned!" << endl;
			monst_turn_order[i]->unstun();
		}

		//If the monster is not stunned, choose an attack option
		//This section governs the 'Monster AI'
		//Currect setup gives a roughly 40% chance to hit the weakest character and 20% to all other characters
		else if (current_monst->get_HP() != 0 && current_monst->is_stunned == 0) {

			if (attack_select == 0) { // Light random attack
				current_monst->std_attack(target_Ptr, 0);
			}
			else if (attack_select == 1) { // Light random attack
				current_monst->std_attack(target_Ptr, 0);
			}
			else if (attack_select == 2) { // Heavy random attack
				current_monst->std_attack(target_Ptr, 2);
			}
			else if (attack_select == 3) { // Light target weakest attack
				current_monst->std_attack(weak_target_Ptr, 0);
			}
			else if (attack_select == 4) { // Random stun attack
				target_Ptr->stun();
			}
			std::cout << endl;
		}
		this_thread::sleep_for(milliseconds(2000)); //Adds a time delay
	}
}

bool character_turn() {
	return 0;
}

bool combat(int select) {
	//Set up combat
	vector<shared_ptr<Being>> monst_turn_order = {};
	setupMonsterCombat(monst_turn_order, select);
	genCast(upgradeMatrix);

	//Variables
	bool exit = 1;
	bool monst_status = 1;
	bool char_status = 1;

	//Loop turns until one side dies
	while (exit != 0) {
		
		
		//If the monster/character turns exit with no one dead they will return 1. 
		//If either party completely dies then it will return 0 and trigger the exit
		clearscreen();
		monst_status = monster_turn(monst_turn_order);
		clearscreen();
		print_vect(characterVect);
		Sleep(1000);
		char_status = character_turn();
		exit = monst_status * char_status; //Exit == 0 completes combat
	}

	//If all the monsters died
	if (monst_status == 0) {
		//Flavor text
		return 0;
	}
	//If all the characters died
	else {
		//Flavor text
		return 1;
	}
}

//Overloaded version of the combat function
//TODO: make sure that they are the same function
bool combat(vector<shared_ptr<Being>> monst_turn_order) {
	
	genCast(upgradeMatrix);

	//Variables
	bool exit = 1;
	bool monst_status = 1;
	bool char_status = 1;

	//Loop turns until one side dies
	while (exit != 0) {
		//If the monster/character turns exit with no one dead they will return 1. 
		//If either party completely dies then it will return 0 and trigger the exit
		clearscreen();
		monst_status = monster_turn(monst_turn_order);
		clearscreen();
		print_vect(characterVect);
		Sleep(1000);
		char_status = character_turn();
		exit = monst_status * char_status; //Exit == 0 completes combat
	}

	//If all the monsters died
	if (monst_status == 0) {
		//Flavor text
		return 0;
	}
	//If all the characters died
	else {
		//Flavor text
		return 1;
	}
}

//The function for the main menu, will run continuously until user wants to exit program
void main_menu() {	
	while (true) {
		//Splash Screen
		//TODO: Replace with string_manip once there are some options to work with
		vector<string> main_menu_str{
			"=======================================================\n>> Load Game\n   New Game\n   Skirmish\n   Options [Under Construction]\n   Close Program\n=======================================================",
			"=======================================================\n   Load Game\n>> New Game\n   Skirmish\n   Options [Under Construction]\n   Close Program\n=======================================================",
			"=======================================================\n   Load Game\n   New Game\n>> Skirmish\n   Options [Under Construction]\n   Close Program\n=======================================================",
			"=======================================================\n   Load Game\n   New Game\n   Skirmish\n   Options [Under Construction]\n>> Close Program\n======================================================="
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
				if (response2 != 3) {
					FILE_NAME = filenames[response2]; //Sets the active file name
					load_vars();
					load_save_file(response2);

				}
				//Option that reloads the main menu function
				else {
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
			if (select != 3) {
				FILE_NAME = filenames[select]; //Sets the active file name
				load_vars();
				start_new_game(select);
			}
			//If the response is to cancel redo main menu function
			else {
			}
		}

		//Skirmish Response
		if (response == 2) {
			
			vector<shared_ptr<Being>> skirm_vect = {};
			int x = 0;

			//Vector of options to select from
			vector<vector<int>> options{
				{3, 3},		//Easy
				{3, 4},		//Medium
				{3, 3, 4}	//Hard
			};
			

			//Select a cast set of monsters
			string difficulty_options = "   Easy\n   Medium\n   Hard\n";
			clearscreen();
			vector<string> dyn_input = string_manip(difficulty_options, "   ", ">> ");
			int input = dynamic_input(dyn_input, "Select the difficulty level of monsters.\n");
			
			bool victory = 0;

			//Conduct combat
			for (int x = 0; x < options.size(); x++) {
				setupMonsterCombat(skirm_vect, options[input][x]);
				victory = combat(skirm_vect);

				//If the user loses during the round
				if (victory == 0) {
					cout << "You have lost and your soldiers will join the ranks of the undead. Good luck next time!" << endl;
					Sleep(1000);
					clearscreen();
					break;
				}
			}

			// Endstate if user lost
			if (victory == 0) {
				cout << "You have lost and your soldiers will join the ranks of the undead. Good luck next time!" << endl;
				Sleep(1000);
				clearscreen();
			}
			//Endstate if user won
			else if (victory == 1) {
				cout << "You have beaten the tomb and carried off the riches hidden within." << endl;
				Sleep(1000);
				clearscreen();
			}

			//No end catch, meaning that it returns to main menu
		}

		//TODO: Insert the options section 'function'. Make sure to change the main_menu_str and the next response to == 3.


		//If response is to close program, end the loop, which will close the program
		if (response == 3) {
			clearscreen();
			return;
		}
	}
}

//The main function for the game
int main() {
	main_menu();
}