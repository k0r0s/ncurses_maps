#include <ncurses.h>
#include <window.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

void toggleWin(WINDOW *p_win)
{
	touchwin(p_win);
	wrefresh(p_win);
}

void initWinParams(ROOM *p_win, int height, int width, int init_y, int init_x)
{
	if (p_win->is_passage) // TODO change -- only works for horizontal passages.
	{
		p_win->height = height;
		p_win->width = width;
		p_win->starty = init_y;
		p_win->startx = init_x + p_win->width;

		p_win->border.ls = '|'; // ACS_VLINE;
		p_win->border.rs = '|'; // ACS_VLINE;
		p_win->border.ts = '-'; // ACS_HLINE;
		p_win->border.bs = '-'; // ACS_HLINE;
		p_win->border.tl = '+'; // ACS_LLCORNER;
		p_win->border.tr = '+'; // ACS_LRCORNER;
		p_win->border.bl = '+'; // ACS_ULCORNER;
		p_win->border.br = '+'; // ACS_URCORNER;
	}
	else
	{
		p_win->height = height;
		p_win->width = width;
		p_win->starty = init_y;
		p_win->startx = init_x;

		p_win->border.ls = '|'; // ACS_VLINE;
		p_win->border.rs = '|'; // ACS_VLINE;
		p_win->border.ts = '-'; // ACS_HLINE;
		p_win->border.bs = '-'; // ACS_HLINE;
		p_win->border.tl = '+'; // ACS_ULCORNER;
		p_win->border.tr = '+'; // ACS_URCORNER;
		p_win->border.bl = '+'; // ACS_LLCORNER;
		p_win->border.br = '+'; // ACS_LRCORNER;
	}
}

void printWinParams(ROOM *p_win)
{
#ifdef _DEBUG
	mvprintw(25, 0, "%d %d %d %d", p_win->startx, p_win->starty,
			 p_win->width, p_win->height);
	refresh();
#endif
}

void drawBoxBorder(ROOM *p_win, bool flag)
{
	int i, j;
	int x, y, w, h;

	x = p_win->startx;
	y = p_win->starty;
	w = p_win->width;
	h = p_win->height;

	if (flag == TRUE)
	{
		mvaddch(y, x, p_win->border.tl);		 // TOP LEFT CORNER
		mvaddch(y, x + w, p_win->border.tr);	 // TOP RIGHT CORNER
		mvaddch(y + h, x, p_win->border.bl);	 // BOTTOM LEFT CORNER
		mvaddch(y + h, x + w, p_win->border.br); // BOTTOM RIGHT CORNER

		mvhline(y, x + 1, p_win->border.ts, w - 1);		// TOP HORIZONTAL LINE
		mvhline(y + h, x + 1, p_win->border.bs, w - 1); // BOTTOM HORIZONTAL LINE
		mvvline(y + 1, x, p_win->border.ls, h - 1);		// LEFT HORIZONTAL LINE
		mvvline(y + 1, x + w, p_win->border.rs, h - 1); // RIGHT HORIZONTAL LINE
	}													// erase
	else
		for (j = y; j <= y + h; ++j)
			for (i = x; i <= x + w; ++i)
				mvaddch(j, i, ' ');

	refresh();
}

void drawBoxFull(ROOM *p_win, bool flag)
{
	int i, j;
	int x, y, w, h;

	x = p_win->startx;
	y = p_win->starty;
	w = p_win->width;
	h = p_win->height;

	if (flag == TRUE)
	{
		for (j = y; j < y + h; ++j)
			for (i = x; i < x + w; ++i)
				mvaddch(j, i, '#');
	} // erase
	else
		for (j = y; j <= y + h; ++j)
			for (i = x; i <= x + w; ++i)
				mvaddch(j, i, ' ');

	refresh();
}

bool valueInRange(int value, int min, int max)
{
	return (value >= min) && (value <= max);
}

bool rectOverlap(ROOM A, ROOM B)
{
	bool xOverlap = valueInRange(A.startx, B.startx, B.startx + B.width) ||
					valueInRange(B.startx, A.startx, A.startx + A.width);

	bool yOverlap = valueInRange(A.starty, B.starty, B.starty + B.height) ||
					valueInRange(B.starty, A.starty, A.starty + A.height);

	return xOverlap && yOverlap;
}

bool checkAllOverlap(ROOM *rooms, int n)
{
	ROOM A = rooms[n];
	for (int i = 0; i < n; i++)
	{
		ROOM B = rooms[i];
		if (rectOverlap(A, B))
		{
			return TRUE;
		}
	}
	return FALSE;
}

