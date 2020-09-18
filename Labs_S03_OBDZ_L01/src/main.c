#include <stdio.h>

#include "menu/menu.h"

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
	struct Menu* menu_main = createMenu("main menu\0", function_exit);
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
	return 0;
}