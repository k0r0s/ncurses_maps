#include <ncurses.h>
#include <stdlib.h>
#include <time.h>

#include "window.h"
#include "menu.h"
#define N_ROOMS 10
#define COLOR_WW 1
#define COLOR_WB 2

win_size_t small_win_size;
win_size_t base_win_size;


int main(int c, char *argv[])
{
	win_struct_t * base_win_s, * small_win_s;
	int maxy, maxx;

	/* INITIALIZE CURSES AND REFRESH THE STANDARD SCREEN */
	setup();

	init_pair(COLOR_WW, COLOR_WHITE, COLOR_WHITE);
	init_pair(COLOR_WB, COLOR_WHITE, COLOR_BLACK);

	getmaxyx(stdscr, maxy, maxx);
	base_win_size = (win_size_t){.maxy = maxy, .maxx = maxx, .miny = 0, .minx = 0 };
	small_win_size = (win_size_t){.maxy = 10, .maxx = COLS - 20, .miny = LINES - 11, .minx = 1};

	touchwin(stdscr);
	wrefresh(stdscr); /* I don't know why this is necessary, but it is! */

	/* CREATE AND DISPLAY THE BASE WINDOW */
	base_win_s = initWin(base_win_size, initBaseWin);

	touchwin(base_win_s->window);
	wrefresh(base_win_s->window);
	srand(time(NULL));
	getch();

	/* CREATE AND DISPLAY THE SMALL WINDOW */
	small_win_s = initWin(small_win_size, initTabWin);

	touchwin(small_win_s->window);
	wrefresh(small_win_s->window);
	attron(COLOR_PAIR(COLOR_WW));

	getch();

	int ch;
	ROOM *rooms = malloc(N_ROOMS * sizeof(ROOM));

	while (!isDone())
	{
		ch = getKey();
		switch (ch)
		{
		case KEY_F(1):
			quit();
			break;
		case KEY_BACKSPACE:
			toggleWin(base_win_s->window);
			break;
		case 9:
			toggleWin(small_win_s->window);
			break;
		default:
			layoutRooms(rooms, N_ROOMS, LINES, COLS);
			assignNumConnections(rooms, N_ROOMS, 2);
			getCenters(rooms, N_ROOMS);
			getDistancesToClosest(rooms, N_ROOMS);
			attron(COLOR_PAIR(COLOR_WW));
			startDraw();
			for (int i = 0; i < N_ROOMS; i++)
			{
				drawBoxFull(&rooms[i], TRUE);
			}
			drawConnections(rooms, N_ROOMS);
			box(base_win_s->window, 0, 0);
			endDraw();
			init_pair(COLOR_WB, COLOR_WHITE, COLOR_BLACK);
			attron(COLOR_PAIR(COLOR_WB));
			border(0,0,0,0,0,0,0,0);
			break;
		}
	}

	teardown();
	free(rooms);

	killWin(small_win_s);
	killWin(base_win_s);
	return (0);
}