void layoutRooms(ROOM *rooms, int num, int MAP_HEIGHT, int MAP_WIDTH)
{
	int ROOM_MIN_WIDTH = 5;
	int ROOM_MIN_HEIGHT = 5;
	int ROOM_MAX_WIDTH = 20;
	int ROOM_MAX_HEIGHT = 5;
	int width, height, startx, starty, n;

	width = rand() % (ROOM_MAX_WIDTH + 1);
	height = rand() % (ROOM_MAX_HEIGHT + 1);

	startx = rand() % (MAP_WIDTH + 1) + 1;
	starty = rand() % (MAP_HEIGHT + 1) + 1;
	rooms[0].is_passage = FALSE;

	initWinParams(&rooms[0], height, width, starty, startx);

	for (n = 0; n < num; n++)
	{
		do
		{
			width = ROOM_MIN_WIDTH + rand() % (ROOM_MAX_WIDTH + 1 - ROOM_MIN_WIDTH);
			height = ROOM_MIN_HEIGHT + rand() % (ROOM_MAX_HEIGHT + 1 - ROOM_MIN_WIDTH);

			startx = width + rand() % ((MAP_WIDTH - (width + 5)) - width); // rand()%((nMax+1)-nMin) + nMin;
			starty = height + rand() % ((MAP_HEIGHT - (height + 5)) - height);
			rooms[n].is_passage = FALSE;

			initWinParams(&rooms[n], height, width, starty, startx);

		} while (checkAllOverlap(rooms, n));
	}
}

void assignNumConnections(ROOM *rooms, int N_ROOMS, int MAX_CONN_NUM)
{
	for (int i = 0; i < N_ROOMS; i++)
	{
		rooms[i].connects = rand() % ((MAX_CONN_NUM + 1) - 2) + 2; // rand()%((nMax+1)-nMin) + nMin;
		int *closest = malloc(rooms[i].connects * sizeof(int));
		rooms[i].closest = closest;
	}
}

void assignRandomClosest(ROOM *rooms, int N_ROOMS)
{
	for (int i = 0; i < N_ROOMS; i++)
	{
		for (int j = 0; j < rooms[i].connects; j++)
		{
			int k = rand() % (N_ROOMS);
			k == i ? MAX(i + 1, N_ROOMS - 1) : k;
			rooms[i].closest[j] = k;
		}
	}
}

void getCenters(ROOM *rooms, int N_ROOMS)
{
	for (int i = 0; i < N_ROOMS; i++)
	{
		rooms[i].centerx = rooms[i].startx + rooms[i].width / 2;
		rooms[i].centery = rooms[i].starty + rooms[i].height / 2;
	}
}

int cmpfunc(const void *a, const void *b)
{ // for qsort
	return (*(int *)a - *(int *)b);
}

void getDistancesToClosest(ROOM *rooms, int N_ROOMS) // THIS IS WRONG
{
	int distancesCenter[N_ROOMS][N_ROOMS];
	int *original = malloc(N_ROOMS * sizeof(int));

	for (int i = 0; i < N_ROOMS; i++)
	{
		for (int j = 0; j < N_ROOMS; j++)
		{
			distancesCenter[i][j] = (rooms[i].centerx - rooms[j].centerx) * (rooms[i].centerx - rooms[j].centerx) +
									(rooms[i].centery - rooms[j].centery) * (rooms[i].centery - rooms[j].centery);
		}
		memcpy(original, distancesCenter[i], N_ROOMS * sizeof(int));
		qsort(distancesCenter[i], N_ROOMS, sizeof(int), cmpfunc);

		for (int j = 0; j < rooms[i].connects; j++)
		{
			int k = 0;
			do {
					k == i ? i+1 : i;
					if (distancesCenter[i][j] == original[k])
					{
						rooms[i].closest[j] = k;
					}
					k++;
			} while (k < N_ROOMS);
		}
	}
}

void drawLine(int starty, int startx, int finaly, int finalx)
{
	int diffy = finaly - starty;
	int diffx = finalx - startx;
	switch (diffy > 0)
	{
	case TRUE: 
		for (starty; starty <= finaly; starty++)
		{
			mvaddch(starty, startx, '#');
		}
		break;
	case FALSE:
		for (starty; starty >= finaly; starty--)
		{
			mvaddch(starty, startx, '#');
		}
		break;
	}

	switch(diffx > 0 )
	{
	case TRUE: 
		for (startx; startx < finalx; startx++)
		{
			mvaddch(starty, startx, '#');
		}
		break;
	case FALSE:
		for (startx; startx > finalx; startx--)
		{
			mvaddch(starty, startx, '#');
		}
		break;
	}
}

void drawConnections(ROOM *rooms, int N_ROOMS)
{
	int distx, disty;
	for (int i = 0; i < N_ROOMS; i++)
	{
		for (int j = 0; j < rooms[i].connects; j++)
		{
			distx = rooms[rooms[i].closest[j]].centerx - rooms[i].centerx;
			disty = rooms[rooms[i].closest[j]].centery - rooms[i].centery;
			drawLine(rooms[i].centery, rooms[i].centerx, rooms[i].centery + disty, rooms[i].centerx + distx);
		}
	refresh();
	}
	// initWinParams(&rooms[n], height, width, starty, startx);
}
