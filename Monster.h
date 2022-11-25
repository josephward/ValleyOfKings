#pragma once
#include <string>
using namespace std;

//Class the models the monsters. Allows them to get object attributes, be stunned, take and give damage, ect.
class Monster {

	private:
		//Monster variables
		string name;	// Name of Monster, 
		int HP;			// Health Points
		int baseDmg;	// Damage w/o modifiers
		

	public:
		//Contructor Function
		Monster(string name, int HP, int baseDmg);

		//Stat values
		int turn_order = 0;
		bool is_stunned = 0;
		
		//Combat Functions
		void takeDmg(int Dmg);
		int std_attack();

		// Getters
		string get_name();
		int get_HP();

		// Setters
		void stun();
		void unstun_monster();
		int set_unit_order(int order);
};