#include "Being.h"

//Constructor Function for Being
Being::Being(string b_name, string b_type, int b_HP, int b_baseDmg, int b_baseHeal) {
	name = b_name;
	type = b_type;
	HP = b_HP;
	baseDmg = b_baseDmg;
	baseHeal = b_baseHeal;
}

