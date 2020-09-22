#include "database.h"

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

void update_m(struct Team* team)
{
    FILE* file = fopen(PATH_TABLE_TEAM, "wb+");
    if (!file)
    {
        printf("File %s not found.\n", PATH_TABLE_TEAM);
        return;
    }

    //get offset and check it existance
    unsigned int offset = 0xFFFFFFFF;
    for (int i = 0; i < sizeDataOffsetsTeam; ++i)
        if (dataOffsetsTeam[i].index == team->id)
            offset = dataOffsetsTeam[i].offset;

    if (offset == 0xFFFFFFFF)
    {
        printf("Team %i not found.\n", team->id);
        return;
    }

    //seek to the needed offset and write here
    fseek(file, offset, SEEK_SET);
    fwrite(team, sizeof(struct Team), 1, file);
    fclose(file);
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




void insert_s(struct Player* player)
{
    if (!isIndexTeamExists(player->team_id))
    {
        printf("Team [%i] not found.\n", player->team_id);
        return;
    }

    FILE* file = fopen(PATH_TABLE_PLAYER, "ab+");
    if (!file)
    {
        printf("File %s not found.\n", PATH_TABLE_PLAYER);
        return;
    }

    // assign new id
    player->id = sizeDataOffsetsPlayer;

    //seek to the end of file and save position as offset for new entry
    fseek(file, 0, SEEK_END);
    unsigned int offset = ftell(file);
    fwrite(player, sizeof(struct Team), 1, file);
    fclose(file);

    //fill correspond field in memory index array
    dataOffsetsPlayer[sizeDataOffsetsPlayer].index = sizeDataOffsetsPlayer;
    dataOffsetsPlayer[sizeDataOffsetsPlayer].offset = offset;
    sizeDataOffsetsPlayer++;
    updateIndexFilePlayer();
}

int isIndexTeamExists(int index)
{
    for (int i = 0; i < sizeDataOffsetsTeam; ++i)
        if (dataOffsetsTeam[i].index == index)
            return 1;
    return 0;
}

struct Player* get_s(unsigned int id)
{
    //no data
    if (sizeDataOffsetsPlayer <= 0)
        return NULL;

    //search through memory table of index
    for (int i = 0; i < sizeDataOffsetsPlayer; ++i)
        if (dataOffsetsPlayer[i].index == id)
            return readPlayerByOffset(dataOffsetsPlayer[i].offset);

    //if not found
    printf("Index %i from table Players not found.\n", id);
    return NULL;
}

struct Player* readPlayerByOffset(unsigned int offset)
{
    FILE* file = fopen(PATH_TABLE_PLAYER, "rb");

    if (!file)
    {
        printf("File %s not found.\n", PATH_TABLE_PLAYER);
        return;
    }

    //seek to needed element
    fseek(file, offset, SEEK_SET);

    struct Player* temp = malloc(sizeof(struct Player));
    fread(
        temp,
        sizeof(struct Player),
        1,
        file);

    fclose(file);

    return temp;
}



void printPlayer(struct Player* player)
{
    struct Team* team = get_m(player->team_id);

    printf("========== Player %s ==========\n", player->player_name);
    printf(
        "# [%i]\n"
        "# Number   \t%i\n"
        "# Team [%i]\t%s\n"
        "# Birthday \t%s\n"
        "# Gender   \t%s\n"
        "# Status   \t%s\n",
        player->id,
        player->player_number,
        player->team_id, team != NULL ? team->team_name : "<Team not found>",
        player->birthday,
        player->gender == 0 ? "Female" : "Male",
        player->status);

    free(team);
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

void updateIndexFilePlayer()
{
    FILE* file = fopen(PATH_TABLE_INDEX_PLAYER, "wb");
    if (!file)
    {
        printf("File %s not found.\n", PATH_TABLE_INDEX_PLAYER);
        return;
    }
    unsigned int trueSize = sizeDataOffsetsPlayer;
    fwrite(&trueSize, sizeof(unsigned int), 1, file);
    for (int i = 0; i < trueSize; ++i)
        fwrite(&dataOffsetsPlayer[i], sizeof(struct DataOffset), 1, file);

    fclose(file);
}
