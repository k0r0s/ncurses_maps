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
	int centerx, centery;
	bool is_passage;
	int connects;
	int * closest;
	WIN_BORDER border;
}ROOM;

static bool m_done;

void setup();
void teardown();
int getKey();
void startDraw();
void endDraw();
bool isDone();
void quit();
void titleScreen(WINDOW *p_win);


void toggleWin(WINDOW *p_win);
void initWinParams(ROOM *p_win, int height, int width, int init_y, int init_x);
void printWinParams(ROOM *p_win);
void drawBoxBorder(ROOM *win, bool flag);
void drawBoxFull(ROOM *win, bool flag);

bool valueInRange(int value, int min, int max);
bool rectOverlap(ROOM A, ROOM B);
bool checkAllOverlap(ROOM * rooms,int n);
void layoutRooms(ROOM * rooms, int num, int MAP_HEIGHT, int MAP_WIDTH);
void assignNumConnections(ROOM * rooms, int N_ROOMS, int MAX_CONN_NUM);
void assignRandomClosest(ROOM * rooms, int N_ROOMS);
void getCenters(ROOM * rooms, int N_ROOMS);
int cmpfunc (const void * a, const void * b);
void getDistancesToClosest(ROOM * rooms, int N_ROOMS);
void drawConnections(ROOM * rooms, int N_ROOMS);

#endif
