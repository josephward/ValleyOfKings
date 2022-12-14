#pragma once
#include <string>
using namespace std;

class Being {

	private:
		string name;	//Name of the being
		string type;	//Type of being (character, undead, boss, etc).
		int HP;			//Hit points of the being
		int baseDmg;	//Unmodified damage of the being
		int baseHeal;	//Unmodified healing factor of the being
		//vector<Action> actionlist; vector of possible extra actions that can be done

	public:
		//Constructor Function
		Being(string name, string type, int HP, int baseDmg, int baseHeal = 0);

		//Status values
		bool is_stunned = 0;
		bool is_ko = 0;
		bool is_mind_controlled = 0;
		int turn_order;
		int max_HP;

		//Combat Functions
		void takeDmg(int dmg);							//Receive damage function
		void beHealed(int heal);						//Be Healed function
		void std_attack(Being& target, int modifier);	//Basic attack
		void std_heal(Being& target, int modifier);		//Basic heal
		void print_info();								//Prints basic info for use in combat

		//Getters
		string get_name();
		int get_HP();
		

		// Setters
		void stun();
		void unstun();
		int set_turn_order(int order);
};

