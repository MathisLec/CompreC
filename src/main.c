#include "main.h"
#include <ncurses.h>
#define WIN_WIDTH_RATIO 70
#define WIN_HEIGHT_RATIO 50

const char* MAIN_OPTIONS[4] ={"3","1. New Game", "2. Load Game", "3. Exit"};
WINDOW* main_win;
int selectedOption = 1;

WINDOW *create_newwin(int height, int width, int starty, int startx);
void destroy_win(WINDOW *local_win);

void printOptionsInWindow(WINDOW *win, const char **options, int size){
	//Compute the middle of the local window
	int middleY = (getmaxy(win) / 2) - (size / 2);
	//Compute the offset between each options horizontally in the local window
	int offset = 50;
	//Print the options horizontally in the local window with the same offset between each options
	for(int i = 1; i <= size; i++){
		if(i == selectedOption){
			//Highlight the selected option
			wattron(win, A_REVERSE);
			mvwprintw(win, middleY, 0 + (i-1 * offset), options[i]);
			wattroff(win, A_REVERSE);
		}else{
			mvwprintw(win, middleY, 0 + (i-1 * offset), options[i]);
		}
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

void keypadManager(int key){
	switch (key)
	{
	case KEY_RIGHT:
		//Select the next option
		if(selectedOption < atoi(MAIN_OPTIONS[0])){
			selectedOption++;
		}
		break;
	
	default:
		break;
	}
}

int main(int argc, char *argv[])
{
	initWindow(main_win);

	int key;
	while((key = getch()) != KEY_F(1))
	{	
		keypadManager(key);
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