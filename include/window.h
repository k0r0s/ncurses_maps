#ifndef WINDOW_H
#define WINDOW_H 

#define MAX(a,b) ((a) > (b) ? (a) : (b))
#define MIN(a,b) ((a) < (b) ? (a) : (b))
#define CLAMP(a) ((a) < 0 ? 0: (a))

typedef struct _win_border_struct {
	chtype 	ls, rs, ts, bs, 
	 	tl, tr, bl, br;
}WIN_BORDER;

typedef struct _ROOM_struct {

	int startx, starty;
	int height, width;
	bool is_passage;
	WIN_BORDER border;
}ROOM;

void toggleWin(WINDOW *p_win);
void initWinParams(ROOM *p_win, int height, int width, int init_y, int init_x);
void printWinParams(ROOM *p_win);
void createBoxBorders(ROOM *win, bool flag);
void createBoxFull(ROOM *win, bool flag);

bool valueInRange(int value, int min, int max);
bool rectOverlap(ROOM A, ROOM B);
bool checkAllOverlap(ROOM * rooms,int n);
void layoutRooms(ROOM * rooms, int num, int MAP_HEIGHT, int MAP_WIDTH);

#endif
