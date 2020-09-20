#ifndef DATABASE_H
#define DATABASE_H

#ifdef _WIN32
#define _CRT_SECURE_NO_DEPRECATE
#endif
#include <errno.h>
#include <stdio.h>
#include <string.h>

#define MAX_STRING_TITLE 128
#define MAX_STRING_COUNTRY 32
#define MAX_STRING_NAME 32
#define MAX_STRING_DATE 11
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
unsigned int sizeIndexPagePlayer;

struct DataOffset* indexPageTeam;
unsigned int sizeIndexPageTeam;

struct Team
{
	unsigned int id;
	char team_name[MAX_STRING_TITLE];
	char country_name[MAX_STRING_COUNTRY];
	char coach_name[MAX_STRING_NAME];
	char status[MAX_STRING_SIZE];
	unsigned int points;
};

struct Player 
{
	unsigned int id;
	unsigned int player_number;
	char player_name[MAX_STRING_NAME];
	char birthday[MAX_STRING_DATE];
	char gender;
	char status[MAX_STRING_SIZE];
};

void addRecord_Player(struct Player player);
void addRecord_Team(struct Team* team);

//allocates memory and reads index pages for tables
void loadIndexFiles();

//loads page of index-offset table
void loadIndexFile(struct DataOffset* indexPage, int* indexPageSize, char path[]);

//prints loaded to memory index-offset table
void printIndexPage(struct DataOffset* indexPage, int indexPageSize);

//reads master element(Team) by id
struct Team* get_m(unsigned int id);

//adds new team to data base
void insert_m(struct Team* team);

//reads team in data file by offset
struct Team* readTeamByOffset(unsigned int offset);

//prints team on screen
void printTeam(struct Team* team);

//writes index-offset table from memory to file
void updateIndexFileTeam();

//writes index-offset table from memory to file
void updateIndexFilePlayer();

#endif // !DATABASE_H


