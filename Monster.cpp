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

//Function that conducts the basic attack options. 
//This is a template of sorts that each monster will modify for their own AI.
//Currect setup gives a roughly 40% chance to hit the weakest character and 20% to all other characters
void Monster::default_attack_AI(shared_ptr<Being> current_monst, shared_ptr<Being> target_Ptr, shared_ptr<Being> weak_target_Ptr) {
	
	//Choose a random option
	int attack_select = rand() % 5;

	//Execute attack option
	if (attack_select == 0) { // Light random attack
		cout << current_monst->get_name() << " attacks " << target_Ptr->get_name() << "!\n";
		current_monst->std_attack(target_Ptr, 0);
	}
	else if (attack_select == 1) { // Light random attack
		cout << current_monst->get_name() << " attacks " << target_Ptr->get_name() << "!\n";
		current_monst->std_attack(target_Ptr, 0);
	}
	else if (attack_select == 2) { // Heavy random attack
		cout << current_monst->get_name() << " attacks " << target_Ptr->get_name() << "!\n";
		current_monst->std_attack(target_Ptr, 2);
	}
	else if (attack_select == 3) { // Light target weakest attack
		cout << current_monst->get_name() << " attacks " << weak_target_Ptr->get_name() << "!\n";
		current_monst->std_attack(weak_target_Ptr, 0);
	}
	else if (attack_select == 4) { // Random stun attack
		cout << current_monst->get_name() << " stuns " << target_Ptr->get_name() << "!\n";
		target_Ptr->stun();
	}	
}

//TODO: Create default_attack_AI version that you can preselect attack option

//Function that governs the monster's choices during their attack phase
void Monster::masterMonsterAI(shared_ptr<Being> current_monst, shared_ptr<Being> target_Ptr, shared_ptr<Being> weak_target_Ptr) {

	string monst_name = current_monst->get_name();
		
	//AI governing Monster
	if (monst_name == "Monster") {
		default_attack_AI(current_monst, target_Ptr, weak_target_Ptr);
	}
	//AI governing Undead Warrior
	else if (monst_name == "Undead Warrior") {
		default_attack_AI(current_monst, target_Ptr, weak_target_Ptr);
	}
	//AI governing Undead Captain
	else if (monst_name == "Undead Captain") {
		default_attack_AI(current_monst, target_Ptr, weak_target_Ptr);
	}
	//AI governing Nomarch
	else if (monst_name == "Nomarch") {
		default_attack_AI(current_monst, target_Ptr, weak_target_Ptr);
	}
	//AI governing Sphinx
	else if (monst_name == "Sphinx") {
		default_attack_AI(current_monst, target_Ptr, weak_target_Ptr);
	}
	//AI governing Mummy
	else if (monst_name == "Mummy") {
		std::cout << "Error: there is no default attack AI for this Mummy.\n";
	}
	//AI governing Nubian Horse-Archer
	else if (monst_name == "Nubian Horse-Archer") {
		std::cout << "Error: there is no default attack AI for this Horse-Archer.\n";
	}
	//AI governing Nubian Raider
	else if (monst_name == "Nubian Raider") {
		std::cout << "Error: there is no default attack AI for this Raider.\n";
	}
	//AI governing Egyptian Grave Robber
	else if (monst_name == "Egyptian Grave Robber") {
		std::cout << "Error: there is no default attack AI for this Grave Robber.\n";
	}
	//AI governing Egyptian Robber Baron
	else if (monst_name == "Egyptian Robber Baron") {
		std::cout << "Error: there is no default attack AI for this Robber Baron.\n";
	}

	else {
		std::cout << "Error: invalid monster name for monster object.\n";
	}
}