#pragma once
#include "Being.h"

class Character : public Being {
	public:
		//Class Vector
		vector<string> Items = {};

		//Constructor
		Character(const string ch_name, const string ch_type, int ch_HP, int ch_baseDmg, int ch_baseHeal = 0);

		//Other Functions
};