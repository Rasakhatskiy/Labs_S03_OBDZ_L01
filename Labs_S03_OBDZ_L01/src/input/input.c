#include "input.h"

struct Team* readTeam()
{
    struct Team* team = malloc(sizeof(struct Team));

    printf("\nEnter team name (max %i symbols):\n", MAX_STRING_TITLE);
    strncpy(team->team_name, readString(MAX_STRING_TITLE), MAX_STRING_TITLE);

    printf("\nEnter country name (max %i symbols):\n", MAX_STRING_NAME);
    strncpy(team->country_name, readString(MAX_STRING_NAME), MAX_STRING_NAME);

    printf("\nEnter coach name (max %i symbols):\n", MAX_STRING_NAME);
    strncpy(team->coach_name, readString(MAX_STRING_NAME), MAX_STRING_NAME);

    printf("\nEnter status (max %i symbols):\n", MAX_STRING_SIZE);
    strncpy(team->status, readString(MAX_STRING_SIZE), MAX_STRING_SIZE);

    printf("\nEnter number of points :\n");
    team->points = readUInt32();

    return team;
}

struct Player* readPlayer()
{
    struct Player* player = malloc(sizeof(struct Player));

    printf("\nEnter player name (max %i symbols):\n", MAX_STRING_NAME);
    strncpy(player->player_name, readString(MAX_STRING_NAME), MAX_STRING_NAME);

    printf("\nEnter player number:\n");
    player->player_number = readUInt32();

    printf("\nEnter team id:\n");
    player->team_id = readUInt32();

    printf("\nEnter birthday (dd.mm.yyyy) (max %i symbols):\n", MAX_STRING_DATE);
    strncpy(player->birthday, readString(MAX_STRING_DATE), MAX_STRING_DATE);

    printf("\nEnter status (max %i symbols):\n", MAX_STRING_SIZE);
    strncpy(player->status, readString(MAX_STRING_SIZE), MAX_STRING_SIZE);

    printf("\nEnter gender (0/1) (female/male) :\n");
    player->gender = readUInt32();

    return player;
}

void editTeam(struct Team* team)
{
}

void editPlayer(struct Player* player)
{
}
