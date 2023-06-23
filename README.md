# CompreC

## Dependencies
### BASH
- cmake
- make

### C
- stdlib.h
- stdio.h
- string.h
- ncurses.h
- zip.h
- getopt.h
- locale.h

## Install
```bash
./install.sh
```
This script will automatically compile and assemble the c files

## Clean
```bash
./clean.sh
```
This script will remove build files and executable

## How to use
This tool can be used with in command line.
To use it, please launch install.sh script, then:
```bash
./compreC [-h] -f <file.zip> [-p <password>]
```
A ncurses session will be launched.
Dependending on if the file is protected or not, you will have a different prompt.
If the file is protected, you will have the choice to enter the password of the file or bruteforce it.

In not protected mode, you can choose among 4 options:
1. Explore: feature in WIP. Currently, it does nothing.
2. Exit: Quit the application. Please, use this option instead of Ctrl-C to keep your memory.

In protected mode, you can choose among 4 options:
1. BruteForce: Try to find the password of the file.
2. Password: Enter the password of the file.
3. Explore: feature in WIP. Currently, it does nothing. A protected zip file doesn't prevent to explore it.
4. Exit: Quit the application. Please, use this option instead of Ctrl-C to keep your memory.

You can navigate through on-screen options using arrow keys and select one by pressing Enter key.

## Architecture

in src directory, you can find:
- CMakeLists.txt: the file used by install.sh to compile the project. Do not remove it please.

- interface_internal.h: declare the libraries used in interface.c and internal functions implemented in internal.c.
- interface.h: declare functions to be used by the other files.
- interface.c: implements ncurses session management.

- zipUtils_internal.h: declare the libraries used in zipUtils.c and internal functions implemented in zipUtils.c.
- zipUtils.h: declare functions to be used by the other files.
- zipUtils.c: implements zip tools to manage zip files.

- main_internal.h: declare the libraries used in main.c and internal functions implemented in main.c.
- main.h: declare libraries to be used by the all files.
- main.c: implements options management and main function.

## Functioning
### Structure
The project is divided in 3 parts:
- interface: manage the ncurses session
- zipUtils: manage zip files
- main: manage options and main function

each part is divided in 3 files:
- .c file: implements the functions
- _internal.h file: declare the libraries and internal functions to be used in the .c file
- .h file: declare the functions to be used by other files

The details of the functions are mentionned as a "JavaDoc" style documentation in the files.

### Unlock a zip file
#### BruteForce a zip file
If you don't provide password, you will have the choice to bruteforce the zip file. The program will try all the combinations of passwords. It will take a long time, but it will find the password.

#### Provide a password
To unlock a zip file, you can provide it at the launch of the program with the -p option. Else, you can use the "Password" option in the ncurses session.


### Disclamer
There are not a complete error management, so you could encounter some bugs but in the traditional way to use our tool, it could be ok.