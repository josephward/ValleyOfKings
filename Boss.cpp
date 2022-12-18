#include "Boss.h"

Boss::Boss(const string name, const string type, int HP, int baseDmg, int baseHeal) :
	Being(name, "Boss", HP, baseDmg, baseHeal) {
	max_HP = HP;
}
