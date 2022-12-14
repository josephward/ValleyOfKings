#pragma once
#define NOMINMAX
#include <fstream>
#include <iostream>
#include <chrono>
#include <thread>
#include <Windows.h>
#include "Monster.h"
#include "Character.h"
#include "Boss.h"
#undef NOMINMAX

using namespace this_thread;
using namespace chrono;
using namespace std;

//Game Engine Vectors
extern vector<shared_ptr<Being>> turn_order_vect;
extern vector<shared_ptr<Being>> characterVect;
extern vector<string> filenames;
extern vector<string> itemvect; //TODO: Add the Item class in

//General Functions
void title_art();
int checkVect(vector<int> vect);
int verify_input(int lower, int upper);
void clearscreen();

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