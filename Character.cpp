#include "Character.h"
#include <iostream>
using namespace std;

//Constructor Function w/ initial values
Character::Character(string ch_name, int ch_HP, int ch_baseDmg, int ch_baseHeal) {
	//Character Attributes
	name = ch_name;
	HP = ch_HP;
	baseDmg = ch_baseDmg;
	baseHeal = ch_baseHeal;
	//Character Status Switches
	turn_order = 0; //Used to generate the turn order vector
	is_stunned = 0; //Status if the character is stunned
	is_ko = 0;		//Status if the character is unconscious

}

//Function that is used in combat give damage to the Character
//If the damage leads to HP above 0, just change the HP and output the info
//If the damage leads to HP at or below 0, turn the character into unconscious
void Character::takeDmg(int Dmg){
	//Character's HP is what it was minus the taken damage
	int new_HP = HP - Dmg;
	set_HP(new_HP);
	if (HP > 0) {
		cout << name << " has taken " << Dmg << " damage! Their health is now " << HP << endl;
	}
	//If HP goes to 0 or below the character becomes unconscious.
	else {
		is_ko = 1;
		cout << name << " has become unconscious. Heal them or defeat the rest of the enemies for them to revive!" << endl;
		HP = 0;
	}
}

//Returns the baseDmg, used in attack functions
int Character::std_attack() {
	return baseDmg;
}

//Method to heal character
void Character::healDmg(int heal_val) {
	Character::set_HP(HP+heal_val);
	cout << name << " has been healed for " << heal_val << " damage! Their health is now " << HP << endl;
}

//Returns healing factor of unit, used in healing function
int Character::std_heal() {
	return baseHeal;
}

//Setter method for health points
//Used in take damage functions
void Character::change_HP(int new_HP){	
	HP += new_HP;
}

//Setter method for health points
//Used to set the HP to a specific value 
void Character::set_HP(int new_HP) {
	HP = new_HP;
}

//Getter method for HP
int Character::get_HP() {
	return HP;
}

//Setter method for the value baseDmg (in case of upgrades).
void Character::change_baseDmg(int new_baseDmg){
	baseDmg = new_baseDmg;
}

//Getter method for the name of the character
string Character::get_name(){
	return name;
}

//Setter method for character turn order
int Character::set_unit_order(int order) {
	turn_order = order;
	return turn_order;
}

//Sets the character as stunned, 
//combat function changes this after a turn.
void Character::stun() {
	is_stunned = 1;
}

//Sets the character as unstunned
void Character::unstun() {
	is_stunned = 0;
}