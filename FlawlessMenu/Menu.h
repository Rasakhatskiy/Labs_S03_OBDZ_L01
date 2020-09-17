#ifndef MENU_H
#define MENU_H

#define MAX_NUMBER_ITEMS 256
#define MAX_STRING_SIZE 256

#include <stdio.h> 
#include <string.h> 

enum menu_button
{
	undefined = 0, 
	up, 
	down, 
	select
};

enum menu_type
{
	back = 0, 
	home, 
	exit, 
	function, 
	submenu
};

struct Menu
{
	//Submenu list
	struct Menu* children[MAX_NUMBER_ITEMS];
	int childrenSize;

	//Title on the top of menu
	char title[MAX_STRING_SIZE];

	//	=======Title=====
	char filler[MAX_STRING_SIZE];

	//-->Menu
	char selector[MAX_STRING_SIZE];

	//Name of that menu in list
	char item[MAX_STRING_SIZE];

	//Selector position in current menu
	int cursor;

	//Functionality of menu
	enum menu_type type;

	//Function for execute when selected
	void (*function)(void);
} ;

//Clears screen and draws menu
void draw(struct Menu* menu);

//Gets next action on menu
enum Button getButton();

//adds menu structure to menu list
void addSubmenuItem(struct Menu* menu, char menu_str[MAX_STRING_SIZE], struct Menu* menuAdd);

//adds function to menu list
void addFunctionItem(struct Menu* menu, char menu_str[MAX_STRING_SIZE], void (*functionAdd)(void));

//start the menu
int startMenu(struct Menu* menu);

#endif