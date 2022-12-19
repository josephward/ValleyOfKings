#include "Character.h"

Character::Character(const string name, const string type, int HP, int baseDmg, int baseHeal) :
	Being(name, "Character", HP, baseDmg, baseHeal) {
	max_HP = HP;
}