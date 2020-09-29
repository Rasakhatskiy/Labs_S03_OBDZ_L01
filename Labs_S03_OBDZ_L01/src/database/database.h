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
#define MAX_STRING_DATE 12
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
	
struct DataOffset* dataOffsetsPlayer;
unsigned int sizeDataOffsetsPlayer;
unsigned int maxIndexPlayer;

struct DataOffset* dataOffsetsTeam;
unsigned int sizeDataOffsetsTeam;
unsigned int maxIndexTeam;




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

//allocates memory and reads index pages for tables
void loadIndexFiles();

//loads page of index-offset table
//calculatex maximum index for future assign new elements
void loadIndexFile(struct DataOffset* indexPage, int* indexPageSize, char path[], unsigned int* maxIndex);

//prints loaded to memory index-offset table
void printIndexPage(struct DataOffset* indexPage, int indexPageSize);

//deletes element from index table
void deleteElement(struct DataOffset* dataOffsets, unsigned int* size, int index);

//rewrites database to avoid empty zones
void clearTrash();




//adds new team to data base
void insert_m(struct Team* team);

//allows to edit database entry
void update_m(struct Team* team);

//reads master element(Team) by id
struct Team* get_m(unsigned int id);

//deletes master element from database and his slave elements
void delete_m(unsigned int id);

//reads team in data file by offset
struct Team* readTeamByOffset(unsigned int offset);

// prints team on screen
void printTeam(struct Team* team);

// checks if team with given index exists
int isIndexTeamExists(int index);



// adds new player to database
void insert_s(struct Player* player); 

//allows to edit database entry
void update_s(struct Player* player);

//deletes slave element from database
void delete_s(unsigned int id);

// checks if player with given index exists
int isIndexPlayerExists(int index);

//reads slave element(Player) by id
struct Player* get_s(unsigned int id);

//reads player in data file by offset
struct Player* readPlayerByOffset(unsigned int offset);

void printPlayer(struct Player* player);





// writes index-offset table from memory to file
void updateIndexFileTeam();

// writes index-offset table from memory to file
void updateIndexFilePlayer();

long getFileSize(char path[]);



#endif // !DATABASE_H


