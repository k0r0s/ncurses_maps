#include <ncurses.h>
#include <window.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>




void toggle_win(WINDOW *p_win)
{
    touchwin(p_win);
	wrefresh(p_win);
}


void init_win_params(ROOM *p_win, int height, int width, int init_y, int init_x)
{
	if (p_win->is_passage) // TODO change -- only works for horizontal passages.
	{
		p_win->height = height;
		p_win->width = width;
		p_win->starty = init_y;	
		p_win->startx = init_x + p_win->width;

		p_win->border.ls = ACS_VLINE;
		p_win->border.rs = ACS_VLINE;
		p_win->border.ts = ACS_HLINE;
		p_win->border.bs = ACS_HLINE;
		p_win->border.tl = ACS_LLCORNER;
		p_win->border.tr = ACS_LRCORNER;
		p_win->border.bl = ACS_ULCORNER;
		p_win->border.br = ACS_URCORNER;
	} 
	else 
	{
		p_win->height = height;
		p_win->width = width;
		p_win->starty = init_y;	
		p_win->startx = init_x;


		p_win->border.ls = ACS_VLINE;
		p_win->border.rs = ACS_VLINE;
		p_win->border.ts = ACS_HLINE;
		p_win->border.bs = ACS_HLINE;
		p_win->border.tl = ACS_ULCORNER;
		p_win->border.tr = ACS_URCORNER;
		p_win->border.bl = ACS_LLCORNER;
		p_win->border.br = ACS_LRCORNER;
	}

}



void print_win_params(ROOM *p_win)
{
#ifdef _DEBUG
	mvprintw(25, 0, "%d %d %d %d", p_win->startx, p_win->starty, 
				p_win->width, p_win->height);
	refresh();
#endif
}


void create_box_borders(ROOM *p_win, bool flag)
{	int i, j;
	int x, y, w, h;

	x = p_win->startx;
	y = p_win->starty;
	w = p_win->width;
	h = p_win->height;

	if(flag == TRUE)
	{	
		mvaddch(y, x, p_win->border.tl); // TOP LEFT CORNER
		mvaddch(y, x + w, p_win->border.tr); // TOP RIGHT CORNER
		mvaddch(y + h, x, p_win->border.bl); // BOTTOM LEFT CORNER
		mvaddch(y + h, x + w, p_win->border.br); // BOTTOM RIGHT CORNER
		mvhline(y, x + 1, p_win->border.ts, w - 1); // TOP HORIZONTAL LINE
		mvhline(y + h, x + 1, p_win->border.bs, w - 1); // BOTTOM HORIZONTAL LINE
		mvvline(y + 1, x, p_win->border.ls, h - 1); // LEFT HORIZONTAL LINE
		mvvline(y + 1, x + w, p_win->border.rs, h - 1); // RIGHT HORIZONTAL LINE

	} // erase
	else
		for(j = y; j <= y + h; ++j)
			for(i = x; i <= x + w; ++i)
				mvaddch(j, i, ' ');
				
	refresh();

}

void create_box_full(ROOM *p_win, bool flag)
{
	int i,j;
	int x,y,w,h;
	
	x = p_win->startx;
	y = p_win->starty;
	w = p_win->width;
	h = p_win->height;

		if(flag == TRUE)
	{	
		for (j = y; j < y + h; ++j)
			for (i = x; i < x + w; ++i)
				mvaddch(j,i,ACS_CKBOARD);
	} // erase
	else
		for(j = y; j <= y + h; ++j)
			for(i = x; i <= x + w; ++i)
				mvaddch(j, i, ' ');
				
	refresh();
}

bool valueInRange(int value, int min, int max)
{ return (value >= min) && (value <= max); }

bool rectOverlap(ROOM A, ROOM B)
{
    bool xOverlap = valueInRange(A.startx, B.startx, B.startx + B.width) ||
                    valueInRange(B.startx, A.startx, A.startx + A.width);

    bool yOverlap = valueInRange(A.starty, B.starty, B.starty + B.height) ||
                    valueInRange(B.starty, A.starty, A.starty + A.height);

    return xOverlap && yOverlap;
}

bool checkAllOverlap(ROOM * rooms,int n)
{
	ROOM A = rooms[n];
	for (int i = 0; i < n; i++)
	{
		ROOM B = rooms[i];
		if (rectOverlap(A,B)){
			return TRUE;
		}
	}
	return FALSE;
}

void layout_rooms(ROOM * rooms, int num, int MAP_HEIGHT, int MAP_WIDTH)
{

	int ROOM_MAX_WIDTH =  20;
	int ROOM_MAX_HEIGHT = 10;
	int width, height, startx, starty, n;

	width = rand() % (ROOM_MAX_WIDTH + 1);
	height = rand() % (ROOM_MAX_HEIGHT + 1);

	startx = rand() % (MAP_WIDTH + 1) + 1;
	starty = rand() % (MAP_HEIGHT + 1) + 1;
	rooms[0].is_passage = FALSE;

	init_win_params(&rooms[0], height, width, starty, startx);

	for (n = 0; n < num; n++)
	{
		do
		{
			width = rand() % (ROOM_MAX_WIDTH + 1);
			height = rand() % (ROOM_MAX_HEIGHT + 1);

			startx = rand() % (MAP_WIDTH + 1) + 1;
			starty = rand() % (MAP_HEIGHT + 1) + 1;
			rooms[n].is_passage = FALSE;

			init_win_params(&rooms[n], height, width, starty, startx);

		} while (checkAllOverlap(rooms,n));

		create_box_full(&rooms[n], TRUE);
		
	}
}