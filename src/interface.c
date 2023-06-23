#include "interface_internal.h"

#define WIN_WIDTH_RATIO 70
#define WIN_HEIGHT_RATIO 50

/**
 * Functions declaration
*/

/**
 * Const string to print
*/
const char* figlet = "  ____                                ____ \n / ___|___  _ __ ___  _ __  _ __ ___ / ___|\n| |   / _ \\| '_ ` _ \\| '_ \\| '__/ _ \\ |    \n| |__| (_) | | | | | | |_) | | |  __/ |___ \n \\____\\___/|_| |_| |_| .__/|_|  \\___|\\____|\n                     |_|                   \n";

const char* MAIN_OPTIONS_PROTECTED[5] ={"4","BruteForce", "Password", "Explore", "Exit"};
const char* MAIN_OPTIONS[3] ={"2","Explore", "Exit"};
const char** currentOptionsSet;

int protectedFlag = 0;
int passwordFlag = 0;

const char * localFilepath;

char interfacePassword[100] = "";

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

/**
 * init(int isProtected, char* password)
 * isProtected: boolean to know if the zip is protected
 * password: the password of the zip
*/
void init(int isProtected, char* password){
	protectedFlag = isProtected;
	passwordFlag = strlen(password) > 0;

	if(isProtected && !passwordFlag)
		currentOptionsSet = MAIN_OPTIONS_PROTECTED;
	else
		currentOptionsSet = MAIN_OPTIONS;

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
	wprintw(figletWin,"%s",figlet);

    if(isProtected){
        mvprintw(7,1,"🔒 Zip protected.");
    }
    else{
        mvprintw(7,1,"🔓 Zip not protected.");
    }
    if(passwordFlag){
        mvprintw(8,1,"🔑 Password provided.");
    }

	//Refresh the main window
	refresh();
	//Refresh the figlet window
	wrefresh(figletWin);
}

/**
 * initBorderWindow(WINDOW* win)
 * win: the window to enhance
*/
void initBorderWindow(WINDOW* win)
{	
	box(win, 0 , 0);
}

/**
 * initMainWindow(WINDOW* win)
 * win: the window to enhance
*/
void initMainWindow(WINDOW* win){
	printMainOptionsInWindow(win, currentOptionsSet, atoi(currentOptionsSet[0]));
}

/**
 * Window utils functions
*/

/**
 * cleanWindowContent(WINDOW *win)
 * win: the window to clean
*/
void cleanWindowContent(WINDOW *win){
	wclear(win);
	wrefresh(win);
}

/**
 * printMainOptionsInWindow(WINDOW *win, const char **options, int size)
 * win: the window to print in
 * options: the options to print
 * size: the size of the options array
*/
void printMainOptionsInWindow(WINDOW *win, const char **options, int size){
	//Compute the middle of the local window
	int middleY = getmaxy(win) / 2;
	int middleX = getmaxx(win) / 2;
	//Print the description of this window
	const char* description = "Select an option (<- or ->) and press Enter";
	mvwprintw(win, 1, middleX - (strlen(description) / 2), "%s", description);
	//Compute the offset between each options horizontally in the local window
	int offset = spaceBetweenEachOption(win, options);
	// Little adjustment for main options, it's hard
	if(currentOptionsSet == MAIN_OPTIONS){
		int percent = 32;
		int toReduce = offset * percent / 100;
		offset-=toReduce;
	}
	//Print the options horizontally in the local window with the same offset between each options
	for(int i = 1; i <= size; i++){
		if(i == selectedOption){
			//Highlight the selected option
			wattron(win, A_REVERSE);
			mvwprintw(win, middleY, 1 + (i * offset), "%s", options[i]);
			wattroff(win, A_REVERSE);
		}else{
			wattron(win, A_BOLD);
			wattron(win, A_UNDERLINE);
			mvwprintw(win, middleY, 1 + (i * offset), "%s",options[i]);
			wattroff(win, A_UNDERLINE);
			wattroff(win, A_BOLD);
		}
	}
	
	wrefresh(win);
	refresh();
	
}

