#ifndef MENU_H
#define MENU_H

#define MAX_NUMBER_ITEMS 256
#define MAX_STRING_SIZE 256

#include <string.h>

enum menu_button
{
	menu_b_undefined = 0,
	menu_b_up,
	menu_b_down,
	menu_b_select
};

enum menu_type
{
	menu_t_back = 1,
	menu_t_exit,
	menu_t_submenu
};

struct Menu 
{
	//Title on the top of menu
	char title[MAX_STRING_SIZE];

	//Submenu list
	struct Menu* children[MAX_NUMBER_ITEMS];

	//number of children
	int size;

	//Selector position in current menu
	int position;

	//Function for execute when selected
	int (*function)(void);
};

void drawMenu(struct Menu* menu);

enum menu_button getButton(void);

int function_back(void); 
int function_exit(void);
int function_none(void);

void addItem(struct Menu* menu, struct Menu* item);

struct Menu* createMenu(char title[MAX_STRING_SIZE], int (*function)(void));

void launchMenu(struct Menu* menu);
#endif