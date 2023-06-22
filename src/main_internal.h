#include "interface.h"
#include "zipUtils.h"
#include <getopt.h>
#include <locale.h>

//Insert all signatures functions implemented in main.c
void printUsage();
void checkZip();
void parseOpt(int argc, char** argv);
int main(int argc, char *argv[]);