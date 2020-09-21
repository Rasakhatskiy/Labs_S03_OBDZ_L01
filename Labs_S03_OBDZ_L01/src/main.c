#ifdef _WIN32
#define _CRT_SECURE_NO_DEPRECATE
#endif

#include <stdio.h>

#include "menu/menu.h"
#include "input/validator.h"
#include "database/database.h"

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

int main()
{
	printf("enter digit:\n");
	unsigned int digit = readUInt32();
	printf("your digit: %i\n", digit);
	return 0;

	//struct Team* team = malloc(sizeof(struct Team));



	loadIndexFiles();
	printIndexPage(dataOffsetsTeam, sizeDataOffsetsTeam);


	struct Team* team = get_m(0);
	printTeam(team);

	/*strncpy(team->team_name, "Big boss team ltd\0", MAX_STRING_NAME);
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
	insert_m(team);*/



	//addRecord_Team(team);

	/*struct Player player;
	player.id = 0;
	player.player_number = 47;
	strncpy_s(player.player_name, MAX_STRING_SIZE, "Maksym\0", MAX_STRING_SIZE);
	strncpy_s(player.birthday, MAX_STRING_SIZE, "20.04.2000\0", MAX_STRING_SIZE);
	player.gender = 1;
	strncpy_s(player.status, MAX_STRING_SIZE, "характер скверный. не женат.\0", MAX_STRING_SIZE);
	
	addRecord_Player(player);*/

	

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