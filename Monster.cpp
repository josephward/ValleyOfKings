#include <iostream>
#include "Monster.h"

//Class constructor function
Monster::Monster(string m_name, int m_HP, int m_baseDmg) {
	name = m_name;			//Name
	HP = m_HP;				//Health Point 
	baseDmg = m_baseDmg;	//Damage w/o modifiers 
	turn_order = 0;			//the turn order
	is_stunned = 0;			//var if stunned or not
}

//Function models taking damage
//If the monster has HP > 0, print that they have taken damage and have HP left
//If they have HP <= 0, print they died and set the HP to 0.
void Monster::takeDmg(int Dmg) {
	HP -= Dmg;
	cout << name << " has taken " << Dmg << " damage! ";
	if (HP > 0) {
		cout << " It has " << HP << " health left." << endl;
	}
	else {
		cout << " " << name << " died!" << endl;
		HP = 0;
	}
}

//Getter function for the name
string Monster::get_name(){
	return name;
}

//Getter function for the HP 
int Monster::get_HP(){
	return HP;
}

//Setter function for the turn order
int Monster::set_unit_order(int order) {
	turn_order = order;
	return turn_order;
}

//Getter function for the standard attack value
int Monster::std_attack() {
	return baseDmg;
}

//Setter function to stunned
void  Monster::stun() {
	is_stunned = 1;
}

//Setter function to not stunned
void Monster::unstun_monster() {
	is_stunned = 0;
}