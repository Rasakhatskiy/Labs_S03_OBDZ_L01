#include "database.h"

void addRecord_Player(struct Player player)
{
	FILE* write_ptr;
    write_ptr = fopen(PATH_TABLE_TEAM, "wb");
    fwrite(&player, sizeof(struct Player), 1, write_ptr);
    fclose(write_ptr);

	
}

void addRecord_Team(struct Team* team)
{
    FILE* write_ptr;
    write_ptr = fopen(PATH_TABLE_TEAM, "wb");
    fwrite(team, sizeof(struct Team), 1, write_ptr);
    fclose(write_ptr);
}

void loadIndexFiles()
{
    dataOffsetsPlayer = malloc(MAX_INDEX_PAGE_ENTRIES * sizeof(struct DataOffset));
    dataOffsetsTeam = malloc(MAX_INDEX_PAGE_ENTRIES * sizeof(struct DataOffset));

    loadIndexFile(
        dataOffsetsPlayer, 
        &sizeDataOffsetsPlayer, 
        PATH_TABLE_INDEX_PLAYER);

    loadIndexFile(
        dataOffsetsTeam, 
        &sizeDataOffsetsTeam, 
        PATH_TABLE_INDEX_TEAM);
}

void loadIndexFile(struct DataOffset* dataOffsets, int *sizeDataOffsets, char path[])
{
    FILE* file = fopen(path, "rb");

    if (!file)
    {
        printf("File %s not found.\n", path);
        return;
    }

    //reset size
    fread(sizeDataOffsets, sizeof(unsigned int), 1, file);

    //if file is empty
    if (sizeDataOffsets == 0)
        return;

    unsigned int entriesRead = 0;

    //read not end of file reached OR
    //error occured AND
    //page size not read
    while (
        fread(
            &dataOffsets[entriesRead++],
            sizeof(struct DataOffset), 
            1, 
            file) &&
        entriesRead < MAX_INDEX_PAGE_ENTRIES);

    //how reading ended
    if (feof(file))
        printf("End of file %s reached.\n", path);
    else
        printf("Failed to read %s file.\n", path);

    fclose(file);
}

void printIndexPage(struct DataOffset* indexPage, int indexPageSize)
{
    for (int i = 0; i < indexPageSize; ++i)
        printf("index: %i\toffset:%i\n", indexPage[i].index, indexPage[i].offset);
}

void insert_m(struct Team* team)
{
    FILE* file = fopen(PATH_TABLE_TEAM, "ab+");
    if (!file)
    {
        printf("File %s not found.\n", PATH_TABLE_TEAM);
        return;
    }

    //assign new id
    team->id = sizeDataOffsetsTeam;

    //seek to the end of file and save position as offset for new entry
    fseek(file, 0, SEEK_END);
    unsigned int offset =  ftell(file);
    fwrite(team, sizeof(struct Team), 1, file);
    fclose(file);

    //fill correspond field in memory index array
    dataOffsetsTeam[sizeDataOffsetsTeam].index = sizeDataOffsetsTeam;
    dataOffsetsTeam[sizeDataOffsetsTeam].offset = offset;
    sizeDataOffsetsTeam++;
    updateIndexFileTeam();
}


struct Team* get_m(unsigned int id)
{
    //no data
    if (sizeDataOffsetsTeam <= 0) 
        return NULL;
    
    //search through memory table of index
    for (int i = 0; i < sizeDataOffsetsTeam; ++i)
        if (dataOffsetsTeam[i].index == id)
            return readTeamByOffset(dataOffsetsTeam[i].offset);

    //if not found
    printf("Index %i from table Teams not found.\n", id);
    return NULL;
}

struct Team* readTeamByOffset(unsigned int offset)
{
    FILE* file = fopen(PATH_TABLE_TEAM, "rb");

    if (!file)
    {
        printf("File %s not found.\n", PATH_TABLE_TEAM);
        return;
    }

    //seek to needed element
    fseek(file, offset, SEEK_SET);

    struct Team* temp = malloc(sizeof(struct Team));
    fread(
        temp,
        sizeof(struct Team),
        1,
        file);

    fclose(file);

    return temp;
}

void printTeam(struct Team* team)
{
    printf("========== Team %s ==========\n", team->team_name);
    printf(
        "# [%i]\n"
        "# Country\t%s\n"
        "# Coach  \t%s\n"
        "# Status \t%s\n"
        "# Points \t%i\n",
        team->id, 
        team->country_name, 
        team->coach_name, 
        team->status, 
        team->points);
}

void updateIndexFileTeam()
{
    FILE* file = fopen(PATH_TABLE_INDEX_TEAM, "wb");
    if (!file)
    {
        printf("File %s not found.\n", PATH_TABLE_INDEX_TEAM);
        return;
    }
    unsigned int trueSize = sizeDataOffsetsTeam;
    fwrite(&trueSize, sizeof(unsigned int), 1, file);
    for (int i = 0; i < trueSize; ++i)
        fwrite(&dataOffsetsTeam[i], sizeof(struct DataOffset), 1, file);

    fclose(file);
}

