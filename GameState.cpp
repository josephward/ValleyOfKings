#include <fstream>
#include <vector>
#include <string>
#include <iostream>
#include <iomanip>
#include <chrono>
#include <thread>

#include "Character.h"
#include "Monster.h"
#include "GameState.h"

using namespace std;
using namespace this_thread;
using namespace chrono;

//Vectors to store 
vector<Monster> monst_vect;
vector<Character> char_vect;

//*****************************General Functions*****************************

//Function checks if all of the cast is dead to see if combat should end
bool check_vectors(vector<Character> vect) {
	bool state = 0;
	//Loops through each character, if anyone is alive the state will stay true.
	for (int i = 0; i < vect.size(); i++) {
		if (vect[i].get_HP() > 0) {
			state += 1;
		}
	}
	return state;
}

//Function checks if all of the monsters are dead to see if combat should end
bool check_vectors(vector<Monster> vect) {
	//If the monster vector is size 0 then all the monsters are dead
	bool state = 1;
	if (vect.size() == 0) {
		state = 0;
	}
	return state;
}

//Set turn order for the monsters and the cast depending in one of two modes, depending on mode desired.
// set_mode = 0: sets the turn order at random
// set_mode = 1; resets all the turns to zero
void set_turn_order(vector<Monster>& monster_turn_order, vector<Monster> monst_vect, vector<Character>& char_turn_order, vector<Character> char_vect, int set_mode) {

	//Import the monster and cast vectors
	vector<Monster> monsters = monst_vect;
	vector<Character> cast = char_vect;

	//Set Mode 0: sets the turn order for the monsters and the cast
	if (set_mode == 0) {
		int m_size = monsters.size(); //if you use monsters.size() directly it eliminates a monster for some reason.
		//For each unassigned monster, choose a random one, add it to the turn order, then erase the first vector
		for (int i = 0; i < m_size; i++) {
			int r = rand() % monsters.size();			//Pick random monster from monster_vect
			monsters[r].set_unit_order(i);				//Set object turn order attribute
			monster_turn_order.push_back(monsters[r]);	//Add monster to set_unit_order
			monsters.erase(monsters.begin() + r);		//Erase random monster from monster_vect, then loop
		}

		int c_size = cast.size();
		for (int i = 0; i < c_size; i++) {
			int r = rand() % cast.size();				//Pick random character from character_vect
			cast[r].set_unit_order(i);					//Set object turn order attribute
			char_turn_order.push_back(cast[r]);			//Add character to set_unit_order
			cast.erase(cast.begin() + r);				//Erase random character from character_vect, then loop
		}
	}
	else if (set_mode == 1) {
		//Set Mode 1: resets all of the turn order to 0 for next round
		//Doesn't set the monsters because those classes will be deleted
		for (int i = 0; cast.size() > i; i++) {
			cast[i].set_unit_order(5);
		}
	}
}

//Function that ensures that the input is an integer
int check_response() {
	//Ask for input
	int response = 0;
	cin >> response;
	//While the input is incorrect, print an error message and re-ask
	while (cin.fail()) {
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "Error, invalid input. Please type the number related to the action you want to do.\nExample: to select '[1] Attack', type 1 and hit enter." << endl;
		cin >> response;
	}
	//return the integer response
	return response;
}

//Checks to see if either all monsters or cast is dead
bool fin_combat(vector<Monster> monster_turn_order, vector<Character> cast_turn_order) {
	bool mon_val = check_vectors(monster_turn_order); //Check for the monsters
	bool cast_val = check_vectors(cast_turn_order); //Check for the characters
	bool in_combat = 1;
	in_combat = mon_val * cast_val; //If either monsters or characters are 0, then in_combat will be false
	return in_combat;
}

//*****************************Monster Combat Functions*****************************

//Monster action that attacks a cast member.
void attack_cast(Character& target, Monster current_monst, int Dmg_Modifier) {
	std::cout << current_monst.get_name() << " attacks " << target.get_name() << " for " << current_monst.std_attack() + Dmg_Modifier << " damage!" << endl;
	target.takeDmg(current_monst.std_attack() + Dmg_Modifier);
}

