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
/*

void addSubmenuItem(struct Menu* menu, char menu_str[MAX_STRING_SIZE], struct Menu* menuAdd)
{
	strncpy_s(menuAdd->item, MAX_STRING_SIZE, menu_str, MAX_STRING_SIZE);
	strncpy_s(menuAdd->children[menuAdd->childrenSize - 1]->item, MAX_STRING_SIZE, "Back\0", 5);
	menuAdd->children[menuAdd->childrenSize - 1]->type = back;

	menu->children[menu->childrenSize++] = menuAdd;
}

void addFunctionItem(struct Menu* menu, char menu_str[MAX_STRING_SIZE], void(*functionAdd)(void))
{
	struct Menu* newMenu = malloc(sizeof(newMenu));
	strncpy_s(newMenu->title, 1, "\0", 1);
	newMenu->type = function;
	strncpy_s(newMenu->item, MAX_STRING_SIZE, menu_str, MAX_STRING_SIZE);
	newMenu->function = functionAdd;
	menu->children[menu->childrenSize++] = newMenu;
}

int startMenu(struct Menu* menu)
{
	switch (menu->type)
	{
		case back:
			return 1;
		case home:
			return 2;
		case exit:
			return 1;
		case function:
			menu->function();
			return 0;
		case submenu:
			break;
		default:
			break;
	}
	int result;
	while (1)
	{
		draw(menu);
		enum menu_button button = getButton();

		switch (button)
		{
			case undefined:
				continue;

			case up:
				if (menu->cursor > 0)
					--menu->cursor;
				continue;

			case down:
				if (menu->cursor < menu->childrenSize - 1)
					++menu->cursor;
				continue;

			case select:
				system("CLS");
				result = startMenu(menu->children[menu->cursor]);
				if (result == 1) return 0;
				if (result == 2) return 2;
				else continue;

			default:
				continue;;
		}
	}
}
*/
#endif