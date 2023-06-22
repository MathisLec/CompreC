#include <ncurses.h>
#include "main.h"
#include "interface.h"
#include "zipUtils.h"

/**
 * Init functions
*/
void init(int isProtected, int hasPassword);
void initBorderWindow(WINDOW* win);
void initMainWindow(WINDOW* win);

/**
 * Window utils functions
*/
void cleanWindowContent(WINDOW *win);
void printMainOptionsInWindow(WINDOW *win, const char **options, int size);
void drawPasswordBox(WINDOW* win);
void printPasswordOptionsInWindow(WINDOW *win);
void updateWindow(WINDOW *win, const char **options, int size);
WINDOW* createGenericWindow(void(*winFunc)(WINDOW*));

/**
 * Application General utils functions
*/
int charNumber(const char** options);
int spaceBetweenEachOption(WINDOW* win, const char** options);
void mainOptionsProtectedManager();
void mainOptionsManager();
void keypadManager(int key);
void freeApp();
void closeApp();