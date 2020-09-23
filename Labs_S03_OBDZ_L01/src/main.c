#ifdef _WIN32
#define _CRT_SECURE_NO_DEPRECATE
#endif

#include <stdio.h>

#include "menu/menu.h"
#include "database/database.h"
#include "input/input.h"

#define SIZE_MAIN_MENU 11


void demoInsertTeams()
{
	struct Team* team = malloc(sizeof(struct Team));

	strncpy(team->team_name, "Big boss team ltd\0", MAX_STRING_NAME);
	strncpy(team->country_name, "Ukraine\0", MAX_STRING_COUNTRY);
	strncpy(team->coach_name, "Main Moksym\0", MAX_STRING_NAME);
	strncpy(team->status, "Procrastinating\0", MAX_STRING_SIZE);
	team->points = 47;
	insert_m(team);

	strncpy(team->team_name, "KNU pro big title team\0", MAX_STRING_NAME);
	strncpy(team->country_name, "Sheva\0", MAX_STRING_COUNTRY);
	strncpy(team->coach_name, "Yakis sportsman\0", MAX_STRING_NAME);
	strncpy(team->status, "Very long long long long long long long long long long long long long long long long long long long long long long long text\0", MAX_STRING_SIZE);
	team->points = 10;
	insert_m(team);

	strncpy(team->team_name, "Kompudatoria\0", MAX_STRING_NAME);
	strncpy(team->country_name, "Belarus\0", MAX_STRING_COUNTRY);
	strncpy(team->coach_name, "Goncharenko\0", MAX_STRING_NAME);
	strncpy(team->status, "Veseli\0", MAX_STRING_SIZE);
	team->points = 12;
	insert_m(team);

	strncpy(team->team_name, "Team 4\0", MAX_STRING_NAME);
	strncpy(team->country_name, "You Crane\0", MAX_STRING_COUNTRY);
	strncpy(team->coach_name, "John Cooper\0", MAX_STRING_NAME);
	strncpy(team->status, "Ya ne znayu sho syda napisaty\0", MAX_STRING_SIZE);
	team->points = 13;
	insert_m(team);
}

void demoInsertPlayer()
{
	struct Player* player = malloc(sizeof(struct Player));

	strncpy(player->birthday, "20.04.2000\0", MAX_STRING_DATE);
	player->team_id = 1;
	player->gender = 1;
	player->player_number = 22;
	strncpy(player->player_name, "Maksym Maksym Maksym\0", MAX_STRING_NAME);
	strncpy(player->status, "Somebody once told him the world is gonna roll him\0", MAX_STRING_SIZE);
	insert_s(player);

	strncpy(player->birthday, "99.99.9999\0", MAX_STRING_DATE);
	player->team_id = 0;
	player->gender = 0;
	player->player_number = 14;
	strncpy(player->player_name, "Olga\0", MAX_STRING_NAME);
	strncpy(player->status, "Is not the sharpest tool in the shed\0", MAX_STRING_SIZE);
	insert_s(player);

	strncpy(player->birthday, "11.11.2011\0", MAX_STRING_DATE);
	player->team_id = 2;
	player->gender = 0;
	player->player_number = 123;
	strncpy(player->player_name, "Keksik\0", MAX_STRING_NAME);
	strncpy(player->status, "Eating keks\0", MAX_STRING_SIZE);
	insert_s(player);

	strncpy(player->birthday, "11.11.2011\0", MAX_STRING_DATE);
	player->team_id = 2;
	player->gender = 0;
	player->player_number = 123;
	strncpy(player->player_name, "A\0", MAX_STRING_NAME);
	strncpy(player->status, "A\0", MAX_STRING_SIZE);
	insert_s(player);

	strncpy(player->birthday, "11.11.2011\0", MAX_STRING_DATE);
	player->team_id = 1;
	player->gender = 0;
	player->player_number = 123;
	strncpy(player->player_name, "B\0", MAX_STRING_NAME);
	strncpy(player->status, "B\0", MAX_STRING_SIZE);
	insert_s(player);

	strncpy(player->birthday, "11.11.2011\0", MAX_STRING_DATE);
	player->team_id = 0;
	player->gender = 0;
	player->player_number = 123;
	strncpy(player->player_name, "C\0", MAX_STRING_NAME);
	strncpy(player->status, "C\0", MAX_STRING_SIZE);
	insert_s(player);
}



int main()
{
	loadIndexFiles();
	//printIndexPage(dataOffsetsTeam, sizeDataOffsetsTeam);
	//printf("\n");
	//printIndexPage(dataOffsetsPlayer, sizeDataOffsetsPlayer);
	//_getch();
	demoInsertTeams();
	demoInsertPlayer();
	return 0;
	struct Menu* menu_main = createMenu("Main menu\0", function_exit);
	struct Menu* menus[SIZE_MAIN_MENU] =
	{
		createMenu("Add Team   [insert-m]\0", function_insert_m),
		createMenu("Add Player [insert-s]\0", function_insert_s),
		createMenu("Get Team   [get-m]\0", function_get_m),
		createMenu("Get Player [get-s]\0", function_get_s),
		createMenu("Upd Team   [update-m]\0", function_update_m),
		createMenu("Upd Player [update-s]\0", function_update_s),
		createMenu("Del Team   [delete-m]\0", function_delete_m),
		createMenu("Del Player [delete-s]\0", function_delete_s),
		createMenu("Print all teams\0", function_printAll_m),
		createMenu("Print all players\0", function_printAll_s),
		createMenu("Exit\0", function_back)
	};

	/*struct Menu* menu_test_submenu = createMenu("sub\0", function_none);
	struct Menu* menu_back = createMenu("back\0", function_back);*/

	for (int i = 0; i < SIZE_MAIN_MENU; ++i)
		addItem(menu_main, menus[i]);
	
	launchMenu(menu_main);

	free(menu_main);
	for (int i = 0; i < SIZE_MAIN_MENU; ++i)
		free(menus[i]);

	return 0;
}