/**
 * drawPasswordBox(WINDOW* win)
 * win: the window to draw in
*/
void drawPasswordBox(WINDOW* win){
	int middleY = getmaxy(win) / 2;
	char underline[1080] = "";
	for(int i = 0; i < getmaxx(win)-2; i++){
		underline[i] = '-';
	}
	//Underline the password characters
	mvwprintw(win, middleY + 1, 1, "%s", underline);

	//Borders for the password
	//First Line
	mvwaddch(win, middleY-1, 0, ACS_ULCORNER);
	for(int i = 1; i < getmaxx(win)-1; i++){
		mvwaddch(win, middleY-1, i, ACS_HLINE);
	}
    mvwaddch(win, middleY-1, getmaxx(win) - 1, ACS_URCORNER);
	//Left and Right borders
	mvwaddch(win, middleY, 0, ACS_VLINE);
    mvwaddch(win, middleY, getmaxx(win) - 1, ACS_VLINE);
	
	mvwaddch(win, middleY+1, 0, ACS_VLINE);
    mvwaddch(win, middleY+1, getmaxx(win) - 1, ACS_VLINE);
	//Last Line
	mvwaddch(win, middleY+2, 0, ACS_LLCORNER);
	for(int i = 1; i < getmaxx(win)-1; i++){
		mvwaddch(win, middleY+2, i, ACS_HLINE);
	}
	mvwaddch(win, middleY+2, getmaxx(win) - 1, ACS_LRCORNER);

}

/**
 * printPasswordOptionsInWindow(WINDOW *win)
 * win: the window to print in
*/
void printPasswordOptionsInWindow(WINDOW *win){
	//Compute the middle of the local window
	int middleY = getmaxy(win) / 2;
	int middleX = getmaxx(win) / 2;
	
	//Print the description of this window
	const char* description = "Enter your password here";
	mvwprintw(win, 1, middleX - (strlen(description) / 2), "%s",description);
	//Reallow the input buffering and echo user's input
	nocbreak();
	echo();
	
	drawPasswordBox(win);
	//Get the password from the user
	mvwgetnstr(win, middleY, 1, interfacePassword,100);
	if(isPasswordCorrect(localFilepath, interfacePassword)){
		char* passwordCorrectMessage = "Password correct! Zip file unlocked!";
		mvwprintw(win, getmaxy(win) - 3, middleX - (strlen(passwordCorrectMessage) / 2), "%s",passwordCorrectMessage);

		char* indicationMessage = "Press Enter to continue.";
		mvwprintw(win, getmaxy(win) - 2, middleX - (strlen(indicationMessage) / 2), "%s",indicationMessage);

		currentOptionsSet = MAIN_OPTIONS;
	}
	else{
		//Reset the buffer
		memset(interfacePassword, 0, sizeof(interfacePassword));
		//Prompt the user that the password is incorrect
		char* passwordIncorrectMessage = "Password incorrect! Try again!";
		mvwprintw(win, getmaxy(win) - 3, middleX - (strlen(passwordIncorrectMessage) / 2), "%s",passwordIncorrectMessage);

		char* indicationMessage = "Press Enter to continue.";
		mvwprintw(win, getmaxy(win) - 2, middleX - (strlen(indicationMessage) / 2), "%s",indicationMessage);
	}

	//And disable the input buffering and echo user's input
	noecho();
	cbreak();

	wrefresh(win);
	refresh();
	
	//Wait until the user press enter
	char c = getch();
	while(c != KEY_ENTER && c != 10)
		c = getch();
	
	cleanWindowContent(win);
	printMainOptionsInWindow(win, currentOptionsSet, atoi(currentOptionsSet[0]));
}

void bruteForce(WINDOW* win, const char* filePath){
	//Compute the middle of the local window
	int middleY = getmaxy(win) / 2;
	int middleX = getmaxx(win) / 2;
	//Print the description of this window
	const char* description = "BruteForcing the password...";
	mvwprintw(win, 1, middleX - (strlen(description) / 2), "%s",description);

	int bruteMaxSize = 100;
	char currentPassword[100] = "a";
	//Code that initialise the variable with all string combinations in loop
	int i = 0;
	while(i < bruteMaxSize){
		//password Incrementation
		if(currentPassword[i] == 'z'){
			if(i>0){
				int y = i - 1;
				if(currentPassword[y] == 'z'){
					while(currentPassword[y] == 'z'){
						if(y > 0)
							y--;
						else
							break;
						currentPassword[y+1] = 'a';
					}
					if(y > 0){
						currentPassword[y]++;
					}
					else if(y == 0){
						if(currentPassword[y] == 'z'){
							currentPassword[y] = 'a';
							i++;
						}
						else{
							currentPassword[y]++;
						}
					}
					
					currentPassword[i] = 'a';
					currentPassword[i-1] = 'a';
				}
				else{
					currentPassword[y]++;

					currentPassword[i] = 'a';
				}
			}
			else{
				currentPassword[i] = 'a';
				i++;
				currentPassword[i] = 'a';
			}
		}
		else{
			currentPassword[i]++;
		}
		wmove(win, middleY, middleX);
		wclrtoeol(win);
		wattron(win, A_BOLD);
		mvwprintw(win, middleY, middleX -(strlen(currentPassword)/2), "%s",currentPassword);
		wattroff(win, A_BOLD);
		wrefresh(win);
		//Check if the password is correct
		if(isPasswordCorrect(filePath, currentPassword)){
			currentOptionsSet = MAIN_OPTIONS;
			for(int j = 0; j <= i; j++)
				interfacePassword[j] = currentPassword[j];
			break;
		}
	}
	wattron(win, A_BOLD);
	wattron(win, A_UNDERLINE);
	char* foundMessage = "Found! Press Enter to continue.";
	mvwprintw(win, getmaxy(win)-3,middleX - (strlen(foundMessage)/2),"%s",foundMessage);
	wattroff(win, A_UNDERLINE);
	wattroff(win, A_BOLD);
	wrefresh(win);
	//Wait until the user press enter
	char c = getch();
	while(c != KEY_ENTER && c != 10)
		c = getch();
	
	cleanWindowContent(win);
	printMainOptionsInWindow(win, currentOptionsSet, atoi(currentOptionsSet[0]));
}

