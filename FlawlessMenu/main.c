#include <stdio.h>

#include "Menu.h"

int main()
{
	struct Menu menu;
	while (1)
	{
		enum menu_button e = getButton();
		printf("%d", e);
	}
	printf("Hello world! \n");
}