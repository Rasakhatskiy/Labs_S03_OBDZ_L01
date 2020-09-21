#ifndef INPUT_H
#define INPUT_H

#ifdef _WIN32
#define _CRT_SECURE_NO_DEPRECATE
#endif

#include "../database/database.h"

// Enter Team from console
struct Team* readTeam();

#endif // !INPUT_H

