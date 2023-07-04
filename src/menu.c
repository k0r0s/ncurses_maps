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

void titleScreen(WINDOW *p_win)
{
mvwaddstr(p_win, 1, 1, "TITLE GOES HERE!");
}

void initBaseWin(WINDOW * p_win)
{
	assert(p_win);
	box(p_win, 0, 0);
	titleScreen(p_win);
}

void initTabWin(WINDOW * p_win)
{
	assert(p_win);
	box(p_win, 0, 0);
	mvwaddstr(p_win, 1, 1, "<HELP>");
	mvwaddstr(p_win, 3, 3, "F1\t\t<QUIT>");
	mvwaddstr(p_win, 4, 3, "BACKSPACE \t<MAIN MENU>");
	mvwaddstr(p_win, 5, 3, "TAB \t \t<SUBMENU>");
	mvwaddstr(p_win, 6, 3, "ANY KEY\t<GENERATE MAP>");
}

void killWin(win_struct_t * win_s)
{
	free(win_s);
}
