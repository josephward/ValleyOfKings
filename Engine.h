#pragma once
#include "Monster.h"
#include "Character.h"

//Mosnter Functions
shared_ptr<Monster> genMonster(int option);
void setupMonsterCombat(vector<shared_ptr<Monster>>& monstVect, int encounter);

//Character Functions
shared_ptr<Character> genCast();