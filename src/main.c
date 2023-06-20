#include "main.h"
#include "interface.h"
#include "zipUtils.h"
#include <getopt.h>

char* filepath;

void printUsage(){
	printf("Usage: ./compreC [-h] [-f file]\n");
	printf("Options:\n");
	printf("\t-h\t\tShow this help message\n");
	printf("\t-f file\t\tSpecify the file to open\n");
}

//Function that parse input options with getopt
void parseOpt(int argc, char* argv){
	int opt;
	while((opt = getopt(argc, argv,"hf:")) != -1){
		switch(opt){
			case 'h':
				printUsage();
				exit(EXIT_SUCCESS);
				break;
			case 'f':
				filepath = optarg;
				checkZip();
				break;
			default:
				printUsage();
				exit(EXIT_FAILURE);
				break;
		}
	}

}

void checkZip(){
	if(isZipProtected(filepath)){
		printf("The zip is protected\n");
	}else{
		printf("The zip is not protected\n");
	}
}

/**
 * Main function
*/
int main(int argc, char *argv[])
{
	parseOpt(argc, argv);
	//launchInterface();
	return 0;
}