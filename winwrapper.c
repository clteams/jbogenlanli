#include<ncurses.h>
#include<locale.h>

struct cbox {
	WINDOW *derwin,win
};

	int w=80,h=25;
	int sy=(LINES-h)/2;
	int sx=(COLS-w)/2;
	WINDOW *win1=newwin(h+2,w+2,sy+1,sx+1);
	WINDOW *win=derwin(win1,h,w,1,1);
	box(win1, 0, 0);
	wrefresh(win1);
	wmove(win,0,0);
	scrollok(win,TRUE);
	delwin(win);
	delwin(win1);
