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
void editPlayer(struct Player* player);


#endif // !INPUT_H

