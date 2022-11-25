#pragma once
#include <vector>
#include "Character.h"
#include "Monster.h"

//General Functions
bool check_vectors(vector<Character> vect);
bool check_vectors(vector<Monster> vect);
void set_turn_order(vector<Monster>& monster_turn_order, vector<Monster> monst_vect, vector<Character>& char_turn_order, vector<Character> char_vect, int set_mode);
int check_response();
bool fin_combat(vector<Monster> monster_turn_order, vector<Character> cast_turn_order);

//Monster Combat Functions
void attack_cast(Character& target, Monster current_monst, int Dmg_Modifier);
void stun_cast(Character& target, Monster current_monst);

//Character Combat Functions
void attack_monsters(Character current_cast, vector<Monster>& monster_turn_order, int dmg_mod = 0);
void stun_monsters(vector<Monster>& monster_turn_order);
void heal_cast(Character current_cast, vector<Character>& cast_turn_order);

//Print Functions
void print_units(vector<Monster> input_vect);
void print_units(vector<Character> input_vect);
void print_monsters(vector<Monster> monster_turn_order);
void print_cast(vector<Character> cast_turn_order);
void print_combat_cast(vector<Character> cast_turn_order, vector<Character> cast);

//Main Combat Functions
void monster_turn(vector<Monster>& monst_turn_order, vector<Character>& cast_turn_order);
void cast_turn(vector<Monster>& monster_turn_order, vector<Character>& cast_turn_order, vector<Character> cast_vect);
void combat_turns(vector<Monster>& monst_vect, vector<Character>& char_vect);

//Generation Functions
vector<Character> init_cast();
vector<Monster> gen_basic_squad_3();
vector<Monster> gen_basic_squad_4();
vector<Monster> gen_capt_squad_5();