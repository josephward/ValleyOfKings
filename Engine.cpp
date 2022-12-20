#include "Engine.h"

//Game Engine Vectors
vector<shared_ptr<Being>> turn_order_vect = {};
vector<shared_ptr<Being>> characterVect = {};
vector<string> itemvect{}; //TODO: Add the Item class in

//Setup for Upgrade Matrix
vector<int> m1{ 0 }; //Infantry
vector<int> m2{ 0 }; //Cultist
vector<int> m3{ 0 }; //Healer
vector<int> m4{ 0 }; //Druid
vector<vector<int>> upgradeMatrix {m1, m2, m3, m4};

//State Variables for the Save File
int DIFFICULTY_LEVEL = 1;
int GOLD_STASH = 0;
int LEVEL_BEATEN = 0;
int UPGRADE_POINTS = 0;

//--------------------------------------General Functions--------------------------------------

//Function that prints the title card for the game art
//Art generated from https://patorjk.com/software/taag/#p=testall&f=Doh&t=Valley%20of%20Kings using Colossal
void title_art() {
	std::cout << endl;
	std::cout
		<< " 888     888         888 888                                  .d888      888    d8P  d8b                            " << endl
		<< " 888     888         888 888                                 d88P        888   d8P   Y8P                            " << endl
		<< " 888     888         888 888                                 888         888  d8P                                   " << endl
		<< " Y88b   d88P 8888b.  888 888  .d88b.  888  888       .d88b.  888888      888d88K     888 88888b.   .d88b.  .d8888b  " << endl
		<< "  Y88b d88P      88b 888 888 d8P  Y8b 888  888      d88  88b 888         8888888b    888 888  88b d88P 88b 88K      " << endl
		<< "   Y88o88P  .d888888 888 888 88888888 888  888      888  888 888         888  Y88b   888 888  888 888  888  Y8888b. " << endl
		<< "    Y888P   888  888 888 888 Y8b.     Y88b 888      Y88..88P 888         888   Y88b  888 888  888 Y88b 888      X88 " << endl
		<< "     Y8P     Y888888 888 888   Y8888    Y88888        Y88P   888         888    Y88b 888 888  888   Y88888  88888P  " << endl
		<< "                                           888                                                         888          " << endl
		<< "                                      Y8b d88P                                                    Y8b d88P          " << endl
		<< "                                        Y88P                                                        Y88P            " << endl << endl;
}

//Currently Not Used for Anything
//Checks if a vector has anything in it
int checkVect(vector<int> vect) {
	int sum = 0;
	for (int i = 0; i < vect.size(); i++) {
		sum += vect[i];
	}

	return sum;
}

//--------------------------------------Boss Functions--------------------------------------

shared_ptr<Being> genBoss(int option) {
	switch (option) {

	//Generate Anubis
	case 1: {
		Boss newBoss = Boss("Incarnation of Anubis", "", 50, 0);
		auto ptr = make_shared<Being>(newBoss);
		return ptr;
	}
	}
}

//--------------------------------------Monster Functions--------------------------------------

//Function that provides a succinct way to generate monsters
shared_ptr<Being> genMonster(int option) {
	switch (option) {
	
	//Generate Undead Warrior
	case 1: {
		Monster newMonst = Monster("Undead Warrior", "Undead", 8, 2);
		auto ptr = make_shared<Being>(newMonst);
		return ptr;
	}
	//Generate Undead Captain
	case 2: {
		Monster newMonst = Monster("Undead Captain", "Undead", 8, 4);
		auto ptr = make_shared<Being>(newMonst);
		return ptr;
	}
	//Generate Nomarch
	case 3: {
		Monster newMonst = Monster("Nomarch", "Undead", 10, 4);
		auto ptr = make_shared<Being>(newMonst);
		return ptr;
	}
	//Generate Sphinx
	case 4: {
		Monster newMonst = Monster("Sphinx", "Creature", 12, 4);
		auto ptr = make_shared<Being>(newMonst);
		return ptr;
	}
	//Generate Mummy
	case 5:
		Monster newMonst = Monster("Mummy", "Undead", 0, 0);
		auto ptr = make_shared<Being>(newMonst);
		return ptr;
	}
}

