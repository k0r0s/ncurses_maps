#ifndef MENU_H
#define MENU_H

#include <ncurses.h>
#include <window.h>
#include <stdlib.h>



typedef struct win_size_tag {
	int maxy;
	int maxx;
	int miny;
	int minx;
} win_size_t;

typedef struct win_struct_tag {
	win_size_t size;
	WINDOW * window;
} win_struct_t;

typedef void (*initWinFun)(WINDOW * win);
win_struct_t * initWin(win_size_t win_s, initWinFun pFun);
void killWin(win_struct_t * win_s);
void titleScreen(WINDOW * p_win);
void initBaseWin(WINDOW * p_win);
void initTabWin(WINDOW * p_win);

#endif /* MENU_H */