//Monster action that stuns a cast member.
void stun_cast(Character& target, Monster current_monst) {
	std::cout << current_monst.get_name() << " stuns " << target.get_name() << "!" << endl;
	target.stun();
}

//*****************************Character Combat Functions*****************************

//Cast action that chooses a monster to attack
void attack_monsters(Character current_cast, vector<Monster>& monster_turn_order, int dmg_mult) {
	print_monsters(monster_turn_order);
	int response = 0;
	bool status = 0;

	//Checks if the user input is an integer.
	response = check_response() - 1;
	//Checks if the user input is a number in range
	while (status != 1) {
		if (response > monster_turn_order.size()) {
			cout << "Error, invalid input. Please type a number corrisponding to a monster." << endl;
			response = check_response() - 1;
		}
		else {
			status = 1;
		}
	}

	//Prints who gives and receives damage and the remaining HP, and changes the values
	std::cout << current_cast.get_name() << " attacks " << monster_turn_order[response].get_name() << " for " << current_cast.std_attack() + dmg_mult << "!" << endl;
	monster_turn_order[response].takeDmg(current_cast.std_attack() + dmg_mult);
}

//Cast action that chooses a monster to stun
void stun_monsters(vector<Monster>& monster_turn_order) {
	//Prints all the monsters, then asks for a choice
	print_monsters(monster_turn_order);
	int response;
	response = check_response() - 1;
	monster_turn_order[response].stun(); //Stuns the chosen monster

	//Prints that the monster is stunned
	std::cout << monster_turn_order[response].get_name() << " is stunned!" << endl;
}

//Cast action that chooses a cast member to heal
void heal_cast(Character current_cast, vector<Character>& cast_turn_order, vector<Character> cast_vect) {
	//Prints the cast, then asks to choose one
	print_cast(cast_turn_order);
	int response;
	response = check_response() - 1;
	//Heals the cast member
	cast_turn_order[response].healDmg(current_cast.std_heal());

	//If the user tries to heal more than the amount they are supposed to, they are set to the correct amount
	if (cast_turn_order[response].get_HP() > cast_vect[response].get_HP()) {
		cout << cast_turn_order[response].get_name() << "'s health was set to the max amount. Their new hit points are " << cast_vect[response].get_HP() << endl;
		cast_turn_order[response].set_HP(cast_vect[response].get_HP());
	}
}

//*****************************Print Functions*****************************

//Function to print the enemies currently being encountered
//prints: name | HP
void print_units(vector<Monster> input_vect) {
	//Set up vectors and variables
	vector<Monster> vect = input_vect;
	int size = input_vect.size();
	int len = 0;

	//Iterates through all of the values to be printed, 
	//then finds the length of the largest stinrg to be printed.
	for (int i = 0; size > i; i++) {
		if (input_vect[i].get_name().size() > len) {
			len = input_vect[i].get_name().size();
		}
	}

	//Print each monster's values, spaced to make it look a little nicer.
	for (int i = 0; size > i; i++) {
		std::cout << setw(len) << input_vect[i].get_name() << " | " << input_vect[i].get_HP() << endl;
	}
	std::cout << endl;
}

//Function to print the cast
//prints: name | HP
void print_units(vector<Character> input_vect) {
	//Set up vectors and variables
	vector<Character> vect = input_vect;
	int size = input_vect.size();
	int len = 0;

	//Iterates through all of the values to be printed, 
	//then finds the length of the largest stinrg to be printed.
	for (int i = 0; size > i; i++) {
		if (input_vect[i].get_name().size() > len) {
			len = input_vect[i].get_name().size();
		}
	}

	//Print each monster's values, spaced to make it look a little nicer.
	for (int i = 0; size > i; i++) {
		std::cout << setw(len) << input_vect[i].get_name() << " | " << input_vect[i].get_HP() << endl;
	}
	std::cout << endl;
}

