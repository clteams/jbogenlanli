#include<locale.h>
#include<ncurses.h>
#include <readline/history.h>
#include <readline/readline.h>


struct fline {
	unsigned int len;
	wchar_t *s;
};

int /*fn*/(const char *fname) {
	FILE *fp=fopen(fname,"r");
	wchar;
}

int yoffset=0,xoffset=0;

int main(WINDOW *win) {
	while((c = wgetch(win)) != 'q') {
		int wx,wy; getmaxyx(win,wy,wx);
		switch(c) {
			case KEY_DOWN: if (length>yoffset+wy) {yoffset++; redraw();} break;
			case KEY_UP: if (yoffset) {yoffset--; redraw();} break;
			case KEY_LEFT: if (yoffset) {yoffset--; redraw();}
			case KEY_RIGHT:
				int lsz=str//?
				for (i=yoffset+1;i<offset+wy;i++) if ([i]>lsz) lsz=[i];
				if (xoffset+wx<lsz) {xoffset++; redraw();}
				break;
		}
		//wprintw(win,"%c",c);
		//int x,y; getyx(win,y,x);
		//mvwprintw(win,0,0,"asd");
		//wmove(win,y,x);
		//wprintw(win,"%d,%d",y,x);
	}
	delwin(win);
	delwin(win1);
	echo();
	endwin();
	return 0;
}
