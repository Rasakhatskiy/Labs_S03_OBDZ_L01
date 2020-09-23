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
    while (1)
    {
        player->team_id = readUInt32();
        if (isIndexTeamExists(player->team_id))
            break;
        else
            printf("Team id %i doesn't exists.\n", player->team_id);
    }


    printf("\nEnter birthday (dd.mm.yyyy) (max %i symbols):\n", MAX_STRING_DATE);
    strncpy(player->birthday, readString(MAX_STRING_DATE), MAX_STRING_DATE);

    printf("\nEnter status (max %i symbols):\n", MAX_STRING_SIZE);
    strncpy(player->status, readString(MAX_STRING_SIZE), MAX_STRING_SIZE);

    printf("\nEnter gender (0/1) (female/male) :\n");
    player->gender = readUInt32();

    return player;
}

void editTeam(unsigned int id)
{
    struct Team* team = get_m(id);
    if (!team) return;

    int result = 1;

    while (
        result >= 1 &&
        result <= 5)
    {
        printf(
            "\nEdit field:\n"
            "# 1 Name\n"
            "# 2 Country\n"
            "# 3 Coach\n"
            "# 4 Status\n"
            "# 5 Points\n"
            "# any other number to cancel.\n");

        result = readUInt32();

        switch (result)
        {
            case 1: 
                printf("\nEnter team name (max %i symbols):\n", MAX_STRING_TITLE);
                strncpy(team->team_name, readString(MAX_STRING_TITLE), MAX_STRING_TITLE);
                break;
            case 2:
                printf("\nEnter country name (max %i symbols):\n", MAX_STRING_NAME);
                strncpy(team->country_name, readString(MAX_STRING_NAME), MAX_STRING_NAME);
                break;
            case 3:
                printf("\nEnter coach name (max %i symbols):\n", MAX_STRING_NAME);
                strncpy(team->coach_name, readString(MAX_STRING_NAME), MAX_STRING_NAME);
                break;
            case 4:
                printf("\nEnter status (max %i symbols):\n", MAX_STRING_SIZE);
                strncpy(team->status, readString(MAX_STRING_SIZE), MAX_STRING_SIZE);
                break;
            case 5:
                printf("\nEnter number of points :\n");
                team->points = readUInt32();
                break;
            default:
                printf("\nCancelled.\n");
                break;
        }
    }
    update_m(team);
    free(team);
}

void editPlayer(unsigned int id)
{
    struct Player* player = get_s(id);
    if (!player) return;

    int result = 1;

    while (
        result >= 1 &&
        result <= 5)
    {
        printf(
            "\nEdit field:\n"
            "# 1 Name\n"
            "# 2 Number\n"
            "# 3 Team id\n"
            "# 4 Birthday\n"
            "# 5 Status\n"
            "# 6 Gender\n"
            "# any other number to cancel.\n");

        result = readUInt32();

        switch (result)
        {
            case 1:
                printf("\nEnter player name (max %i symbols):\n", MAX_STRING_NAME);
                strncpy(player->player_name, readString(MAX_STRING_NAME), MAX_STRING_NAME);
                break;
            case 2:
                printf("\nEnter player number:\n");
                player->player_number = readUInt32();
                break;
            case 3:
                printf("\nEnter team id:\n");
                while (1)
                {
                    player->team_id = readUInt32();
                    if (isIndexTeamExists(player->team_id))
                        break;
                    else
                        printf("Team id %i doesn't exists.\n", player->team_id);
                }
                break;
            case 4:
                printf("\nEnter birthday (dd.mm.yyyy) (max %i symbols):\n", MAX_STRING_DATE);
                strncpy(player->birthday, readString(MAX_STRING_DATE), MAX_STRING_DATE);
                break;
            case 5:
                printf("\nEnter status (max %i symbols):\n", MAX_STRING_SIZE);
                strncpy(player->status, readString(MAX_STRING_SIZE), MAX_STRING_SIZE);
                break;
            case 6:
                printf("\nEnter gender (0/1) (female/male) :\n");
                player->gender = readUInt32();
                break;
            default:
                printf("\nCancelled.\n");
                break;
        }
    }
    update_s(player);
    free(player);
}

void function_insert_m()
{
    system("CLS");
    struct Team* team = readTeam();
    insert_m(team);
    free(team);
    wait();
}

void function_insert_s()
{
    system("CLS");
    struct Player* player = readPlayer();
    insert_s(player);
    free(player);
    wait();
}

void function_get_m()
{
    system("CLS");
    printf("Enter team id\n");
    unsigned int id = readUInt32();
    struct Team* team = get_m(id);
    if (team) 
        printTeam(team);
    free(team);
    wait();
}

void function_get_s()
{
    system("CLS");
    printf("Enter player id\n");
    unsigned int id = readUInt32();
    struct Player* player = get_s(id);
    if (player)
        printPlayer(player);
    free(player);
    wait();
}

void function_update_m()
{
    system("CLS");
    printf("Enter team id\n");
    unsigned int id = readUInt32();
    editTeam(id);
    wait();
}

void function_update_s()
{
    system("CLS");
    printf("Enter player id\n");
    unsigned int id = readUInt32();
    editPlayer(id);
    wait();
}

void function_delete_m()
{
    system("CLS");
    printf("Enter team id\n");
    unsigned int id = readUInt32();
    delete_m(id);
    wait();
}

void function_delete_s()
{
    system("CLS");
    printf("Enter player id\n");
    unsigned int id = readUInt32();
    delete_s(id);
    wait();
}


void function_printAll_m()
{
    for (int i = 0; i < sizeDataOffsetsTeam; ++i)
    {
        struct Team* team = get_m(dataOffsetsTeam[i].index);
        if (team) 
            printTeam(team);
        free(team);
    }
    wait();
}

void function_printAll_s()
{
    for (int i = 0; i < sizeDataOffsetsPlayer; ++i)
    {
        struct Player* player = get_s(dataOffsetsPlayer[i].index);
        if (player) 
            printPlayer(player);
        free(player);
    }
    wait();
}

void function_count()
{
    system("CLS");
    printf("Number of teams : %i\n", sizeDataOffsetsTeam);
    for (int i = 0; i < sizeDataOffsetsTeam; ++i)
    {
        int count = 0;
        struct Team* team = get_m(dataOffsetsTeam[i].index);
        for (int j = 0; j < sizeDataOffsetsPlayer; ++j)
        {
            struct Player* player = get_s(dataOffsetsPlayer[j].index);
            if (player->team_id == team->id)
                ++count;
            free(player);
        }
        free(team);
        printf("Team %i has %i players.\n", dataOffsetsTeam[i].index, count);
    }
    wait();
}

void wait()
{
    printf("\nPress any key to continue...\n");
    _getch();
}
