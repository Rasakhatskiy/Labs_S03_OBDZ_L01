#ifndef INPUT_H
#define INPUT_H

#ifdef _WIN32
#define _CRT_SECURE_NO_DEPRECATE
#endif

#include "../database/database.h"
#include "../input/validator.h"

// Enter Team from console
struct Team* readTeam();

//Enter player from console
struct Player* readPlayer();

//edit team object from console
void editTeam(unsigned int id);

//edit player object from console
void editPlayer(unsigned int id);

void function_insert_m();
void function_insert_s();
void function_get_m();
void function_get_s();
void function_update_m();
void function_update_s();
void function_delete_m();
void function_delete_s();

void function_printAll_m();
void function_printAll_s();

void function_count();

void wait();
#endif // !INPUT_H

