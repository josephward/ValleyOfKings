#pragma once
#include <string>
using namespace std;

//Class that models characters and allows them to take damage, heal damage, be stunned, set turn order, among other things. 
class Character {
	
	private:
		std::string name;	//Name of the Character
		int HP;				//The health that the character has
		int baseDmg;		//The Standard Damage the character does
		int baseHeal;		//The Standard Healing amount character does
		
		// vector<item> item_vector		- the inventory of the character, implementation to add items to characters
		// vector<bool> upgrade_vector	- the list of upgrades that the characters has unlocked. Corresponds to a list 


	public:
		//Constructor function
		Character(string name, int HP, int baseDmg, int baseHeal);
		
		//Character attributes
		int turn_order = 0;
		bool is_stunned = 0;
		bool is_ko = 0;

		//** General Functions **

		//Combat Functions
		void takeDmg(int Dmg);
		void healDmg(int heal_val);

		// Setters
		void change_HP(int new_HP);
		void change_baseDmg(int new_baseDmg);
		int set_unit_order(int order);
		void set_HP(int new_HP);

		// Getters
		string get_name();
		int get_HP();
		int std_attack();
		int std_heal();
		void stun();
		void unstun();
};