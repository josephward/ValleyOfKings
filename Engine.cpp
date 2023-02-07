#include "Engine.h"

//Game Engine Vectors
vector<shared_ptr<Being>> turn_order_vect{};
vector<shared_ptr<Being>> characterVect{};
vector<string> itemvect{}; //TODO: Add the Item class in

//Setup for File Name
vector<string> filenames{ "Save_File_1.txt", "Save_File_2.txt", "Save_File_3.txt" };

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
string title_art() {
	string str;
	str += "\n 888     888         888 888                                  .d888      888    d8P  d8b                            \n";
	str +=   " 888     888         888 888                                 d88P        888   d8P   Y8P                            \n";
	str +=   " 888     888         888 888                                 888         888  d8P                                   \n";
	str +=   " Y88b   d88P 8888b.  888 888  .d88b.  888  888       .d88b.  888888      888d88K     888 88888b.   .d88b.  .d8888b  \n";
	str +=   "  Y88b d88P      88b 888 888 d8P  Y8b 888  888      d88  88b 888         8888888b    888 888  88b d88P 88b 88K      \n";
	str +=   "   Y88o88P  .d888888 888 888 88888888 888  888      888  888 888         888  Y88b   888 888  888 888  888  Y8888b. \n";
	str +=   "    Y888P   888  888 888 888 Y8b.     Y88b 888      Y88..88P 888         888   Y88b  888 888  888 Y88b 888      X88 \n";
	str +=   "     Y8P     Y888888 888 888   Y8888    Y88888        Y88P   888         888    Y88b 888 888  888   Y88888  88888P  \n";
	str +=   "                                           888                                                         888          \n";
	str +=   "                                      Y8b d88P                                                    Y8b d88P          \n";
	str +=   "                                        Y88P                                                        Y88P            \n";

	return str;
}

//TODO: Either use this code or eliminate it
//Currently Not Used for Anything
//Checks if a vector has anything in it
int checkVect(vector<int> vect) {
	int sum = 0;
	for (int i = 0; i < vect.size(); i++) {
		sum += vect[i];
	}

	return sum;
}

//Function makes sure that the input is correct for type and range
int verify_input(int lower, int upper) {
	//Ask for input
	int response = 0;
	cin >> response;

	//While the input is the incorrect type, print an error message and re-ask
	while (cin.fail()) {
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "Error, invalid type of input. Please type the number related to the action you want to do.\nExample: to select '[1] Attack', type 1 and hit enter." << endl;
		cin >> response;
	}

	//While the input is out of bounds, print an error message and re-ask
	while (response > upper || response < lower) {
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "Error, out of bounds input. Please type in a number that is a valid option and hit enter." << endl;
		cin >> response;

	}
	//return the integer response
	return response;
}

//Function that clears the screen
//Using the first method from the following resource
//https://www.geeksforgeeks.org/how-to-clear-console-in-cpp/
void clearscreen() {
	system("cls");
}

