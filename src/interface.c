#include <ncurses.h>
#define WIN_WIDTH_RATIO 70
#define WIN_HEIGHT_RATIO 50

/**
 * Functions declaration
*/
WINDOW *create_newwin(int height, int width, int starty, int startx);
void printOptionsInWindow(WINDOW *win, const char **options, int size);
void updateWindow(WINDOW *win, const char **options, int size);
void cleanWindowContent(WINDOW *win);
WINDOW* createGenericWindow(WINDOW*(*winFunc)(WINDOW*));
void initMainWindow(WINDOW* win);
void initBorderWindow(WINDOW* win);
void keypadManager(int key);

/**
 * Const string to print
*/
const char* figlet = "  ____                                ____ \n / ___|___  _ __ ___  _ __  _ __ ___ / ___|\n| |   / _ \\| '_ ` _ \\| '_ \\| '__/ _ \\ |    \n| |__| (_) | | | | | | |_) | | |  __/ |___ \n \\____\\___/|_| |_| |_| .__/|_|  \\___|\\____|\n                     |_|                   \n";

const char* MAIN_OPTIONS_WITH_PASSWORD[5] ={"4","BruteForce", "Password", "Explore", "Exit"};
const char* MAIN_OPTIONS[3] ={"2","Explore", "Exit"};

/**
 * Global windows and variables
*/
WINDOW* border_win;
WINDOW* main_win;
int selectedOption = 1;

/**
 * Functions implementation
*/

/**
 * Init functions
*/

void init(){
	//Disable cursor
	curs_set(0);

	/**
	 * Print in the general window
	*/
	//Print exit key
	printw("Press F1 to exit\n");
	
	//Get the middle of the terminal to print the figlet (with a little offset)
	int middlex = (getmaxx(stdscr) / 2) - 22;
	//Create a new window in the middle of the terminal to print the figlet
	WINDOW* figletWin = newwin(10, 86, 1, middlex);
	wprintw(figletWin, figlet);

	//Refresh the main window
	refresh();
	//Refresh the figlet window
	wrefresh(figletWin);
}

void initBorderWindow(WINDOW* win)
{	
	box(win, 0 , 0);
}

void initMainWindow(WINDOW* win){
	printOptionsInWindow(win, MAIN_OPTIONS, atoi(MAIN_OPTIONS[0]));
}

/**
 * Window utils functions
*/

void cleanWindowContent(WINDOW *win){
	wclear(win);
	wrefresh(win);
}

void printOptionsInWindow(WINDOW *win, const char **options, int size){
	//Compute the middle of the local window
	int middleY = getmaxy(win) / 2;
	int middleX = getmaxx(win) / 2;
	//Compute the offset between each options horizontally in the local window
	int offset = getmaxx(win) / size;
	//Print the description of this window
	const char* description = "Select an option (<- or ->) and press Enter";
	mvwprintw(win, 1, middleX - (strlen(description) / 2), description);
	//Print the options horizontally in the local window with the same offset between each options
	for(int i = 1; i <= size; i++){
		if(i == selectedOption){
			//Highlight the selected option
			wattron(win, A_REVERSE);
			mvwprintw(win, middleY, 1 + (i * offset)/size, options[i]);
			wattroff(win, A_REVERSE);
		}else{
			mvwprintw(win, middleY, 1 + (i * offset)/size, options[i]);
		}
	}
	
	wrefresh(win);
	
}

void updateWindow(WINDOW *win, const char **options, int size){

	cleanWindowContent(win);
	printOptionsInWindow(win, options, size);
}

WINDOW* createGenericWindow(WINDOW*(*winFunc)(WINDOW*)){
	int startx, starty,width, height, termWidth, termHeight;
	 
	//Get the size of the terminal
	getmaxyx(stdscr, termHeight, termWidth);
	//Fix the window size from ratio
	width = (termWidth * WIN_WIDTH_RATIO) / 100;
	height = (termHeight * WIN_HEIGHT_RATIO) / 100;
	
	//Compute startx and starty
	startx = (termWidth - width) / 2;
	starty = (termHeight - height) / 2;
	if(winFunc == initBorderWindow){
		startx--;
		starty--;
		//Add 1 to the width and height to have a border
		width+=2;
		height+=2;
	}

	WINDOW* genericWindow = newwin(height, width, starty, startx);
	//Enhance the window
	winFunc(genericWindow);
	wrefresh(genericWindow);
	return genericWindow;

}

/**
 * Application General utils functions
*/

void keypadManager(int key){
	switch (key)
	{
	case KEY_RIGHT:
		//Select the next option
		if(selectedOption < atoi(MAIN_OPTIONS[0])){
			selectedOption++;
			updateWindow(main_win, MAIN_OPTIONS, atoi(MAIN_OPTIONS[0]));
		}
		break;
	case KEY_LEFT:
		//Select the previous option
		if(selectedOption > 1){
			selectedOption--;
			updateWindow(main_win, MAIN_OPTIONS, atoi(MAIN_OPTIONS[0]));
		}
		break;
	case KEY_ENTER:
	case 10:
		//Execute the selected option
		switch (selectedOption)
		{
		case 1:
			//Explore
			break;
		case 2:
			closeApp();
			exit(0);
		default:
			break;
		}
		break;
	default:
		break;
	}
}

void freeApp(){
	delwin(border_win);
	delwin(main_win);
}

void closeApp(){
	freeApp();
	endwin();
}

void launchInterface(){
    //Start curses mode
	initscr();
	init();
	//Disable line buffering
	cbreak();
	//Don't show the user's input
	noecho();
	//Initialize the window
	border_win=createGenericWindow(initBorderWindow);
	main_win=createGenericWindow(initMainWindow);
	//Activate the keypad of the user's terminal			
	
	keypad(stdscr, TRUE);
	int key;
	while((key = getch()) != KEY_F(1))
	{	
		keypadManager(key);
	}
	closeApp();
}