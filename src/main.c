#include <ncurses.h>
#include <window.h>
#include <stdlib.h>

#define N_ROOMS 10

int main(int c, char *argv[])
	{
	WINDOW *base_win, *small_win;
	int maxy, maxx;
    ROOM room1, passage1;
    passage1.is_passage = TRUE;

	/* INITIALIZE CURSES AND REFRESH THE STANDARD SCREEN */
	initscr();
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
	getch();

    /* CREATE AND DISPLAY THE SMALL WINDOW */
    small_win = newwin(10, 30, 3,3);
	box(small_win, 0, 0);
	mvwaddstr(small_win, 1,1,"<HELP>");
	mvwaddstr(small_win, 3,3,"F1<QUIT>");
	touchwin(base_win);
	wrefresh(small_win);
	getch();

    init_win_params(&room1,5,10, 5,50);
	init_win_params(&passage1,1,10, 7,50);

    int ch;
	ROOM * rooms = malloc(N_ROOMS*sizeof(ROOM));

    while (ch != KEY_F(1))
    {
		wclear(base_win);
        layout_rooms(rooms,N_ROOMS,LINES-2,COLS-2);

        ch = getch();
        toggle_win(small_win);
        ch = getch();
        box(base_win, 0, 0);
        toggle_win(base_win);     

        init_pair(1, COLOR_CYAN, COLOR_BLACK);
	    attron(COLOR_PAIR(1));

        //create_box_full(&room1, TRUE);
	    //create_box_full(&passage1, TRUE);
    }

	endwin();
	return(0);
	}