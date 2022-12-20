#pragma once
#include <fstream>
#include <iostream>
#include "Monster.h"
#include "Character.h"
#include "Boss.h"

//Game Engine Vectors
vector<shared_ptr<Being>> turn_order_vect = {};
vector<shared_ptr<Being>> characterVect = {};
vector<string> filenames = ("Save_File_1.txt", "Save_File_2.txt", "Save_File_3.txt");
vector<string> itemvect{}; //TODO: Add the Item class in

//General Functions
void title_art();
int checkVect(vector<int> vect);
int verify_input(int lower, int upper);

//Boss Functions
shared_ptr<Being> genBoss(int option);

//Monster Functions
shared_ptr<Being> genMonster(int option);
void setupMonsterCombat(vector<shared_ptr<Monster>>& monstVect, int encounter);

//Character Functions
shared_ptr<Being> genCast(vector<vector<int>>& upgradeMatrix);

//Saving/Loading Functions
void load_game(int savefile);
void save_game(int savefile);
void new_game(int savefile, int difficulty_level = 0);