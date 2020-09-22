#ifdef _WIN32
#define _CRT_SECURE_NO_DEPRECATE
#endif

#include <stdio.h>

#include "menu/menu.h"
#include "database/database.h"
#include "input/input.h"

void A()
{
	printf("A \n");
	getButton();
}

void B()
{
	printf("B \n");
	getButton();

}

void C()
{
	printf("C \n");
	getButton();
}


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
	//struct Team* team = malloc(sizeof(struct Team));


	loadIndexFiles();

	//demoInsertPlayer();
	//demoInsertTeams();
	//printIndexPage(dataOffsetsTeam, sizeDataOffsetsTeam);

	//struct Team* t;
	//for (int i = 0; i < 3; ++i)
	//{
	//	t = get_m(i);
	//	printTeam(t);
	//	//editTeam(i);
	//}
	

	struct Player* player;
	for (int i = 0; i < 3; ++i)
	{
		player = get_s(i);
		printPlayer(player);
		//editPlayer(i);
	}

	/*struct Menu* menu_main = createMenu("main menu\0", function_exit);
	struct Menu* menu_a = createMenu("A\0", A);
	struct Menu* menu_b = createMenu("B\0", B);
	struct Menu* menu_c = createMenu("C\0", C);

	struct Menu* menu_test_submenu = createMenu("sub\0", function_none);
	struct Menu* menu_back = createMenu("back\0", function_back);


	addItem(menu_main, menu_a);
	addItem(menu_main, menu_b);
	addItem(menu_main, menu_c);
	addItem(menu_main, menu_test_submenu);

	addItem(menu_test_submenu, menu_a);
	addItem(menu_test_submenu, menu_b);
	addItem(menu_test_submenu, menu_c);
	addItem(menu_test_submenu, menu_back);

	launchMenu(menu_main);

	free(menu_main);
	free(menu_test_submenu);
	free(menu_a);
	free(menu_b);
	free(menu_c);
	return 0;*/
}