//Prints which monsters are active so the user can select which one
//[turn order] monster name | HP status 
void print_monsters(vector<Monster> monster_turn_order) {
	//For each monster, print the monster using the format:
	for (int i = 0; i < monster_turn_order.size(); i++) {
		int var = i + 1;
		string status;
		//If the monster is stunned included stunned
		if (monster_turn_order[i].is_stunned == 1) {
			status = "stunned";
		}
		std::cout << "[" << var << "]" << monster_turn_order[i].get_name() << " | " << monster_turn_order[i].get_HP() << setw(10) << status << endl;
	}
	std::cout << endl;
}

// Prints cast members so user can select which one.
// Used by the cast heal function
//[turn order] character name | HP
void print_cast(vector<Character> cast_turn_order) {
	vector<Character> vector_turn_order = cast_turn_order;
	//For each character print in the format
	for (int i = 0; i < vector_turn_order.size(); i++) {
		int var = i + 1;
		std::cout << "[" << var << "]" << vector_turn_order[i].get_name() << " | " << vector_turn_order[i].get_HP() << endl;
	}
	std::cout << endl;
}

//Prints the cast's important details during battle
//[turn order] character name HP/Max HP status
void print_combat_cast(vector<Character> cast_turn_order, vector<Character> cast) {
	//Prints each character in the format:
	
	for (int i = 0; i < cast_turn_order.size(); i++) {
		string status;
		if (cast_turn_order[i].is_stunned == 1) {
			status = "stunned";
		}
		if (cast_turn_order[i].get_HP() <= 0) {
			status = "unconscious";
		}
		std::cout << setw(11) << cast_turn_order[i].get_name() << " " << cast_turn_order[i].get_HP() << "/" << cast[i].get_HP() << setw(12) << status << endl;
	}
	std::cout << endl;
}

//*****************************Main Combat Functions*****************************
//Functions for combat, and the monster and cast turn

//Function that conducts the monster's turn. For each monster that's alive, check if they can do an action
void monster_turn(vector<Monster>& monst_turn_order, vector<Character>& cast_turn_order) {
	int r = 0;

	//If the monster goes below 0 hitpoints delete from vector and pass the turn
		//Then end skip the monster
	for (int i = 0; i < monst_turn_order.size(); i++) {
		if (monst_turn_order[i].get_HP() < 1) {
			monst_turn_order.erase(monst_turn_order.begin() + i);
			i -= 1;
		}
	}
	
	//If all the monsters are dead, end the function.
	if (monst_turn_order.size() == 0) {
		return;
	}

	std::cout << "The Monsters attack!" << endl << endl;
	this_thread::sleep_for(milliseconds(2500)); //Adds a time delay

	//For each monster select a valid target then conduct an attack
	for (int i = 0; i < monst_turn_order.size(); i++) {
		//Set up variables
		Monster current_monst = monst_turn_order[i];
		int attack_select = rand() % 5;						//Choose a random attack
		int char_select = rand() % cast_turn_order.size();	//Choose a random cast member as a target
		int temp_target = char_select;
		int x = 0;

		//Search through the cast list and find a valid target
		//Used rand instead of just going to next cast member so that chance to hit stays the same for all characters
		bool valid_target = 0;
		while (valid_target == 0) {
			//If the current character has HP > 0 choose them
			if (cast_turn_order[char_select].get_HP() != 0) {
				temp_target = char_select;
				valid_target = 1;
			}
			//Else choose a random other character
			//Choose random characters 30 times, if they still cannot find a match then just pass
			else {
				char_select = rand() % 4;
				//There is a 0.018% chance that this loop will not find a match
				if (x > 30) {
					return;
				}
			}
			x++;
		}

		//Run through the cast list and find the one with the lowest HP
		//If all characters are equal, defaults to the first nonQuintus character
		int temp_weak_target = 0;
		for (int j = 1; j < cast_turn_order.size(); j++) {
			//If the jth indice has a smaller value, replace the weak_target
			if (cast_turn_order[temp_weak_target].get_HP() < cast_turn_order[j].get_HP() && cast_turn_order[j].get_HP() > 0) {
				temp_weak_target = j;
			}
		}

		//Set up pointers for the target character and the weakest character
		Character* target_Ptr = &cast_turn_order[temp_target];
		Character* weak_target_Ptr = &cast_turn_order[temp_weak_target];

		//If the monster is stunned, unstun them and pass the turn
		if (current_monst.is_stunned == 1) {
			std::cout << current_monst.get_name() << " is stunned!" << endl;
			monst_turn_order[i].unstun_monster();
		}

		//If the monster is not stunned, choose an attack option
		//This section governs the 'Monster AI'
		//Currect setup gives a roughly 40% chance to hit the weakest character and 20% to all other characters
		else if (current_monst.get_HP() != 0 && current_monst.is_stunned == 0) {

			if (attack_select == 0) { // Light random attack
				attack_cast(*target_Ptr, current_monst, 0);
			}
			else if (attack_select == 1) { // Light random attack
				attack_cast(*target_Ptr, current_monst, 0);
			}
			else if (attack_select == 2) { // Heavy random attack
				attack_cast(*target_Ptr, current_monst, 2);
			}
			else if (attack_select == 3) { // Light target weakest attack
				attack_cast(*weak_target_Ptr, current_monst, 0);
			}
			else if (attack_select == 4) { // Random stun attack
				stun_cast(*target_Ptr, current_monst);
			}
			std::cout << endl;
		}
		this_thread::sleep_for(milliseconds(2000)); //Adds a time delay
	}
}

