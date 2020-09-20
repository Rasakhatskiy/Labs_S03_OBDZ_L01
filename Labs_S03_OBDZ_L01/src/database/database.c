#include "database.h"

void addRecord_Player(struct Player player)
{
	FILE* write_ptr;
    write_ptr = fopen(PATH_TABLE_TEAM, "wb");
    fwrite(&player, sizeof(struct Player), 1, write_ptr);
    fclose(write_ptr);

	
}

void loadIndexPages()
{
    indexPagePlayer = malloc(MAX_INDEX_PAGE_ENTRIES * sizeof(struct DataOffset));
    indexPageTeam = malloc(MAX_INDEX_PAGE_ENTRIES * sizeof(struct DataOffset));

    loadIndexPage(
        0, 
        indexPagePlayer, 
        &indexPagePlayerSize, 
        PATH_TABLE_INDEX_PLAYER);

    loadIndexPage(
        0, 
        indexPageTeam, 
        &indexPageTeamSize, 
        PATH_TABLE_INDEX_TEAM);
}

void loadIndexPage(unsigned int page, struct DataOffset* indexPage, int *indexPageSize, char path[])
{
    FILE* file = fopen(path, "rb");

    if (!file)
    {
        printf("File %s not found.\n", path);
        return;
    }

    fseek(file, page * MAX_INDEX_PAGE_ENTRIES * sizeof(struct DataOffset), 0);
    *indexPageSize = -1;

    while (fread(
        &indexPage[++(*indexPageSize)], 
        sizeof(struct DataOffset), 
        1, 
        file));

    if (feof(file))
        printf("End of file %s reached.\n", path);
    else
        printf("Failed to read %s file.\n", path);
}

void printIndexPage(struct DataOffset* indexPage, int indexPageSize)
{
    for (int i = 0; i < indexPageSize; ++i)
        printf("index: %i\toffset:%i\n", indexPage[i].index, indexPage[i].offset);
}

