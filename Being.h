#pragma once
#include <string>
#include <vector>
#include <memory>
using namespace std;

class Being {

	private:
		const string name;	//Name of the being
		const string type;	//Type of being (character, undead, boss, etc).
		int HP;				//Hit points of the being
		int baseDmg;		//Unmodified damage of the being
		int baseHeal;		//Unmodified healing factor of the being


	public:

		//Status values
		bool is_stunned = 0;
		bool is_ko = 0;
		bool is_mind_controlled = 0;
		int max_HP = 0;

		//Constructor Function
		Being(const string name, const string type, int HP, int baseDmg, int baseHeal = 0);

		//Combat Functions
		void takeDmg(int dmg);								//Receive damage function
		void beHealed(int heal);							//Be Healed function
		void std_attack(Being& target, int modifier = 0);	//Basic attack
		void std_heal(Being& target, int modifier = 0);		//Basic heal
		void print_info();									//Prints basic info for use in combat

		//Getters
		string get_name();
		string get_type();
		int get_HP();
		int get_Dmg();
		int get_HealingFactor();
		
		// Setters
		void stun();
		void unstun();
};

