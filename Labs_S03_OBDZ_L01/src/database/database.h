#ifndef DATABASE_H
#define DATABASE_H

#ifdef _WIN32
#define _CRT_SECURE_NO_DEPRECATE
#endif
#include <errno.h>
#include <stdio.h>
#include <string.h>

#define MAX_STRING_SIZE 256

//8b * 2048 = 16 kib
#define MAX_INDEX_PAGE_ENTRIES 2048

static const char PATH_TABLE_INDEX_TEAM[] =		"TEAM_INDEX.bin";
static const char PATH_TABLE_TEAM[] =			"TEAM_DATA.bin";
static const char PATH_TABLE_INDEX_PLAYER[] =	"PLAYER_INDEX.bin";
static const char PATH_TABLE_PLAYER[] =			"PLAYER_DATA.bin";




struct DataOffset
{
	unsigned int offset;
	unsigned int index;
};
	
struct DataOffset* indexPagePlayer;
unsigned int indexPagePlayerSize;
struct DataOffset* indexPageTeam;
unsigned int indexPageTeamSize;


struct Team
{
	unsigned int id;
	char team_name[MAX_STRING_SIZE];
	char country_name[MAX_STRING_SIZE];
	char coach_name[MAX_STRING_SIZE];
	char status[MAX_STRING_SIZE];
	unsigned int points;
};

struct Player 
{
	unsigned int id;
	unsigned int player_number;
	char player_name[MAX_STRING_SIZE];
	char birthday[MAX_STRING_SIZE];
	char gender;
	char status[MAX_STRING_SIZE];
};

void addRecord_Player(struct Player player);
void addRecord_Team(struct Team team);

void loadIndexPages();
void loadIndexPage(unsigned int page, struct DataOffset* indexPage, int* indexPageSize, char path[]);
void printIndexPage(struct DataOffset* indexPage, int indexPageSize);

#endif // !DATABASE_H


