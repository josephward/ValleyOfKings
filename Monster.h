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
		static void default_attack_AI(shared_ptr<Being> current_monst, shared_ptr<Being> target_Ptr, shared_ptr<Being> weak_target_Ptr);
		static void masterMonsterAI(shared_ptr<Being> current_monst, shared_ptr<Being> target_Ptr, shared_ptr<Being> weak_target_Ptr);

		//Other Functions
		vector<shared_ptr<Monster>> monsterVect = {};
};