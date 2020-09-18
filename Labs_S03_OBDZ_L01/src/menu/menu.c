#include "menu.h"


void drawMenu(struct Menu* menu)
{
	system("CLS");

	printf("==========%s==========\n", menu->title);

	for (unsigned i = 0; i < menu->size; ++i)
	{
		if (menu->position == i)
			printf(">");
		else
			printf(" ");

		printf("%s\n", menu->children[i]->title);
	}
}

enum menu_button getButton(void)
{
	auto key = _getch();

	if (key == 0x00 ||
		key == 0xE0)
		key = _getch();

	switch (key)
	{
		case 119: case 72:		return menu_b_up;
		case 115: case 80:		return menu_b_down;
		case 13:				return menu_b_select;
		default:				return menu_b_undefined;
	}
}

int function_back(void) { return menu_t_back; }
int function_exit(void) { return menu_t_exit; }
int function_none(void) { return -1; }

void addItem(struct Menu* menu, struct Menu* item)
{
	menu->children[menu->size++] = item;
}

struct Menu* createMenu(char title[MAX_STRING_SIZE], int(*function)(void))
{
	struct Menu* menu = malloc(sizeof(struct Menu));
	menu->position = 0;
	menu->size = 0;
	menu->function = function;
	strncpy_s(menu->title, MAX_NUMBER_ITEMS, title, MAX_NUMBER_ITEMS);
	return menu;
}

void launchMenu(struct Menu* menu)
{
	int result;
	while (1)
	{
		drawMenu(menu);
		enum menu_button button = getButton();

		switch (button)
		{
			case menu_b_undefined:
				continue;

			case menu_b_up:
				if (menu->position > 0)
					--menu->position;
				continue;

			case menu_b_down:
				if (menu->position < menu->size - 1)
					++menu->position;
				continue;

			case menu_b_select:
				system("CLS");
				result = menu->children[menu->position]->function();
				if (result == -1) launchMenu(menu->children[menu->position]);
				if (result == menu_t_back) return menu_t_back;
				else continue;

			default:
				continue;
		}
	}
}
