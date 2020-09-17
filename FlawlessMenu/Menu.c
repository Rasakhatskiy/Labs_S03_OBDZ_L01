#include "Menu.h"

void draw(struct Menu* menu)
{
	system("CLS");

	printf("%s", menu->filler);
	printf("%s", menu->title);
	printf("%s", menu->filler);

	for (unsigned i = 0; i < menu->childrenSize; ++i)
	{
		if (menu->cursor == i)	
			printf("%s", menu->selector);
		else	
			printf(" ");

		printf("%s\n", menu->children[i]->item);
	}
}

enum menu_button getButton()
{
	auto key = _getch();

	if (key == 0x00 || 
		key == 0xE0) 
		key = _getch();

	switch (key)
	{
		case 119: case 72:		return up;
		case 115: case 80:		return down;
		case 13:				return select;
		default:				return undefined;
	}
}

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
