#include<stdlib.h>
#include<locale.h>
#include<string.h>
#include<ncurses.h>
#include<readline/readline.h>
#include<readline/history.h>

WINDOW *dwin;
WINDOW *win;
unsigned char inc,avail=0; /*input char*/
int isavail() {return avail;}

int sh=0; /*quick and dirty hack: this var contains y coord. of line at which current input line begins; it is needed for redisplay func. */

int rlgetc(FILE *dummy) {
	avail=0;
	return inc;
}

void pchar(unsigned char c) {
	/*some symbols like KEY_UP and so on handler*/
	//else {
	//}
	inc=c;
	avail=1;
	rl_callback_read_char();
}

void redisplay(void) {
	int cy=-1,cx=-1;
	unsigned int in=0;
	int pcy=-1,pcx=-1;
	int prev_col = 0;
	int height = 1;
	wmove (win,sh,0);
	for (in=0;rl_display_prompt && rl_display_prompt[in];in++) {
		waddch(win,rl_display_prompt[in]);
		getyx(win,cy,cx);
		if (cx<prev_col) height++;
		prev_col=cx;
	}
	for (in=0;in<rl_end;in++) {
		unsigned char c=(unsigned char)rl_line_buffer[in];
		if (in==rl_point) getyx(win,pcy,pcx);
		if (CTRL_CHAR (c) || c == RUBOUT) {
			waddch (win,'^');
			waddch (win,CTRL_CHAR (c) ?  UNCTRL (c) : '?');
		} else waddch (win,c);
		getyx (win,cy,cx);
		if (cx < prev_col) height++;
		prev_col = cx;
	}
	wclrtobot(win);
	getyx (win,sh,cx);
	if (pcy>=0) wmove (win,pcy,pcx);
	sh-=height-1;
}

void shandle(char *buf) {
	waddch(win,'\n');
	rl_on_new_line(); 
	int cy,cx;getyx(win,cy,cx); sh=cy;
	if (buf && *buf) {
		add_history(buf);
		wprintw(dwin,"%s\n",buf); wrefresh(dwin);
		free(buf);
	}
}

void initrl() {
	rl_catch_signals = 0;
	rl_catch_sigwinch = 0;
	rl_deprep_term_function = NULL;
	rl_prep_term_function = NULL;
	rl_change_environment=0;
	rl_getc_function=rlgetc;
	rl_input_available_hook=isavail;
	rl_redisplay_function=redisplay;
	rl_callback_handler_install("\\> ",shandle);
	int cy,cx;getyx(win,cy,cx);
	sh=cy;
}

int main(void) {
	setlocale(LC_ALL,"");
	int c=0;
	initscr();
	cbreak();
	noecho();
	curs_set(2);
	printw("%d,%d\n",COLS,LINES);
	refresh();
	int w=80,h=25;
	int sy=(LINES-h)/2;
	int sx=(COLS-w)/2;
	WINDOW *win1=newwin(h+2,w+2,sy+1,sx+1);
	win=derwin(win1,h,w,1,1);
	box(win1, 0, 0);
	wrefresh(win1);
	wmove(win,0,0);
	scrollok(win,TRUE);
	dwin=newwin(110,80,3,0);
	wrefresh(dwin);
	wmove(dwin,0,0);
	scrollok(dwin,TRUE);
	initrl();
	while((c = wgetch(win)) != 'q') pchar(c);
	rl_set_prompt((char *)NULL);
	rl_callback_handler_remove();
	rl_free_keymap(rl_get_keymap());
	//rl_cleanup_after_signal();
	//rl_free_line_state();

	delwin(win);
	delwin(win1);
	echo();
	endwin();
	return 0;
}
