#include <ncurses.h>
#include <window.h>
#include <stdlib.h>
#include <time.h>

#define N_ROOMS 10
#define COLOR_WW 1
#define COLOR_WB 2

int main(int c, char *argv[])
{
	WINDOW *base_win, *small_win;
	int maxy, maxx;

	/* INITIALIZE CURSES AND REFRESH THE STANDARD SCREEN */
	setup();

	init_pair(COLOR_WW, COLOR_WHITE, COLOR_WHITE);
	init_pair(COLOR_WB, COLOR_WHITE, COLOR_BLACK);

	getmaxyx(stdscr, maxy, maxx);
	touchwin(stdscr);
	wrefresh(stdscr); /* I don't know why this is necessary, but it is! */

	/* CREATE AND DISPLAY THE BASE WINDOW */
	base_win = newwin(maxy, maxx, 0, 0);
	box(base_win, 0, 0);
	titleScreen(base_win);
	touchwin(base_win);
	wrefresh(base_win);
	srand(time(NULL));
	//getch();

	/* CREATE AND DISPLAY THE SMALL WINDOW */
	small_win = newwin(10, COLS - 20, LINES - 11, 1);
	box(small_win, 0, 0);
	mvwaddstr(small_win, 1, 1, "<HELP>");
	mvwaddstr(small_win, 3, 3, "F1<QUIT>");
	mvwaddstr(small_win, 4, 3, "BACKSPACE \t<MAIN MENU>");
	mvwaddstr(small_win, 5, 3, "TAB \t \t<SUBMENU>");
	mvwaddstr(small_win, 6, 3, "ANY KEY\t<GENERATE MAP>");
	touchwin(base_win);
	wrefresh(small_win);
	attron(COLOR_PAIR(COLOR_WW));
	//getch();

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
			toggleWin(base_win);
			break;
		case 9:
			toggleWin(small_win);
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
			box(base_win, 0, 0);
			endDraw();
			init_pair(COLOR_WB, COLOR_WHITE, COLOR_BLACK);
			attron(COLOR_PAIR(COLOR_WB));
			border(0,0,0,0,0,0,0,0);
			break;
		}
	}

	teardown();
	return (0);
}