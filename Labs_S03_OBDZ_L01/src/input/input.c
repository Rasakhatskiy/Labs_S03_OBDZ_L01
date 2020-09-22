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
            printf("Team id %i doesn't exists.\n");
    }


    printf("\nEnter birthday (dd.mm.yyyy) (max %i symbols):\n", MAX_STRING_DATE);
    strncpy(player->birthday, readString(MAX_STRING_DATE), MAX_STRING_DATE);

    printf("\nEnter status (max %i symbols):\n", MAX_STRING_SIZE);
    strncpy(player->status, readString(MAX_STRING_SIZE), MAX_STRING_SIZE);

    printf("\nEnter gender (0/1) (female/male) :\n");
    player->gender = readUInt32();

    return player;
}


/*
struct Team
{
    unsigned int id;
    char team_name[MAX_STRING_TITLE];		//1
    char country_name[MAX_STRING_COUNTRY];	//2
    char coach_name[MAX_STRING_NAME];		//3
    char status[MAX_STRING_SIZE];			//4
    unsigned int points;					//5
};

struct Player
{
    unsigned int id;
    unsigned int player_number;				//1
    unsigned int team_id;					//2
    char player_name[MAX_STRING_NAME];		//3
    char birthday[MAX_STRING_DATE];			//4
    char gender;							//5
    char status[MAX_STRING_SIZE];			//6
};
*/

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