//Function that accepts a string of options, and allows the user to 'cycle' through the options
//Built in 'collaboration' with several online resources
//Code pulled from a modified version of user93353's answer to: https://stackoverflow.com/questions/24708700/c-detect-when-user-presses-arrow-key
//Virtual-Key Constant Reference https://learn.microsoft.com/en-us/windows/win32/inputdev/virtual-key-codes?redirectedfrom=MSDN
//For future expansion see https://iq.direct/blog/325-how-to-read-direct-mouse-and-keyboard-events-in-c-console-app.html
int dynamic_input(vector<string> str_vect, string default_message, vector<string> explanation) {

	//Example of a good string vector is:
	//string str1 = ">> Save File 1\n   Save File 2\n   Save File 3\n";
	//string str2 = "   Save File 1\n>> Save File 2\n   Save File 3\n";
	//string str3 = "   Save File 1\n   Save File 2\n>> Save File 3\n";
	//This allows for each input to flow nicely to the next

	//Sometimes an explanation vector will be smaller the vector of options
	//This attempts to ensure they are the correct size
	//TODO: have the program throw an exception
	while (explanation.size() < str_vect.size()) {
		explanation.push_back("");
	}

	int x = 0;	//Variable to manipulate vector
	cout << default_message << endl;
	cout << str_vect[x] << endl; // Inital Value 
	cout << explanation[x];

	//While loop to provide continuous input until an ending event
	while (true) {

		//Variables used in the input reading functions below
		HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE);
		DWORD NumInputs = 0;
		DWORD InputsRead = 0;
		bool running = true;
		INPUT_RECORD irInput;

		//Functions to get input from the stream
		//See: https://learn.microsoft.com/en-us/windows/console/readconsoleinput?redirectedfrom=MSDN
		GetNumberOfConsoleInputEvents(hInput, &NumInputs);
		ReadConsoleInput(hInput, &irInput, 1, &InputsRead);

		//If statement required to ensure it doesn't return two triggers (one for press down, and one for letting go)
		if (irInput.Event.KeyEvent.bKeyDown) {
			//Switch statement that interprets the user inputted virtual-key constant reference 
			//See the Virtual-Key Constant reference site above for more keys
			switch (irInput.Event.KeyEvent.wVirtualKeyCode) {

				//Case of what happens when the user selects a value
				case VK_RETURN:
					return x;

				//Case of inputting up
				case VK_UP:
					x--;
					//If the x var. goes smaller than 0, go to the max value
					if (x < 0) {
						x = str_vect.size() - 1;
					}
					clearscreen();
					cout << default_message << endl;
					cout << str_vect[x] << endl;
					cout << explanation[x];
					break;

				//Case of inputting down
				case VK_DOWN:
					x++;
					//If the x var. goes bigger than the max size, go to zero
					if (x > str_vect.size() - 1) {
						x = 0;
					}
					clearscreen();
					cout << default_message << endl;
					cout << str_vect[x] << endl;
					cout << explanation[x];
					break;
				}
		}
	}
}
	
//Function that takes a string, and provides buffered output by default at ~260 words/min
//The time parameter is in turns of milliseconds (1000 ms = 1 sec)
void buffered_output(string str, DWORD time) {
	for (int i = 0; i < str.size(); i++) {
		cout << str[i];
		Sleep(time);
	}
	cout << "\n";
}

//Takes a string, the string to be found, and what to replace it with, then executes.
//This supports finding and replacing multiple options
//Lifted with changes from https://stackoverflow.com/questions/5878775/how-to-find-and-replace-string
//And https://stackoverflow.com/questions/18972258/index-of-nth-occurrence-of-the-string
vector<string> string_manip(string s, string to_replace, string replace_with) {
	//Variables used, and vector returned
	vector<string> str_vect;
	size_t pos = 0, prevPos;
	int cnt = 0, i = 0;

	// Continue looping until you reach the end of the string
	while (true) {
		string temp_str;			// Build fresh string
		temp_str.reserve(s.size());	// Reserve rough estimate of final size

		// Find the next instance of string to replace
		while (cnt == i) {
			prevPos = pos;
			pos = s.find(to_replace, pos);
			cnt++;

			// If pos reaches the end of the string return the function
			if (pos == string::npos) {
				return str_vect;
			}

			//If the first chunk is being replaced
			if (pos == 0) {
				temp_str += replace_with;
				pos += to_replace.size();
				temp_str.append(s, pos, s.size() - pos);
			}
			//If anywhere else is being replaced
			else {
				temp_str.append(s, 0, pos);
				temp_str += replace_with;
				pos += to_replace.size();
				temp_str.append(s, pos, s.size() - pos);
			}

		}
		str_vect.push_back(temp_str); // Add to vector
		i++;
	}
	return str_vect;
}

void print_vect(vector<shared_ptr<Being>> vect) {
	for (int i = 0; i < vect.size(); i++) {
		int var = i + 1;
		string status;
		//If the monster is stunned included stunned
		if (vect[i]->is_stunned == 1) {
			status = "stunned";
		}

		int s = vect[0]->get_name().size();
		vector<string> name_vect;
		for (int i = 0; i < vect.size(); i++) {
			name_vect.push_back(vect[i]->get_name());
			if (vect[i]->get_name().size() > s) {
				s = vect[i]->get_name().size();
			}
		}

		std::cout	<< left 
					<< setw(s+2) << name_vect[i]
					<< setw(5) << vect[i]->get_HP() 
					<< setw(7) << status << endl;
	}
	std::cout << endl;
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
		case 5: {
			Monster newMonst = Monster("Mummy", "Undead", 0, 0);
			auto ptr = make_shared<Being>(newMonst);
			return ptr;
		}
		//Generate Nubian Horse-Archer
		case 6: {
			Monster newMonst = Monster("Nubian Horse-Archer", "Human", 12, 4);
			auto ptr = make_shared<Being>(newMonst);
			return ptr;
		}
		//Generate Nubian Raider
		case 7: {
			Monster newMonst = Monster("Nubian Raider", "Human", 8, 4);
			auto ptr = make_shared<Being>(newMonst);
			return ptr;
		}
		//Generate Egyptian Grave Robber
		case 8: {
			Monster newMonst = Monster("Egyptian Grave Robber", "Human", 8, 4);
			auto ptr = make_shared<Being>(newMonst);
			return ptr;
		}
			  //Generate Egyptian Robber Baron
		case 9: {
			Monster newMonst = Monster("Egyptian Robber Baron", "Human", 8, 6);
			auto ptr = make_shared<Being>(newMonst);
			return ptr;
		}
	}		
}

