#include <assert.h>
#include <stdlib.h>
#include "menu.h"

/*****************************************/
/* BASE WINDOW */

win_struct_t * initWin(win_size_t size, initWinFun pFun)
{
	win_struct_t * win_s = malloc(sizeof(win_struct_t));

	win_s->window = newwin(size.maxy, size.maxx, size.miny, size.minx);
	win_s->size = size;
	pFun(win_s->window);
	return win_s;
}


void initBaseWin(WINDOW * win)
{
	assert(win);
	box(win, 0, 0);
	titleScreen(win);
}

void initTabWin(WINDOW * win)
{
	assert(win);
	box(win, 0, 0);
	mvwaddstr(win, 1, 1, "<HELP>");
	mvwaddstr(win, 3, 3, "F1<QUIT>");
	mvwaddstr(win, 4, 3, "BACKSPACE \t<MAIN MENU>");
	mvwaddstr(win, 5, 3, "TAB \t \t<SUBMENU>");
	mvwaddstr(win, 6, 3, "ANY KEY\t<GENERATE MAP>");
}


