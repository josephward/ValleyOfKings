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
				bool exit = combat(i, characterVect);
				
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
				bool exit = combat(i, characterVect);
				if (exit == 1) {
					i = 8;
				}
			}
			//End of level flavor text
		}
			  //Level 3 - Boss 1
		case 3: {
			for (int i = 8; i <= 10; i++) {
				bool exit = combat(i, characterVect);
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

	//Clear monster vector function and check if combat should be over
	for (int i = 0; i < monst_turn_order.size(); i++) {
		if (monst_turn_order[i]->get_HP() < 1) {
			monst_turn_order.erase(monst_turn_order.begin() + i);
			i -= 1;
		}
	}
	if (monst_turn_order.size() == 0) {
		return 0;
	}

	std::cout << "The Monsters attack!" << endl << endl;
	Sleep(1000);
	//this_thread::sleep_for(milliseconds(2500)); //Adds a time delay

	//For each monster select a valid target then conduct an attack
	for (int i = 0; i < monst_turn_order.size(); i++) {

		//Status Checks (addition check like mind control can

		//If all the characters are dead then return the function
		int x = 0;
		for (int i = 0; i < characterVect.size(); i++) {
			if (characterVect[i]->get_HP() <= 0) {
				x++;
			}
			if (x == 4) {
				return 1;
			}
		}

		//If the monster is stunned, unstun them and pass the turn
		shared_ptr<Being> current_monst = monst_turn_order[i];
		if (current_monst->is_stunned == 1) {
			monst_turn_order[i]->unstun();
		}

		//Conduct the targeting and attack
		else {

			//Choose targets

			//Create a vector of all characters that are concious
			vector<shared_ptr<Being>> temp_char_vect;
			for (int j = 0; j < characterVect.size(); j++) {
				if (characterVect[j]->get_HP() > 0) {
					temp_char_vect.push_back(characterVect[j]);
				}
			}

			//Select a random target
			int temp_target = rand() % temp_char_vect.size();

			//Select the weakest target (defaults to first weakest)
			int temp_weak_target = 0;
			for (int k = 0; k < temp_char_vect.size(); k++) {
				if (temp_char_vect[temp_weak_target]->get_HP() < temp_char_vect[k]->get_HP()) {
					temp_weak_target = k;
				}
			}

			//Other future addtions could be:
			// - random unstunned 
			// - strongest

			//Set target pointers
			shared_ptr<Being> target_Ptr = temp_char_vect[temp_target];
			shared_ptr<Being> weak_target_Ptr = temp_char_vect[temp_weak_target];

			//Conduct the combat
			shared_ptr<Monster>temp_monst;
			temp_monst->masterMonsterAI(current_monst, target_Ptr, weak_target_Ptr);
		}
		cout << endl;
		Sleep(2000); //Adds a time delay
	}

	return 1; //If nothing else trips, return
}

string gen_select(vector<string> options) {
	string new_option;
	for (int i = 0; i < options.size(); i++) {
		string temp = "   ";
		temp.append(options[i]);
		temp.append("\n");
		new_option.append(temp);
	}
	return new_option;
}

string gen_select(vector<shared_ptr<Being>> options) {
	string new_option;
	for (int i = 0; i < options.size(); i++) {
		string temp = "   ";
		temp.append(options[i]->get_name());
		temp.append("  ");
		temp.append(to_string(options[i]->get_HP()));
		temp.append("\n");
		new_option.append(temp);
	}
	return new_option;
}

bool character_turn(vector<shared_ptr<Being>> monst_turn_order) {
	Sleep(1000);
	
	//If all the characters are dead then return the function
	int x = 0;
	for (int i = 0; i < characterVect.size(); i++) {
		if (characterVect[i]->get_HP() <= 0) {
			x++;
		}
		if (x == 4) {
			return 0;
		}
	}

	//Combat loop 
	for (int p = 0; p < characterVect.size(); p++) {
		clearscreen();
				
		//Clear monster vector function and check if combat should be over
		for (int i = 0; i < monst_turn_order.size(); i++) {
			if (monst_turn_order[i]->get_HP() < 1) {
				monst_turn_order.erase(monst_turn_order.begin() + i);
				i -= 1;
			}
		}
		if (monst_turn_order.size() == 0) {
			return 1;
		}

		//Output battle information
		print_vect(monst_turn_order);
		print_vect(characterVect);

		//Choose target and execute attack
		shared_ptr<Being> current_char = characterVect[p];
		
		//If the char is stunned, then unstun them and break
		if (characterVect[p]->is_stunned) {
			characterVect[p]->unstun();
		}
		//If the char has less than or equal to 0, pass the turn
		else if (characterVect[p]->get_HP() <= 0) {
			cout << characterVect[p]->get_name() << " is unconcious!" << endl;
		}
		else if (characterVect[p]->get_name() == "Quintus") {
			string standard = "Quintus' turn:\nUse the up/down keys to select an option, then hit enter.";

			//Set up vectors
			vector<string> options = { "Attack", "Shield Bash" };
			vector<string> explain = { 
				"Cause a monster to take 6 damage.\n", 
				"Cause a monster to be stunned for one turn.\n" };
			
			//Check the upgrade matrix
			if (upgradeMatrix[0][0] == 1) {
				options.push_back("Upgrade 1");
				explain.push_back("This is an example upgrade");
			}

			//Selects which attack option
			string temp_options = gen_select(options);
			options = string_manip(temp_options, "   ", ">> ");
			//Ask for input
			int response = dynamic_input(options, standard, explain);
			clearscreen();

			//Selects which monster to target
			string temp_options2 = gen_select(monst_turn_order);
			vector<string> options2 = string_manip(temp_options2, "   ", ">> ");
			//Ask for input
			int response2 = dynamic_input(options2, standard);

			//Execute input
			if (response == 0) {
				cout << current_char->get_name() << " attacks " << monst_turn_order[response2]->get_name() << "!\n";
				current_char->std_attack(monst_turn_order[response2]);
			}
			else if (response == 1) {
				cout << current_char->get_name() << " stuns " << monst_turn_order[response2]->get_name() << "!\n";
				monst_turn_order[response2]->stun();
			}
			else if (response == 2) {
				cout << "Error: This upgrade has not been initialized." << endl;
			}
		}
		else if (characterVect[p]->get_name() == "Nysa") {
			string standard = "Nysa's turn:\nUse the up/down keys to select an option, then hit enter.";

			//Set up vectors
			vector<string> options = { "Attack", "Jupiter's Lightning" };
			vector<string> explain = {
				"Cause a monster to take 4 damage.\n",
				"Cause each monster to take 2 damage\n" };

			//Check the upgrade matrix
			if (upgradeMatrix[1][0] == 1) {
				options.push_back("Upgrade 1");
				explain.push_back("This is an example upgrade");
			}

			//Selects which attack option
			string temp_options = gen_select(options);
			options = string_manip(temp_options, "   ", ">> ");
			//Ask for input
			int response = dynamic_input(options, standard, explain);
			clearscreen();

			//Selects which monster to target
			int response2;
			if (response != 1) {
				string temp_options2 = gen_select(monst_turn_order);
				vector<string> options2 = string_manip(temp_options2, "   ", ">> ");
				//Ask for input
				response2 = dynamic_input(options2, standard);
			}

			//Execute input
			if (response == 0) {
				cout << current_char->get_name() << " attacks " << monst_turn_order[response2]->get_name() << "!\n";
				current_char->std_attack(monst_turn_order[response2]);
			}
			else if (response == 1) {
				for (int i = 0; i < monst_turn_order.size(); i++) {
					cout << current_char->get_name() << " attacks " << monst_turn_order[i]->get_name() << "!\n";
					current_char->std_attack(monst_turn_order[i], 0, .5);
					cout << endl;
				}
			}
			else if (response == 2) {
				cout << "Error: This upgrade has not been initialized." << endl;
			}
		}
		else if (characterVect[p]->get_name() == "Paltibaal") {
			string standard = "Paltibaal's turn:\nUse the up/down keys to select an option, then hit enter.";

			//Set up vectors
			vector<string> options = { "Attack", "Heal" };
			vector<string> explain = {
				"Cause a monster to take 4 damage.\n",
				"Cause a character to be healed for 4 damage.\n" };

			//Check the upgrade matrix
			if (upgradeMatrix[2][0] == 1) {
				options.push_back("Upgrade 1");
				explain.push_back("This is an example upgrade");
			}

			//Selects which attack option
			string temp_options = gen_select(options);
			options = string_manip(temp_options, "   ", ">> ");
			//Ask for input
			int response = dynamic_input(options, standard, explain);
			clearscreen();


			int response2 = 0;
			if (response != 1) {
				//Selects which monster to target
				string temp_options2 = gen_select(monst_turn_order);
				vector<string> options2 = string_manip(temp_options2, "   ", ">> ");
				//Ask for input
				response2 = dynamic_input(options2, standard);
			}
			else {
				//Selects which monster to target
				string temp_options2 = gen_select(characterVect);
				vector<string> options2 = string_manip(temp_options2, "   ", ">> ");
				//Ask for input
				response2 = dynamic_input(options2, standard);
			}

				

			//Execute input
			if (response == 0) {
				cout << current_char->get_name() << " attacks " << monst_turn_order[response2]->get_name() << "!\n";
				current_char->std_attack(monst_turn_order[response2]);
			}
			else if (response == 1) {
				cout << characterVect[p]->get_name() << " heals " << characterVect[response2]->get_name() << "!\n";
				characterVect[p]->std_heal(characterVect[response2]); //Current char heals chosen char.
			}
			else if (response == 2) {
				cout << "Error: This upgrade has not been initialized." << endl;
			}
		}
		else if (characterVect[p]->get_name() == "Ganna") {
			string standard = "Ganna's turn:\nUse the up/down keys to select an option, then hit enter.";

			//Set up vectors
			vector<string> options = { "Attack", "Old Magic" };
			vector<string> explain = {
				"Cause a monster to take 4 damage.\n",
				"Cause a monster to take 8 damage and stun Ganna for a turn.\n" };

			//Check the upgrade matrix
			if (upgradeMatrix[3][0] == 1) {
				options.push_back("Upgrade 1");
				explain.push_back("This is an example upgrade");
			}

			//Selects which attack option
			string temp_options = gen_select(options);
			options = string_manip(temp_options, "   ", ">> ");
			//Ask for input
			int response = dynamic_input(options, standard, explain);
			clearscreen();

			//Selects which monster to target
			string temp_options2 = gen_select(monst_turn_order);
			vector<string> options2 = string_manip(temp_options2, "   ", ">> ");
			//Ask for input
			int response2 = dynamic_input(options2, standard);

			//Execute input
			if (response == 0) {
				cout << current_char->get_name() << " attacks " << monst_turn_order[response2]->get_name() << "!\n";
				current_char->std_attack(monst_turn_order[response2]);
			}
			else if (response == 1) {
				cout << current_char->get_name() << " curses " << monst_turn_order[response2]->get_name() << "!\n";
				current_char->std_attack(monst_turn_order[response2], 0, 2);
				characterVect[p]->stun();
			}
			else if (response == 2) {
				cout << "Error: This upgrade has not been initialized." << endl;
			}
		}
		Sleep(2000); //The sleep between each character's turn
	}
	
	Sleep(1000);
	return 1; //If nothing else trips, return
}

//Combat function for use during the standard game
bool combat(int select, vector<shared_ptr<Being>> old_char_vect) {
	//Set up combat
	vector<shared_ptr<Being>> monst_turn_order = {};
	setupMonsterCombat(monst_turn_order, select);
	
	//Build the character vector
	if (old_char_vect.size() == 0) {
		genCast(upgradeMatrix);
	}
	else {
		//This is a second or third round of combat
		//So the characterVect was previously built
	}

	//Variables
	bool exit = 1;
	bool monst_status = 1;
	bool char_status = 1;

	//Loop turns until one side dies
	while (exit != 0) {
		
		
		//If the monster/character turns exit with no one dead they will return 1. 
		//If either party completely dies then it will return 0 and trigger the exit
		monst_status = monster_turn(monst_turn_order);
		char_status = character_turn(monst_turn_order);
		exit = monst_status * char_status; //Exit == 0 completes combat
	}

	//If all the monsters died
	if (monst_status == 0) {
		//Flavor text
		return 1;
	}
	//If all the characters died
	else {
		//Flavor text
		return 0;
	}
}

//Overloaded version of the combat function for skirmish
//TODO: make sure that they are the same function
bool combat(vector<shared_ptr<Being>> monst_turn_order, vector<shared_ptr<Being>> old_char_vect) {
	
	//Build the character vector
	if (old_char_vect.size() == 0) {
		genCast(upgradeMatrix);
	}
	else {
		//This is a second or third round of combat
		//So the characterVect was previously built
	}

	//Variables
	bool exit = 1;
	bool monst_status = 1;
	bool char_status = 1;

	//Loop turns until one side dies
	while (exit != 0) {

		//If the monster/character turns exit with no one dead they will return 1. 
		//If either party completely dies then it will return 0 and trigger the exit
		monst_status = monster_turn(monst_turn_order);
		char_status = character_turn(monst_turn_order);
		exit = monst_status * char_status; //Exit == 0 completes combat
	}

	//If all the monsters died
	if (monst_status == 0) {
		for (int i = 0; i < characterVect.size(); i++) {
			if (characterVect[i]->is_stunned == 1) {
				characterVect[i]->unstun();
			}
		}
		cout << "You vanquished the tomb. You raid it for everything not nailed down." << endl;//Flavor text
		Sleep(1000);
		return 1;
	}
	//If all the characters died
	else {
		cout << "The tomb has vanquished you." << endl; //Flavor text
		Sleep(1000);
		return 0;
	}
}

//The function for the main menu, will run continuously until user wants to exit program
void main_menu() {	
	srand(time(NULL));
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
				{3, 4, 6}	//Hard
			};

			//Select a cast set of monsters
			string difficulty_options = "   Easy\n   Medium\n   Hard\n";
			clearscreen();
			vector<string> dyn_input = string_manip(difficulty_options, "   ", ">> ");
			int input = dynamic_input(dyn_input, "Select the difficulty level of monsters.\n");
			
			bool victory = 0;

			//Conduct combat
			for (int x = 0; x < options[input].size(); x++) {
				setupMonsterCombat(skirm_vect, options[input][x]);
				victory = combat(skirm_vect,characterVect);

				//If the user loses during the round
				if (victory == 0) {
					cout << "You have lost and your soldiers will join the ranks of the undead. Better luck next time!" << endl;
					Sleep(1000);
					clearscreen();
					break;
				}
			}
			
			//Endstate if user won
			if (victory == 1) {
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
	
	//DELETE: Temp Combat Testing
	srand(time(NULL));
	title_art();
	vector<shared_ptr<Being>> skirm_vect = {};

	//Vector of options to select from
	vector<vector<int>> options{
		{3, 3},			//Easy
		{3, 4},			//Medium
		{3, 4, 6},		//Hard
		{4, 4, 6, 6}	//Impossible
	};

	string difficulty_options = "   Easy\n   Medium\n   Hard\n   Impossible\n";
	clearscreen();
	vector<string> dyn_input = string_manip(difficulty_options, "   ", ">> ");
	int input = dynamic_input(dyn_input, "Select the difficulty level of monsters.\n");

	bool victory = 0;

	//Conduct combat
	for (int x = 0; x < options[input].size(); x++) {
		clearscreen();
		cout << "Round " << x+1 << " of " << options[input].size() << endl;
		Sleep(1500);
		setupMonsterCombat(skirm_vect, options[input][x]);
		victory = combat(skirm_vect, characterVect);

		//If the user loses during the round
		if (victory == 0) {
			clearscreen();
			cout << "You have lost and your soldiers will join the ranks of the undead. Better luck next time!" << endl;
			Sleep(2500);
			clearscreen();
			break;
		}
	}

	//Endstate if user won
	if (victory == 1) {
		clearscreen();
		cout << "You have beaten the tomb and carried off the riches hidden within." << endl;
		Sleep(2500);
		clearscreen();
	}

	
	//main_menu();
}