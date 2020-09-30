#include "database.h"

void loadIndexFiles()
{
    dataOffsetsPlayer = malloc(MAX_INDEX_PAGE_ENTRIES * sizeof(struct DataOffset));
    dataOffsetsTeam = malloc(MAX_INDEX_PAGE_ENTRIES * sizeof(struct DataOffset));

    maxIndexPlayer = 0;
    maxIndexTeam = 0;

    loadIndexFile(
        dataOffsetsPlayer, 
        &sizeDataOffsetsPlayer, 
        PATH_TABLE_INDEX_PLAYER,
        &maxIndexPlayer);

    loadIndexFile(
        dataOffsetsTeam, 
        &sizeDataOffsetsTeam, 
        PATH_TABLE_INDEX_TEAM,
        &maxIndexTeam);
}

void loadIndexFile(struct DataOffset* dataOffsets, int *sizeDataOffsets, char path[], unsigned int* maxIndex)
{
    FILE* file = fopen(path, "rb");

    if (!file)
    {
        printf("File %s not found.\n", path);
        return;
    }

    *maxIndex = 0;

    //reset size
    fread(sizeDataOffsets, sizeof(unsigned int), 1, file);

    //if file is empty
    if (sizeDataOffsets == 0)
        return;

    unsigned int entriesRead = 0;

    //read not end of file reached OR
    //error occured AND
    //page size not read
    //remember max index also
    while (
        fread(
            &dataOffsets[entriesRead++],
            sizeof(struct DataOffset),
            1,
            file) &&
        entriesRead < MAX_INDEX_PAGE_ENTRIES)
        if (dataOffsets[entriesRead - 1].index > *maxIndex)
            *maxIndex = dataOffsets[entriesRead - 1].index;

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

void deleteElement(struct DataOffset* dataOffsets, unsigned int* size, int index)
{
    //find needed index in table of index-offsets
    for (int i = 0; i < *size; ++i)
    {
        if (dataOffsets[i].index == index)
        {
            //shift all table to the left by 1
            for (int j = i; j < *(size) - 1; ++j)
                dataOffsets[j] = dataOffsets[j + 1];

            //decrease table size
            --(*size);
            break;
        }
    }
}

void clearTrash()
{
    //calculate old size
    printf("Size before clearing %i bytes.\n", getFileSize(PATH_TABLE_TEAM));

    //open temp file
    FILE* file = fopen("temp", "ab+");
    if (!file)
    {
        printf("Cannot create temp file. Aborting.\n");
        return;
    }

    //rewrite temp file from table
    struct Team* team;
    unsigned int offset;
    for (int i = 0; i < sizeDataOffsetsTeam; ++i)
    {
        team = readTeamByOffset(dataOffsetsTeam[i].offset);
        offset = ftell(file);
        fwrite(team, sizeof(struct Team), 1, file);

        //remember new offset
        dataOffsetsTeam[i].offset = offset;
    }
    fclose(file);
    //delete old table
    if (!remove(PATH_TABLE_TEAM))
    {
        printf("Unable to remove file %s. Aborting.\n", PATH_TABLE_TEAM);
        return;
    }
    //rename temp to table
    if (!rename("temp", PATH_TABLE_TEAM))
    {
        printf("Unable to rename file %s to %s. Aborting.\n", "temp", PATH_TABLE_TEAM);
        return;
    }
    //update index file
    updateIndexFileTeam();
    //calculate new size
    printf("Size after clearing %i bytes.\n", getFileSize(PATH_TABLE_TEAM));


    //calculate old size
    printf("Size before clearing %i bytes.\n", getFileSize(PATH_TABLE_PLAYER));

    //open temp file
    file = fopen("temp", "ab+");
    if (!file)
    {
        printf("Cannot create temp file. Aborting.\n");
        return;
    }

    //rewrite temp file from table
    struct Player* player;
    for (int i = 0; i < sizeDataOffsetsPlayer; ++i)
    {
        
        team = readPlayerByOffset(dataOffsetsPlayer[i].offset);
        offset = ftell(file);
        fwrite(team, sizeof(struct Player), 1, file);

        //remember new offset
        dataOffsetsPlayer[i].offset = offset;
    }
    fclose(file);
    if (!remove(PATH_TABLE_PLAYER))
    {
        printf("Unable to remove file %s. Aborting.\n", PATH_TABLE_PLAYER);
        return;
    }
    //rename temp to table
    if (!rename("temp", PATH_TABLE_PLAYER))
    {
        printf("Unable to rename file %s to %s. Aborting.\n", "temp", PATH_TABLE_PLAYER);
        return;
    }
    //update index file
    updateIndexFilePlayer();
    //calculate new size
    printf("Size after clearing %i bytes.\n", getFileSize(PATH_TABLE_PLAYER));
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
    team->id = ++maxIndexTeam;
    team->firstSlaveOffset = UINT_MAX;

    //seek to the end of file and save position as offset for new entry
    fseek(file, 0, SEEK_END);
    unsigned int offset =  ftell(file);
    fwrite(team, sizeof(struct Team), 1, file);
    fclose(file);

    //fill correspond field in memory index array
    dataOffsetsTeam[sizeDataOffsetsTeam].index = team->id;
    dataOffsetsTeam[sizeDataOffsetsTeam].offset = offset;
    sizeDataOffsetsTeam++;
    updateIndexFileTeam();
    printf("Data recorded.\n");
}

void update_m(struct Team* team)
{
    FILE* file = fopen(PATH_TABLE_TEAM, "rb+");
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

void delete_m(unsigned int id)
{
    if (!isIndexTeamExists(id))
    {
        printf("Team with id %i doesn't exists", id);
        return;
    }

    struct Team* team = get_m(id);
    unsigned int next = team->firstSlaveOffset;
    free(team);

    while (next != UINT_MAX)
    {
        struct Player* temp = readPlayerByOffset(next);
        next = temp->nextSlaveOffset;
        deleteElement(dataOffsetsPlayer, &sizeDataOffsetsPlayer, temp->id);
        printf("Player %i deleted\n", temp->id);
        free(temp);
    }

    //delete index from index-offset table
    deleteElement(dataOffsetsTeam, &sizeDataOffsetsTeam, id);

    //write it to file
    updateIndexFileTeam();

    printf("Team %i deleted.\n", id);
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
    printf("\n========== Team %s ==========\n", team->team_name);
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

int isIndexTeamExists(int index)
{
    for (int i = 0; i < sizeDataOffsetsTeam; ++i)
        if (dataOffsetsTeam[i].index == index)
            return 1;
    return 0;
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
    player->id = ++maxIndexPlayer;
    player->nextSlaveOffset = UINT_MAX;

    //seek to the end of file and save position as offset for new entry
    fseek(file, 0, SEEK_END);
    unsigned int offset = ftell(file);
    fwrite(player, sizeof(struct Team), 1, file);
    fclose(file);

    //find last slave from this team
    unsigned int lastOffset = UINT_MAX;
    if (sizeDataOffsetsPlayer > 0)
    {
        //searching from end
        for (int i = sizeDataOffsetsPlayer - 1; i >= 0; --i)
        {
            //remember offset from last player of team
            struct Player* temp = readPlayerByOffset(dataOffsetsPlayer[i].offset);
            if (temp->team_id == player->team_id)
            {
                lastOffset = dataOffsetsPlayer[i].offset;
                free(temp);
                break;
            }
            free(temp);
        }
        //update previous slave to give next slave offset
        if (lastOffset != UINT_MAX)
        {
            struct Player* toUpdate = readPlayerByOffset(lastOffset);
            toUpdate->nextSlaveOffset = offset;
            update_s(toUpdate);
            free(toUpdate);
        }
        
    }

    //set team
    {
        struct Team* team = get_m(player->team_id);
        if (team->firstSlaveOffset == UINT_MAX)
        {
            team->firstSlaveOffset = offset;
            update_m(team);
        }
        free(team);
    }

    //fill correspond field in memory index array
    dataOffsetsPlayer[sizeDataOffsetsPlayer].index = player->id;
    dataOffsetsPlayer[sizeDataOffsetsPlayer].offset = offset;
    sizeDataOffsetsPlayer++;
    updateIndexFilePlayer();
    printf("Data recorded.\n");
}

void update_s(struct Player* player)
{
    FILE* file = fopen(PATH_TABLE_PLAYER, "rb+");
    if (!file)
    {
        printf("File %s not found.\n", PATH_TABLE_PLAYER);
        return;
    }

    //get offset and check it existance
    unsigned int offset = 0xFFFFFFFF;
    for (int i = 0; i < sizeDataOffsetsPlayer; ++i)
        if (dataOffsetsPlayer[i].index == player->id)
            offset = dataOffsetsPlayer[i].offset;

    if (offset == 0xFFFFFFFF)
    {
        printf("Player %i not found.\n", player->id);
        return;
    }

    //seek to the needed offset and write here
    fseek(file, offset, SEEK_SET);
    fwrite(player, sizeof(struct Player), 1, file);
    fclose(file);
}

void delete_s(unsigned int id)
{
    if (!isIndexPlayerExists(id))
    {
        printf("Player with id %i doesn't exists", id);
        return;
    }

    if (sizeDataOffsetsPlayer == 1)
    {
        //delete index from index-offset table
        struct Player* player = get_s(id);
        struct Team* team = get_m(player->team_id);
        team->firstSlaveOffset = UINT_MAX;
        update_m(team);
        free(team);
        free(player);
    }
    else
    {
        unsigned int prevOffset = UINT_MAX;
        unsigned int currOffset = UINT_MAX;
        unsigned int nextOffset = UINT_MAX;

        struct Player* curr = get_s(id);
        for (int i = 0; i < sizeDataOffsetsPlayer; ++i)
        {
            if (dataOffsetsPlayer[i].index == id)
            {
                currOffset = dataOffsetsPlayer[i].offset;
                struct Player* player = readPlayerByOffset(dataOffsetsPlayer[i].offset);
                nextOffset = player->nextSlaveOffset;
                free(player);
                break;
            }
        }
            
        //find team
        struct Team* team = NULL;
        for (int i = 0; i < sizeDataOffsetsTeam; ++i)
        {
            team = get_m(dataOffsetsTeam[i].index);
            if (team->id == curr->team_id)
            {
                break;
            }
        }

        //if deleting first slave of master
        if (team->firstSlaveOffset == currOffset)
        {
            team->firstSlaveOffset = nextOffset;
            update_m(team);
        }
        //remember offset of first
        else
        {
            prevOffset = team->firstSlaveOffset;
            struct Player* prev = readPlayerByOffset(prevOffset);
            while (
                prev->nextSlaveOffset != currOffset &&
                prev->nextSlaveOffset != UINT_MAX)
            {
                prevOffset = prev->nextSlaveOffset;
                free(prev);
                prev = readPlayerByOffset(prevOffset);
            }

            prev->nextSlaveOffset = nextOffset;
            update_s(prev);
            free(prev);
        }
        free(team);
        free(curr);
    }
    
    deleteElement(dataOffsetsPlayer, &sizeDataOffsetsPlayer, id);

    //write it to file
    updateIndexFilePlayer();

    printf("Player %i deleted.\n", id);
}

int isIndexPlayerExists(int index)
{
    for (int i = 0; i < sizeDataOffsetsPlayer; ++i)
        if (dataOffsetsPlayer[i].index == index)
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

    printf("\n========== Player %s ==========\n", player->player_name);
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

long getFileSize(char path[])
{
    FILE* file = fopen(PATH_TABLE_TEAM, "ab+");
    fseek(file, 0, SEEK_END);
    unsigned int offset = ftell(file);
    fclose(file);
    return offset;
}