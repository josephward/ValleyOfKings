#pragma once
#include <string>
using namespace std;

class Being {

	private:
		string name;	//Name of the being
		int HP;			//Hit points of the being
		int baseDmg;	//Unmodified damage of the being
		int baseHeal;	//Unmodified healing factor of the being
		string type;	//Type of being (character, undead, boss, etc).
		//vector<Action> actionlist; vector of possible extra actions that can be done

	public:
		//Constructor Function
		Being(string name, string type, int HP, int baseDmg, int baseHeal = 0);

		//Status values
		int turn_order = 0;
		bool is_stunned = 0;
		bool is_ko = 0;

		//Combat Functions
		void takeDmg(int dmg);	//Receive damage function
		int std_attack();		//Basic attack
		int std_heal();			//Basic heal

		//Getters
		string get_name();
		int get_HP();

		// Setters
		void stun();
		void unstun();
		int set_being_order(int order);
};

