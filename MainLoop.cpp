#include "GameState.h"
#include <iostream>
#include <chrono>
#include <thread>

using namespace std;
using namespace this_thread;
using namespace chrono;

//This program is the "main loop" for the game. Use this as an executionable to execute the game.
//Every other function should be called from here, aka this should have the only main function in the project.

//Function that conducts a skirmish with several different modes
void skirmish() {
	int sleep_val = 25; //Adjusts all the typing values to make things faster or slower.
	string intro1 = "\nWelcome to the Valley of Kings. You are a group of adventures in ancient Rome under the reign of Principe Augustus,\nexcavating for buried treasure in the old pharaoh's hidden tombs.\n\n";

	//Prints the intro1 string like its being typed
	int x = 0;
	while (intro1[x] != '\0') {
		std::cout << intro1[x];
		sleep_for(milliseconds(sleep_val + rand() % sleep_val));
		x++;
	}

	//Prints the game modes that the user can play
	cout << "Select which game mode you want to play" << endl;
	cout << "[1] Tutorial" << endl;
	cout << "[2] Easy" << endl;
	cout << "[3] Medium" << endl;
	cout << "[4] Impossible" << endl;

	//Ensure the response is an int
	int response = check_response();


	//If tutorial mode is selected print the information and generate the easy monster pode
	if (response == 1) {

		//Gives an introduction to the characters and some background about them.
		cout << "Here is some backstory about your adventurers. They each have different actions that you can choose to defeat the\nmonsters." << endl << endl;
		sleep_for(milliseconds(5000));
		cout << "Quintus is a veteran of the Roman Civil wars and Julius Caesar's Gaulic campaigns. After retiring from the military\nhe decided to found an adventuring group so he could keep getting his thrill fix." << endl << endl;
		cout << "Nysa is an acolyte of the Greek Eleusinian Mysteries, and is known to be favored of the gods.\nShe joined Quintus when he saw her call down lightning against a group of barbarians in Attacca." << endl << endl;
		cout << "Ganna is a Gaulic druid from one of the tribes of the Belgae. Quintus and Ganna are friends in\nspite of his service fighting her people, because he freed her from slavery." << endl << endl;
		cout << "Paltibaal is a doctor of the former city of Carthage that fell on hard times. Though he accepted the job\nfrom Quintus there is visible tension between them because of what the Romans did to Carthage." << endl << endl;

		//Break to let the user catch up in reading
		string continue1 = "empty";
		std::cout << "\nWhen you are ready, type: 'begin'.\n";
		cin >> continue1;
		std::cout << endl;

		//Gives instructions on how to play the game.
		cout << "------------------------------------------------------------------------------------------------------------------" << endl;
		cout << "How to play Valley of Kings" << endl;
		cout << "------------------------------------------------------------------------------------------------------------------" << endl;
		cout << "The game is conducted in a series of turns. The monsters get a turn first, then the player,\nalternating until either the monsters are destroyed or the player loses." << endl;
		cout << "You win if you are able to destroy all the monsters." << endl;
		cout << "Each time you play, the characters and monsters will be assigned a random turn order. When it is your turn, ";
		cout << "you will be given a selection of actions you can take based on what character is selected.\nTo select an action, type the number enclosed by brackets and hit 'enter'" << endl;
		cout << "\nHere is a summary of actions you can take. Look out for special actions that come from upgrades or new characters." << endl;
		cout << "\nStandard Actions:" << endl;
		cout << ">Attack - A basic move that will do 4 damage to an enemy you select.\n>Heal - Heals a character for usually 6 damage.\n>Stun - Any action that has this word in it will prevent a monster from attack for one round." << endl;
		cout << "\nSpecial Actions:" << endl;
		cout << ">Jupiter's Lightning - An attack by Nysa that will do 2 damage to all monsters.\n>Old Magic - An attack by Ganna that will cause the monster to suffer 8 damage but will stun Ganna for a turn." << endl;
		cout << "------------------------------------------------------------------------------------------------------------------" << endl;

		//Break to let the user catch up in reading
		string continue2 = "empty";
		std::cout << "\nWhen you are ready, type: 'continue'.\n";
		cin >> continue2;
		std::cout << endl;

		//Print the string like its being typed
		string intro2 = "\nYou have stumbled into a previously undiscovered tomb. Upon entering the sarcophagus room you are attacked!\n";
		x = 0;
		while (intro2[x] != '\0') {
			std::cout << intro2[x];
			sleep_for(milliseconds(sleep_val + rand() % sleep_val));
			x++;
		}

		//Initilize the characters, easy monsters and print them to the user.
		cout << "\nCharacter/Monster Name | Health Point Value\n" << endl;
		vector<Character> char_vect = init_cast();
		vector<Monster> monst_vect = gen_basic_squad_3();

		//Begin combat
		combat_turns(monst_vect, char_vect);
	}

	//Easy mode option
	else if (response == 2) {
		vector<Character> char_vect = init_cast();
		vector<Monster> monst_vect = gen_basic_squad_3();
		combat_turns(monst_vect, char_vect);
	}

	//Medium mode option
	else if (response == 3) {
		vector<Character> char_vect = init_cast();
		vector<Monster> monst_vect = gen_basic_squad_4();
		combat_turns(monst_vect, char_vect);
	}

	//Impossible mode option
	else {
		vector<Character> char_vect = init_cast();
		vector<Monster> monst_vect = gen_capt_squad_5();
		combat_turns(monst_vect, char_vect);
	}

}

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
	sleep_for(milliseconds(500));
}

//Main function for the program
int main() {
	title_art();
	srand(time(0)); //sets the seed for the random number generator
	skirmish();
	cout << "\nThank you for playing Valley of Kings. This was made by Eero Ward in November 2022. All rights reserved.";
	
	//End loop that keeps the program open so the user can review the game
	while (true) {
		sleep_for(milliseconds(10000));
	}
}