/**
 * updateWindow(WINDOW *win, const char **options, int size)
 * win: the window to update
 * options: the options to print
 * size: the size of the options array
*/
void updateWindow(WINDOW *win, const char **options, int size){

	cleanWindowContent(win);
	printMainOptionsInWindow(win, options, size);
}

/**
 * createGenericWindow(void(*winFunc)(WINDOW*))
 * winFunc: the function to enhance the window
 * return: the enhanced window
*/
WINDOW* createGenericWindow(void(*winFunc)(WINDOW*)){
	int startx, starty,width, height, termWidth, termHeight;
	 
	//Get the size of the terminal
	getmaxyx(stdscr, termHeight, termWidth);
	//Fix the window size from ratio
	width = (termWidth * WIN_WIDTH_RATIO) / 100;
	height = (termHeight * WIN_HEIGHT_RATIO) / 100;
	
	//Compute startx and starty
	startx = (termWidth - width) / 2;
	starty = (termHeight - height) / 2 + 4; // Middle of the terminal, +4 to have a little offset
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

/**
 * charNumber(const char** options)
 * options: the options array to count
 * return: the number of characters in the options array
*/
int charNumber(const char** options){
	int number = 0;
	for(int i = 1; i <= atoi(options[0]);i++){
		number+=strlen(options[i]);
	}
	return number;
}

/**
 * spaceBetweenEachOption(WINDOW* win, const char** options)
 * win: the window to compute the space
 * options: the options array to count
 * return: the space between each options
*/
int spaceBetweenEachOption(WINDOW* win, const char** options){
	int charNum = charNumber(options);
	return (getmaxx(win) - charNum) / atoi(options[0]);
}

void mainOptionsProtectedManager(){
	switch (selectedOption)
	{
		case 1:
			//BruteForce
			cleanWindowContent(main_win);
			bruteForce(main_win, localFilepath);
			break;
		case 2:
			//Password
			cleanWindowContent(main_win);
			printPasswordOptionsInWindow(main_win);
			break;
		case 3:
			//Explore
			break;
		case 4:
			closeApp();
			exit(0);
		default:
			break;
	}
}

void mainOptionsManager(){
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
}

/**
 * keypadManager(int key)
 * key: the key pressed by the user
*/
void keypadManager(int key){
	switch (key)
	{
	case KEY_RIGHT:
		//Select the next option
		if(selectedOption < atoi(currentOptionsSet[0])){
			selectedOption++;
			updateWindow(main_win, currentOptionsSet, atoi(currentOptionsSet[0]));

		}
		break;
	case KEY_LEFT:
		//Select the previous option
		if(selectedOption > 1){
			selectedOption--;
			updateWindow(main_win, currentOptionsSet, atoi(currentOptionsSet[0]));
		}
		break;
	case KEY_ENTER:
	case 10:
		if(currentOptionsSet == MAIN_OPTIONS_PROTECTED){
			mainOptionsProtectedManager();
		}
		else if(currentOptionsSet == MAIN_OPTIONS){
			mainOptionsManager();
		}
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

/**
 * launchInterface(const char* filePath, int isProtected, char* password)
 * filePath: the path of the zip file
 * isProtected: boolean to know if the zip is protected
 * password: the password of the zip
*/
void launchInterface(const char* filePath, int isProtected, char* password){
    //Start curses mode
	initscr();
	localFilepath = filePath;
	init(isProtected, password);
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