//Function that computes the turn for the user
void cast_turn(vector<Monster>& monster_turn_order, vector<Character>& cast_turn_order, vector<Character> cast_vect) {
	print_combat_cast(cast_turn_order, cast_vect); //Print the cast
	bool old_magic = 0;

	//For each cast member, in their turn order, conduct their turn
	for (int i = 0; i < cast_turn_order.size(); i++) {

		Character current_cast = cast_turn_order[i]; //Short hand for some functions
		this_thread::sleep_for(milliseconds(1000)); //Adds a time delay

		int cast_response;

		//Break conditions for:
		//If all the monsters died during the turn and end the loop
		int status = 0;
		for (int i = 0; i < monster_turn_order.size(); i++) {
			if (monster_turn_order[i].get_HP() > 0) {
				status += 1;
			}
		}
		if (status < 1) {
			break;
		}
		
		//If the current cast member is unconscious
		if (cast_turn_order[i].get_HP() <= 0) {
			if (cast_turn_order[i].get_HP() < 0) {
				std::cout << cast_turn_order[i].get_name() << " is unconscious!" << endl;
				cast_turn_order[i].change_HP(0);
			}
		}
		//If the current cast member is stunned
		else if (cast_turn_order[i].is_stunned == 1) {
			std::cout << cast_turn_order[i].get_name() << " is stunned! " << endl;
			cast_turn_order[i].is_stunned = 0;
		}

		//Else, execute actions based on which character it is

		//Conduct the turn if it is Quintus
		else if (current_cast.get_name() == "Quintus") {
			//Output the class options
			std::cout << "Infantry: Quintus" << endl;
			std::cout << "[1] Attack" << endl;
			std::cout << "[2] Shield Bash (Stun)" << endl;
			cast_response = check_response();
			//Attack monster option
			if (cast_response == 1) {
				attack_monsters(current_cast, monster_turn_order);
			}
			//Stun monster option
			else if (cast_response == 2) {
				stun_monsters(monster_turn_order);
			}
			//If invalid option just attack a monster
			else {
				attack_monsters(current_cast, monster_turn_order);
			}
		}
		else if (current_cast.get_name() == "Nysa") {
			//Output the class options
			std::cout << "Cultist: Nysa" << endl;
			std::cout << "[1] Attack" << endl;
			std::cout << "[2] Jupiter's Lightning" << endl;
			cast_response = check_response();
			//Attack monster option
			if (cast_response == 1) {
				attack_monsters(current_cast, monster_turn_order);
			}
			//Special action option
			else if (cast_response == 2) {
				cout << current_cast.get_name() << " calls down lightning! It does " << current_cast.std_attack() / 2 << " damage to all monsters!" << endl;
				//For each monster cause them to take std damage / 2
				for (int i = 0; i < monster_turn_order.size(); i++) {
					if (monster_turn_order[i].get_HP() != 0) {
						monster_turn_order[i].takeDmg(current_cast.std_attack() / 2);
					}
				}
			}

			//Default to attack monsters
			else {
				attack_monsters(current_cast, monster_turn_order);
			}

		}
		else if (current_cast.get_name() == "Paltibaal") {
			//Output the class options
			std::cout << "Healer: Paltibaal" << endl;
			std::cout << "[1] Attack" << endl;
			std::cout << "[2] Heal" << endl;
			cast_response = check_response();
			//Attack monsters option
			if (cast_response == 1) {
				attack_monsters(current_cast, monster_turn_order);
			}
			//Heal cast option
			else if (cast_response == 2) {
				heal_cast(current_cast, cast_turn_order, cast_vect);
			}
			//Default to attack monster
			else {
				attack_monsters(current_cast, monster_turn_order);
			}
		}

		else if (current_cast.get_name() == "Ganna") {
			//Output the class options
			std::cout << "Druid: Ganna" << endl;
			std::cout << "[1] Attack" << endl;
			std::cout << "[2] Old Magic" << endl;
			cast_response = check_response();
			//Attack Monster option
			if (cast_response == 1) {
				attack_monsters(current_cast, monster_turn_order);
			}
			//Special action option
			else if (cast_response == 2) {
				//Attack the monsters using current_cast.std_attack as the attack modifier
				//This doubles whatever the attack output is
				attack_monsters(current_cast, monster_turn_order, current_cast.std_attack());
				//Stun the character
				std::cout << cast_turn_order[i].get_name() << " has been stunned!" << endl;
				cast_turn_order[i].stun();
				old_magic = 1; //Sets this variable so that the stun carries to the next turn
			}
			//Default to attack monsters
			else {
				attack_monsters(current_cast, monster_turn_order);
			}
		}
		//If action old magic was done this turn, the cast member stays stunned for one turn and old magic is reset
		if (old_magic == 1) {
			old_magic = 0;
		}
		//Otherwise you unstun at the end of the turn
		else {
			cast_turn_order[i].unstun();;
		}
	}
}