//Function that is a switch statement for each of the encounters of the game
void setupMonsterCombat(vector<shared_ptr<Being>>& turn_order_vect, int encounter) {
	turn_order_vect.clear(); //Ensure empty vector
	switch (encounter) {
	
	//Level 1
	case 1: {
		//3 Undead Warriors
		turn_order_vect.push_back(genMonster(1));
		turn_order_vect.push_back(genMonster(1));
		turn_order_vect.push_back(genMonster(1));
	}
	case 2: {
		//3 Undead Warriors and a Captain
		turn_order_vect.push_back(genMonster(1));
		turn_order_vect.push_back(genMonster(1));
		turn_order_vect.push_back(genMonster(1));
		turn_order_vect.push_back(genMonster(2));
	}

	//Level 2
	case 3: {
		//Sphinx and Undead Warrior
		turn_order_vect.push_back(genMonster(4));
		turn_order_vect.push_back(genMonster(1));
	}
	case 4: {
		//Sphinx, Captain, and 2 Undead Warriors
		turn_order_vect.push_back(genMonster(4));
		turn_order_vect.push_back(genMonster(2));
		turn_order_vect.push_back(genMonster(1));
		turn_order_vect.push_back(genMonster(1));
	}
	case 5: {
		//Nomarch, 2 Captains, and 2 Mummies
		turn_order_vect.push_back(genMonster(3));
		turn_order_vect.push_back(genMonster(2));
		turn_order_vect.push_back(genMonster(2));
		turn_order_vect.push_back(genMonster(2));
		turn_order_vect.push_back(genMonster(5));
		turn_order_vect.push_back(genMonster(5));
	}

	//Boss Level
	case 6: {
		//Nomarch, 2 Mummies, and Boss 1
		turn_order_vect.push_back(genMonster(3));
		turn_order_vect.push_back(genMonster(5));
		turn_order_vect.push_back(genMonster(5));
		turn_order_vect.push_back(genBoss(1));
	}
	}
}

//--------------------------------------Character Functions--------------------------------------

//Generate each character with pointers, then put them into a vector.
shared_ptr<Being> genCast(vector<vector<int>>& upgradeMatrix) {
	//TODO: Change so that characters are generated based on the upgrades received

	characterVect.clear(); //Make sure there's nothing in the vector first
	shared_ptr<Being> ptr1, ptr2, ptr3, ptr4;

	//Generate Infantry
	//Upgrade 1
	//Health +2
	if (upgradeMatrix[0][0] != 0) {
		Character newChar1 = Character("Quintus", "", 16+2, 6);
		ptr1 = make_shared<Being>(newChar1);
	}
	//Default Infantry
	else {
		Character newChar1 = Character("Quintus", "", 16, 6);
		ptr1 = make_shared<Being>(newChar1);
	}


	//Generate Cultist
	//Upgrade 1
	//Health +2
	if (upgradeMatrix[1][0] != 0) {
		Character newChar2 = Character("Nysa", "", 12+2, 4);
		ptr2 = make_shared<Being>(newChar2);
	}
	//Default Cultist
	else {
		Character newChar2 = Character("Nysa", "", 12, 4);
		ptr2 = make_shared<Being>(newChar2);
	}


	//Generate Healer
	//Upgrade 1
	//Health +2, Healing +2
	if (upgradeMatrix[2][0] != 0) {
		Character newChar3 = Character("Paltibaal", "", 12+2, 4, 6 + 2);
		ptr3 = make_shared<Being>(newChar3);
	}
	//Default Healer
	else {
		Character newChar3 = Character("Paltibaal", "", 12, 4, 6);
		ptr3 = make_shared<Being>(newChar3);
	}


	//Generate Druid
	//Upgrade 1
	//Health +2
	if (upgradeMatrix[3][0] != 0) {
		Character newChar4 = Character("Ganna", "", 12+2, 4);
		ptr4 = make_shared<Being>(newChar4);
	}
	else {
		Character newChar4 = Character("Ganna", "", 12, 4);
		ptr4 = make_shared<Being>(newChar4);
	}
	
	//Temp Vector
	vector<shared_ptr<Being>> list{ ptr1, ptr2, ptr3, ptr4 };

	//Take the pointers and randomly put them into a vector
	int flip = 0, var = 0;
	while (flip == 0) {
		//Randomly choose pointer and load vector
		var = rand() % list.size();
		characterVect.push_back(list[var]);
		list.erase(list.begin() + var);

		//Triggers end of while loop
		if (list.size() == 0) {
			flip = 1;
		}
	}
}

//--------------------------------------Saving/Loading Functions--------------------------------------

