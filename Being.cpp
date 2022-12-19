#include <iostream>
#include "Being.h"

//Constructor Function for Being
Being::Being(const string b_name, const string b_type, int b_HP, int b_baseDmg, int b_baseHeal):
	name(b_name), type(b_type), HP(b_HP), baseDmg(b_baseDmg), baseHeal(b_baseHeal){
	max_HP = HP;
}

//Combat Functions

//Attack Function
void Being::takeDmg(int dmg) {
	//TODO: put in the couts based on what kind of being is receiving damage.
	HP -= dmg;
	cout << name << " had taken " << dmg << " damage! They now have " << HP << " health!" << endl;

	/*
	* Possible path forward for the damage function
	if (HP < 0) {
		is_ko = 1;
		if (a user character) {
			cout << name << " has collapsed! End the fight or heal them for them to recover!" << endl;
		}
		if else(a boss) {
			cout << name << " has been banished!" << endl;
		}
		else {
			cout << name << " has been vanquished!" << endl;
		}
	}
	*/
}

//Healing function 
void Being::beHealed(int heal) {
	//Catch an instant where a being would be healed for more hit points then they started with
	if (max_HP-HP < heal) {
		HP = max_HP;
		cout << name << " has been healed for " << max_HP - HP << ".";
		cout << " Their Health is now " << HP << "!" << endl;
	}
	else {
		HP += heal;
		cout << name << " has been healed for " << heal << ".";
		cout << " Their Health is now " << HP << "!" << endl;
	}
}

//Calls the attack function for the standard amount
void Being::std_attack(Being& target, int modifier) {
	target.takeDmg(baseDmg + modifier);
}

//Calls the healing function for the standard amount
void  Being::std_heal(Being& target, int modifier) {
	target.beHealed(baseHeal + modifier);
}

//Getters
int Being::get_HP() {
	return HP;
}

string Being::get_name() {
	return name;
}

//Prints the basic information about the being to aid user in combat
void Being::print_info() {
	string status;
	if (is_ko == 1) {
		status = "defeated";
	}
	else if (is_mind_controlled == 1) {
		status = "mind controlled";
	}
	else if (is_stunned == 1) {
		status = "stunned";
	}
	cout << name << "   HP " << HP << "/" << max_HP << " " << status << endl;
}

//Setters

//Stuns the being
void Being::stun() {
	is_stunned = 1;
}

//Unstuns the being
void Being::unstun() {
	is_stunned = 0;
}