//The big function that conducts combat turns for monsters and characters
void combat_turns(vector<Monster> &monst_vect, vector<Character> &char_vect) {	
	//Imports monster, character vectors and sets a status check.
	bool combat_status = 1; //A check to see if combat should end, starts true.
	vector<Monster> monsters = monst_vect;
	vector<Monster> monster_turn_order;
	vector<Character> cast = char_vect;
	vector<Character> cast_turn_order;

	//Set the turn order for the monsters and characters
	//using the monsters and cast vectors as options to choose from
	set_turn_order(monster_turn_order, monsters, cast_turn_order, cast, 0);
	vector<Character> original_cast = cast_turn_order; //Vector to show orignal health

	//Continually have alternating monster and character turns until one side all dies
	while (combat_status == true) {
		monster_turn(monster_turn_order, cast_turn_order);
		
		//Checks to see if either all monsters or cast is dead.
		combat_status = fin_combat(monster_turn_order, cast_turn_order);
		if (combat_status == 0) {
			break;
		}
		
		cast_turn(monster_turn_order, cast_turn_order, original_cast);
		
		//Checks to see if either all monsters or cast is dead.
		combat_status = fin_combat(monster_turn_order, cast_turn_order);
		if (combat_status == 0) {
			break;
		}
	}

	//Reset turn order to 0
	set_turn_order(monster_turn_order, monsters, cast_turn_order, cast, 1);
	
	//Prints text to let the user know the result of the combat
	string final_string = " ";
	//If the characters win this is the final text
	if (monster_turn_order.size() == 0) {
		final_string = "\nYou have successfully vanquished the evil in the tomb! Now the riches are yours for the taking.\nEach of you return to your various cities to great acclaim and inspire the next generation of adventurers!\n\n";
	}
	//If the monsters win this is the final text
	else {
		final_string = "\nYour party failed to beat the monsters. You will now become undead guardians of the tomb until the next\nset of grave robbers come through. May Jupiter have mercy on your souls.\n\n";
			
	}
	int x = 0;
	//Print the final text like its typing
	while (final_string[x] != '\0') {
		std::cout << final_string[x];
		sleep_for(milliseconds(40 + rand() % 40));
		x++;
	}
}

