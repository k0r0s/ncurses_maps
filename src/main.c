#include <ncurses.h>
#include <window.h>
#include <stdlib.h>
#include <time.h>

#define N_ROOMS 10

int main(int c, char *argv[])
	{
	WINDOW *base_win, *small_win;
	int maxy, maxx;


	/* INITIALIZE CURSES AND REFRESH THE STANDARD SCREEN */
	initscr();
	if (has_colors() == FALSE)
	{
		endwin();
		printf("Your terminal does not support color. \n");
		exit(1);
	}
	start_color();
	init_pair(1, COLOR_WHITE, COLOR_WHITE);
	attron(COLOR_PAIR(1));

    cbreak();
    keypad(stdscr, TRUE);		/* I need that nifty F1 	*/
	noecho();

	getmaxyx(stdscr, maxy, maxx);
	touchwin(stdscr);
	wrefresh(stdscr); /* I don't know why this is necessary, but it is! */
	
	/* CREATE AND DISPLAY THE BASE WINDOW */
	base_win = newwin(maxy, maxx, 0,0);
	box(base_win, 0, 0);
	mvwaddstr(base_win, 2,2,"<Press any key to toggle>");
	touchwin(base_win);
	wrefresh(base_win);
	srand(time(NULL));
	getch();

    /* CREATE AND DISPLAY THE SMALL WINDOW */
    small_win = newwin(10, COLS - 20, LINES - 11, 1);
	box(small_win, 0, 0);
	mvwaddstr(small_win, 1,1,"<HELP>");
	mvwaddstr(small_win, 3,3,"F1<QUIT>");
	mvwaddstr(small_win,5,3,"ANY KEY<GENERATE MAP>");
	touchwin(base_win);
	wrefresh(small_win);
	getch();


    int ch;
	ROOM * rooms = malloc(N_ROOMS*sizeof(ROOM));

    while (ch != KEY_F(1))
    {
		
        layoutRooms(rooms,N_ROOMS,LINES,COLS);
		assignNumConnections(rooms,N_ROOMS,2);
		getCenters(rooms,N_ROOMS);
		getDistancesToClosest(rooms,N_ROOMS);
		clear();
		for (int i = 0; i < N_ROOMS; i ++)
		{
			drawBoxFull(&rooms[i], TRUE);
		}
		drawConnections(rooms,N_ROOMS);
		box(base_win, 0, 0);
		refresh();
        ch = getch();
        toggleWin(small_win);
        ch = getch();
        toggleWin(base_win);     


    }

	endwin();
	return(0);
	}