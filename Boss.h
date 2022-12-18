#pragma once
#include "Being.h"

class Boss : public Being {

public:
	Boss(const string name, const string type, int HP, int baseDmg, int baseHeal = 0);
};