//*****************************Generation Functions*****************************
//These functions will generate vectors of Characters or Monsters based on preset conditions

//Sets up 4 character objects with basic values, then reads them into the char_vect for ease of access
vector<Character> init_cast() {
	char_vect.clear(); //Clears any extra data
	//Sets up the cast for the initial game creation
	Character infantry = Character("Quintus", 16, 6, 0);		//Initial Infantry Class
	Character cultist = Character("Nysa", 12, 4, 0);			//Initial Cultist Class
	Character druid = Character("Ganna", 12, 4, 0);				//Initial Druid Class
	Character healer = Character("Paltibaal", 12, 4, 6);		//Initial Healer Class

	//Put the cast into the character vector to be referenced
	char_vect.push_back(infantry);
	char_vect.push_back(cultist);
	char_vect.push_back(druid);
	char_vect.push_back(healer);

	//Print the vector of created characters, then return the vector
	print_units(char_vect);
	return(char_vect);
}

//Generate monsters for the easy/tutorial mode
vector<Monster> gen_basic_squad_3() {
	monst_vect.clear(); //Clear previous monsters
	//Generates three basic monsters. Low health and damage.
	Monster monster1 = Monster("1st Undead Soldier", 8, 3);
	Monster monster2 = Monster("2nd Undead Soldier", 8, 3);
	Monster monster3 = Monster("3rd Undead Soldier", 8, 3);

	//Add each monster to the monster vector
	monst_vect.push_back(monster1);
	monst_vect.push_back(monster2);
	monst_vect.push_back(monster3);

	//Print and return the created vector
	print_units(monst_vect);
	return monst_vect;
}

//Generate monsters for the medium mode
vector<Monster> gen_basic_squad_4() {
	monst_vect.clear(); //Clear previous monsters
	//Generates four basic monsters. Low health and damage.
	Monster monster1 = Monster("1st Undead Soldier", 10, 4);
	Monster monster2 = Monster("2nd Undead Soldier", 10, 4);
	Monster monster3 = Monster("3rd Undead Soldier", 10, 4);
	Monster monster4 = Monster("4th Undead Soldier", 10, 4);

	//Add each monster to the monster vector
	monst_vect.push_back(monster1);
	monst_vect.push_back(monster2);
	monst_vect.push_back(monster3);
	monst_vect.push_back(monster4);

	//Print and return the created vector
	print_units(monst_vect);
	return monst_vect;
}

//Generate monsters for the impossible mode
vector<Monster>  gen_capt_squad_5() {
	monst_vect.clear(); //Clear previous monsters

	//Generates three basic monsters and a captain. Low health and damage.
	Monster monster1 = Monster("1st Undead Soldier", 10, 4);
	Monster monster2 = Monster("2nd Undead Soldier", 10, 4);
	Monster monster3 = Monster("3rd Undead Soldier", 10, 4);
	Monster monster5 = Monster("4th Undead Soldier", 10, 4);
	Monster monster4 = Monster("Undead Squad Leader", 16, 6);

	//Add each monster to the monster vector
	monst_vect.push_back(monster1);
	monst_vect.push_back(monster2);
	monst_vect.push_back(monster3);
	monst_vect.push_back(monster4);
	monst_vect.push_back(monster5);

	//Print and return the created vector
	print_units(monst_vect);
	return monst_vect;
}