//Function that loads a gamestate from a savefile option
void load_game(int savefile) {

	ifstream input;

	//Select which save file to interact with
	if (savefile == 1) {
		input.open("Save_File_1.txt");
	}
	else if (savefile == 2) {
		input.open("Save_File_2.txt");
	}
	else if (savefile == 3) {
		input.open("Save_File_3.txt");
	}

	//Variables from the file
	//Expand when there are more upgrades supported
	string garb; //Used to read in and dispose of useless data from file
	bool infantry_upgrade = 0;
	bool cultist_upgrade = 0;
	bool healer_upgrade = 0;
	bool druid_upgrade = 0;

	//Load in the data from the save file

	//Load in status variables
	input >> garb >> DIFFICULTY_LEVEL >> garb >> GOLD_STASH
		>> garb >> LEVEL_BEATEN >> garb >> UPGRADE_POINTS;

	//Load in infantry variables
	input >> garb >> infantry_upgrade;
	vector<int> infVect{ infantry_upgrade };
	upgradeMatrix.push_back(infVect);

	//Load in cultist variables
	input >> garb >> cultist_upgrade;
	vector<int> culVect{ cultist_upgrade };
	upgradeMatrix.push_back(culVect);

	//Load in healer variables
	input >> garb >> healer_upgrade;
	vector<int> healVect{ healer_upgrade };
	upgradeMatrix.push_back(healVect);

	//Load in druid variables
	input >> garb >> druid_upgrade;
	vector<int> druidVect{ druid_upgrade };
	upgradeMatrix.push_back(druidVect);
	
	//Load in Item Variables
	input >> garb;
	string tempItem;
	itemvect.clear();
	while (getline(input, tempItem, ' ')) {
		cout << "Found an item! " << tempItem << endl;
		itemvect.push_back(tempItem);
	}
	
	input.close(); //Closes the file.
}

//Function that saves the data from a game into a savefile option
//Deletes the old contents of the save file then overwrites it
void save_game(int savefile) {

	ofstream output;

	//Select which save file to interact with
	if (savefile == 1) {
		output.open("Save_File_1.txt", ofstream::out | ofstream::trunc);
	}
	else if (savefile == 2) {
		output.open("Save_File_2.txt", ofstream::out | ofstream::trunc);
	}
	else if (savefile == 3) {
		output.open("Save_File_3.txt", ofstream::out | ofstream::trunc);
	}
	else {
		cout << "ERROR: this is an invalid save file option.";
		return;
	}
	
	//Variables used in the process
	string item_str = "";

	// If there are items, loop through and add the item ID to the string
	if (itemvect.size() != 0) {
		for (int i = 0; i < itemvect.size(); i++) {
			item_str.append("\n");
			item_str.append(itemvect[i]);
		}
	}

	//Write the save data to the selected file
	output << "Difficulty" << endl << DIFFICULTY_LEVEL;
	output << endl << "Gold Amount"		<< endl << GOLD_STASH;
	output << endl << "Level Completed" << endl << LEVEL_BEATEN;
	output << endl << "Upgrade Points"	<< endl	<< UPGRADE_POINTS;
	output << endl << "Infantry"		<< endl << upgradeMatrix[0][0];
	output << endl << "Cultist"			<< endl << upgradeMatrix[1][0];
	output << endl << "Healer"			<< endl << upgradeMatrix[2][0];
	output << endl << "Druid"			<< endl << upgradeMatrix[3][0];
	output << endl << "Item Collection" << endl << item_str;
	
	output.close(); //Closes the file
}

//Creates or overwrites a save file for a new game to be played in
void new_game(int savefile, int difficulty_level) {
	
	ofstream output;

	//Select which save file to interact with
	if (savefile == 1) {
		output.open("Save_File_1.txt", ofstream::out | ofstream::trunc);
	}
	else if (savefile == 2) {
		output.open("Save_File_2.txt", ofstream::out | ofstream::trunc);
	}
	else if (savefile == 3) {
		output.open("Save_File_3.txt", ofstream::out | ofstream::trunc);
	}
	else {
		cout << "ERROR: this is an invalid save file option.";
		return;
	}

	//Write the save data to the selected file
	output << "Difficulty" << endl << difficulty_level;
	output << endl << "Gold Amount" << endl << 0;
	output << endl << "Level Completed" << endl << 0;
	output << endl << "Upgrade Points" << endl << 0;
	output << endl << "Infantry" << endl << "0";
	output << endl << "Cultist" << endl << "0";
	output << endl << "Healer" << endl << "0";
	output << endl << "Druid" << endl << "0";
	output << endl << "Item Collection";

	output.close(); //Closes the file
}