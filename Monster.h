#pragma once
#include <map>
#include "Being.h"
#include "Character.h"

//Class that both generates monster objects, and handles the vector of pointers of monsters.
class Monster : public Being {

	public:
		//Constructor
		Monster(const string name, const string type, int HP, int baseDmg, int baseHeal = 0);
		
		//Combat Functions
		void command_the_dead(vector<shared_ptr<Being>>& monstVect); //Nomarch Action
		void stun_character(shared_ptr<Character> target); //Sphinx/Hippo Action
		static void masterMonsterAI(shared_ptr<Monster> current_turn, int option);

		//Other Functions
		shared_ptr<Monster> genMonster(int option);
		vector<shared_ptr<Monster>> monsterVect = {};
};