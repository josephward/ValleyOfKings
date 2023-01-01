#include "Monster.h"

//Constructor Function for Monster
Monster::Monster(const string name, const string type, int HP, int baseDmg, int baseHeal) :
	Being(name, type, HP, baseDmg, baseHeal) {
	max_HP = HP;
}

//Special Action for the Nomarch
void Monster::command_the_dead(vector<shared_ptr<Being>>& monstVect) {
	//Looks through the monstVect for the first thing that has zero hitpoints
	for (int i = 0; i < monstVect.size(); i++) {
		int HP_val = monstVect[i]->get_HP();

		//Once it finds a monster w/ zero hitpoints, it changes it
		if (HP_val == 0) {
			Monster temp = Monster("Undead Warrior", "Undead", 8, 2);
			auto ptr = make_shared<Monster>(temp);
			//monstVect[i] = nullptr; //Deconstructs the original object
			monstVect[i] = ptr;
		}
	}
}

//Special Action for the Sphinx and Hippo
void Monster::stun_character(shared_ptr<Character> target) {
	target->stun();
}

//Function that governs the monster's choices during their attack phase
static void masterMonsterAI(shared_ptr<Monster> current_turn, int option) {
	//Creates a map with each monster to call the related AI functions
	map<string, int> monsterMap;
	//Low Level Monsters
	monsterMap.insert({ "Undead Warrior", 1 });
	monsterMap.insert({ "Undead Captain", 2 });
	monsterMap.insert({ "Nomarch", 3 });
	monsterMap.insert({ "Sphinx", 4 });
	monsterMap.insert({ "Mummy", 5 });

	//Night Raiders
	monsterMap.insert({ "Nubian Horse-Archer", 6});
	monsterMap.insert({ "Nubian Raider", 7 });
	monsterMap.insert({ "Egyptian Grave Robber", 8 });
	monsterMap.insert({ "Egyptian Robber Baron", 9 });

	switch (monsterMap.at(current_turn->get_name())) {
		//AI governing Undead Warrior
		case 1: {
			
		}
		//AI governing Undead Captain
		case 2: {

		}
		//AI governing Nomarch
		case 3: {

		}
		//AI governing Sphinx
		case 4: {

		}
		//AI governing Mummy
		case 5: {

		}
		//AI governing Nubian Horse-Archer
		case 6: {

		}
		//AI governing Nubian Raider
		case 7: {

		}
		//AI governing Egyptian Grave Robber
		case 8: {

		}
		//AI governing Egyptian Robber Baron
		case 9: {

		}
	}
}