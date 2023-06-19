#include "main.h"
#include <ncurses.h>
#define WIN_WIDTH_RATIO 70
#define WIN_HEIGHT_RATIO 50

const char* MAIN_OPTIONS[4] ={"3","1. New Game", "2. Load Game", "3. Exit"};

WINDOW *create_newwin(int height, int width, int starty, int startx);
void destroy_win(WINDOW *local_win);

void printOptionsInWindow(WINDOW *win, const char **options, int size){
	int i;
	for(i = 1; i < size; i++){
		mvwprintw(win, i + 1, 1, options[i]);
	}
	wrefresh(win);
}

void initWindow(WINDOW *win){
	int startx, starty,width, height, termWidth, termHeight;
	//Start curses mode
	initscr();
	//Disable line buffering
	cbreak();
	//Activate the keypad of the user's terminal			
	keypad(stdscr, TRUE); 
	//Get the size of the terminal
	getmaxyx(stdscr, termHeight, termWidth);
	//Fix the window size from ratio
	width = (termWidth * WIN_WIDTH_RATIO) / 100;
	height = (termHeight * WIN_HEIGHT_RATIO) / 100;
	
	//Compute startx and starty
	startx = (termWidth - width) / 2;
	starty = (termHeight - height) / 2;

	printw("Press F1 to exit");
	refresh();
	win = create_newwin(height, width, starty, startx);
	printOptionsInWindow(win, MAIN_OPTIONS, atoi(MAIN_OPTIONS[0]));
}

int main(int argc, char *argv[])
{
	WINDOW* main_win;
	initWindow(main_win);

	int ch;
	while((ch = getch()) != KEY_F(1))
	{	switch(ch)
		{	case KEY_LEFT:
				//destroy_win(my_win);
				//my_win = create_newwin(height, width, starty,--startx);
				break;
			case KEY_RIGHT:
				//destroy_win(my_win);
				//my_win = create_newwin(height, width, starty,++startx);
				break;
			case KEY_UP:
				//destroy_win(my_win);
				//my_win = create_newwin(height, width, --starty,startx);
				break;
			case KEY_DOWN:
				//destroy_win(my_win);
				//my_win = create_newwin(height, width, ++starty,startx);
				break;	
		}
	}
	//End curses mode
	endwin();
	return 0;
}

WINDOW *create_newwin(int height, int width, int starty, int startx)
{	WINDOW *local_win;

	local_win = newwin(height, width, starty, startx);
	box(local_win, 0 , 0);		/* 0, 0 gives default characters 
					 * for the vertical and horizontal
					 * lines			*/
	wrefresh(local_win);		/* Show that box 		*/

	return local_win;
}

void destroy_win(WINDOW *local_win)
{	
	/* box(local_win, ' ', ' '); : This won't produce the desired
	 * result of erasing the window. It will leave it's four corners 
	 * and so an ugly remnant of window. 
	 */
	wborder(local_win, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
	/* The parameters taken are 
	 * 1. win: the window on which to operate
	 * 2. ls: character to be used for the left side of the window 
	 * 3. rs: character to be used for the right side of the window 
	 * 4. ts: character to be used for the top side of the window 
	 * 5. bs: character to be used for the bottom side of the window 
	 * 6. tl: character to be used for the top left corner of the window 
	 * 7. tr: character to be used for the top right corner of the window 
	 * 8. bl: character to be used for the bottom left corner of the window 
	 * 9. br: character to be used for the bottom right corner of the window
	 */
	wrefresh(local_win);
	delwin(local_win);
}