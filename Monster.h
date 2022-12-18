#pragma once
#include "Being.h"

class Monster : public Being {

	public:
		Monster(const string name, const string type, int HP, int baseDmg, int baseHeal = 0);
};