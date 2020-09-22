#ifdef _WIN32
#define _CRT_SECURE_NO_DEPRECATE
#endif

#include <stdio.h>

#include "menu/menu.h"
#include "database/database.h"
#include "input/input.h"

#define SIZE_MAIN_MENU 9


void demoInsertTeams()
{
	struct Team* team = malloc(sizeof(struct Team));

	strncpy(team->team_name, "Big boss team ltd\0", MAX_STRING_NAME);
	strncpy(team->country_name, "Ukraine\0", MAX_STRING_COUNTRY);
	strncpy(team->coach_name, "Main Moksym\0", MAX_STRING_NAME);
	strncpy(team->status, "Procrastinating\0", MAX_STRING_SIZE);
	team->points = 47;
	insert_m(team);

	strncpy(team->team_name, "jebrony nice ass team\0", MAX_STRING_NAME);
	strncpy(team->country_name, "Moskovia\0", MAX_STRING_COUNTRY);
	strncpy(team->coach_name, "Yakis sportsman\0", MAX_STRING_NAME);
	strncpy(team->status, "Very long long long long long long long long long long long long long long long long long long long long long long long text\0", MAX_STRING_SIZE);
	team->points = 10;
	insert_m(team);

	strncpy(team->team_name, "c\0", MAX_STRING_NAME);
	strncpy(team->country_name, "c\0", MAX_STRING_COUNTRY);
	strncpy(team->coach_name, "c\0", MAX_STRING_NAME);
	strncpy(team->status, "c\0", MAX_STRING_SIZE);
	team->points = 12;
	insert_m(team);

	strncpy(team->team_name, "d\0", MAX_STRING_NAME);
	strncpy(team->country_name, "d\0", MAX_STRING_COUNTRY);
	strncpy(team->coach_name, "d\0", MAX_STRING_NAME);
	strncpy(team->status, "d\0", MAX_STRING_SIZE);
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
	strncpy(player->status, "krutgfk fgh fsdgjy g ;e fdhuf kdl hsfdf dsfk jsdkf  fhd  djfhdjf hd f dfhhfh fh\0", MAX_STRING_SIZE);
	insert_s(player);

	strncpy(player->birthday, "99.99.9999\0", MAX_STRING_DATE);
	player->team_id = 0;
	player->gender = 0;
	player->player_number = 14;
	strncpy(player->player_name, "Olga\0", MAX_STRING_NAME);
	strncpy(player->status, "ssdkfdfg gggggggggggg fh\0", MAX_STRING_SIZE);
	insert_s(player);

	strncpy(player->birthday, "88/88/8888\0", MAX_STRING_DATE);
	player->team_id = 2;
	player->gender = 0;
	player->player_number = 123;
	strncpy(player->player_name, "Keksik\0", MAX_STRING_NAME);
	strncpy(player->status, "Eating keks\0", MAX_STRING_SIZE);
	insert_s(player);
}



int main()
{
	loadIndexFiles();

	struct Menu* menu_main = createMenu("Main menu\0", function_exit);
	struct Menu* menus[SIZE_MAIN_MENU] =
	{
		createMenu("Add Team   [insert-m]\0", function_insert_m),
		createMenu("Add Player [insert-s]\0", function_insert_s),
		createMenu("Get Team   [get-m]\0", function_get_m),
		createMenu("Get Player [get-s]\0", function_get_s),
		createMenu("Upd Team   [update-m]\0", function_update_m),
		createMenu("Upd Player [update-s]\0", function_update_s),
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