//Function that is a switch statement for each of the encounters of the game
void setupMonsterCombat(vector<shared_ptr<Being>>& turn_order_vect, int encounter) {
	turn_order_vect.clear(); //Ensure empty vector
	switch (encounter) {
		//Night Raids
		case 1: {
			//Grave Robber Party
			turn_order_vect.push_back(genMonster(6));
			turn_order_vect.push_back(genMonster(6));
			turn_order_vect.push_back(genMonster(7));
			turn_order_vect.push_back(genMonster(7));
			break;
		}
		case 2: {
			//Raider Party
			turn_order_vect.push_back(genMonster(8));
			turn_order_vect.push_back(genMonster(8));
			turn_order_vect.push_back(genMonster(9));
			break;
		}

		//Level 1
		case 3: {
			//3 Undead Warriors
			turn_order_vect.push_back(genMonster(1));
			turn_order_vect.push_back(genMonster(1));
			turn_order_vect.push_back(genMonster(1));
			break;
		}
		case 4: {
			//3 Undead Warriors and a Captain
			turn_order_vect.push_back(genMonster(1));
			turn_order_vect.push_back(genMonster(1));
			turn_order_vect.push_back(genMonster(1));
			turn_order_vect.push_back(genMonster(2));
			break;
		}

		//Level 2
		case 5: {
			//Sphinx and Undead Warrior
			turn_order_vect.push_back(genMonster(4));
			turn_order_vect.push_back(genMonster(1));
			break;
		}
		case 6: {
			//Sphinx, Captain, and 2 Undead Warriors
			turn_order_vect.push_back(genMonster(4));
			turn_order_vect.push_back(genMonster(2));
			turn_order_vect.push_back(genMonster(1));
			turn_order_vect.push_back(genMonster(1));
			break;
		}
		case 7: {
			//Nomarch, 2 Captains, and 2 Mummies
			turn_order_vect.push_back(genMonster(3));
			turn_order_vect.push_back(genMonster(2));
			turn_order_vect.push_back(genMonster(2));
			turn_order_vect.push_back(genMonster(5));
			turn_order_vect.push_back(genMonster(5));
			break;
		}

		//Boss Level
		case 8: {
			//Nomarch, Mummy, Sphinx
			turn_order_vect.push_back(genMonster(3));
			turn_order_vect.push_back(genMonster(5));
			turn_order_vect.push_back(genMonster(4));
			break;
		}
		case 9: {
			//Nomarch, Captain, 2 Mummies
			turn_order_vect.push_back(genMonster(3));
			turn_order_vect.push_back(genMonster(2));
			turn_order_vect.push_back(genMonster(5));
			turn_order_vect.push_back(genMonster(5));
			break;
		}
		case 10: {
			//Nomarch, 2 Mummies, and Boss 1
			turn_order_vect.push_back(genMonster(3));
			turn_order_vect.push_back(genMonster(5));
			turn_order_vect.push_back(genMonster(5));
			turn_order_vect.push_back(genBoss(1));
			break;
		}

		//Level 4
		//Level 5
		//Boss Level 2

		//Level 7
		//Level 8
		//Level 9
		//Boss Level 3
	}
}

//--------------------------------------Character Functions--------------------------------------

//Generate each character with pointers, then put them into a vector.
void genCast(vector<vector<int>>& upgradeMatrix) {
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
	output << endl << "Difficulty"		<< endl << DIFFICULTY_LEVEL;
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