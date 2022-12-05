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

void toggle_win(WINDOW *p_win);
void init_win_params(ROOM *p_win, int height, int width, int init_y, int init_x);
void print_win_params(ROOM *p_win);
void create_box_borders(ROOM *win, bool flag);
void create_box_full(ROOM *win, bool flag);

bool valueInRange(int value, int min, int max);
bool rectOverlap(ROOM A, ROOM B);
bool checkAllOverlap(ROOM * rooms,int n);
void layout_rooms(ROOM * rooms, int num, int MAP_HEIGHT, int MAP_WIDTH);

#endif
