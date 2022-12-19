#include "Generators.h"

//--------------------------------------Monster Functions--------------------------------------

//Function that provides a succinct way to generate monsters
shared_ptr<Monster> genMonster(int option) {
	switch (option) {
	case 1: {
		Monster newMonst = Monster("Undead Warrior", "Undead", 8, 2);
		auto ptr = make_shared<Monster>(newMonst);
		return ptr;
	}
	case 2: {
		Monster newMonst = Monster("Undead Captain", "Undead", 8, 4);
		auto ptr = make_shared<Monster>(newMonst);
		return ptr;
	}
	case 3: {
		Monster newMonst = Monster("Nomarch", "Undead", 10, 4);
		auto ptr = make_shared<Monster>(newMonst);
		return ptr;
	}
	case 4: {
		Monster newMonst = Monster("Sphinx", "Creature", 12, 4);
		auto ptr = make_shared<Monster>(newMonst);
		return ptr;
	}
	case 5:
		Monster newMonst = Monster("Mummy", "Undead", 0, 0);
		auto ptr = make_shared<Monster>(newMonst);
		return ptr;
	}
}

//Function that is a switch statement for each of the encounters of the game
void setupMonsterCombat(vector<shared_ptr<Monster>>& monstVect, int encounter) {
	switch (encounter) {
		//Level 1
	case 1: {
		//3 Undead Warriors
		monstVect.push_back(genMonster(1));
		monstVect.push_back(genMonster(1));
		monstVect.push_back(genMonster(1));
	}
	case 2: {
		//3 Undead Warriors and a Captain
		monstVect.push_back(genMonster(1));
		monstVect.push_back(genMonster(1));
		monstVect.push_back(genMonster(1));
		monstVect.push_back(genMonster(2));
	}

		  //Level 2
	case 3: {
		//Sphinx and Undead Warrior
		monstVect.push_back(genMonster(4));
		monstVect.push_back(genMonster(1));
	}
	case 4: {
		//Sphinx, Captain, and 2 Undead Warriors
		monstVect.push_back(genMonster(4));
		monstVect.push_back(genMonster(2));
		monstVect.push_back(genMonster(1));
		monstVect.push_back(genMonster(1));
	}
	case 5: {
		//Nomarch, 2 Captains, and 2 Mummies
		monstVect.push_back(genMonster(3));
		monstVect.push_back(genMonster(2));
		monstVect.push_back(genMonster(2));
		monstVect.push_back(genMonster(2));
		monstVect.push_back(genMonster(5));
		monstVect.push_back(genMonster(5));
	}

		  //Boss Level
	}
}

//--------------------------------------Character Functions--------------------------------------

shared_ptr<Character> genCast() {

}

//--------------------------------------Boss Functions--------------------------------------