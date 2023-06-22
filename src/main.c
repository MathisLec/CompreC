#include "main.h"
#include "main_internal.h"

char* filepath = "";
char* password = "";
int isProtected = 0;

void printUsage(){
	printf("Usage: ./compreC [-h] [-f file]\n");
	printf("Options:\n");
	printf("\t-h\t\tShow this help message\n");
	printf("\t-f file\t\tSpecify the file to open\n");
}

//Function that parse input options with getopt

void parseOpt(int argc, char** argv){
	int opt;
	while((opt = getopt(argc, argv,"hf:p:")) != -1){
		switch(opt){
			case 'h':
				printUsage();
				exit(EXIT_SUCCESS);
				break;
			case 'f':
				filepath = optarg;
				break;
			case 'p':
				password = optarg;
				break;
			default:
				printUsage();
				exit(EXIT_FAILURE);
				break;
		}
	}
	if(filepath != ""){
		checkZip();
	}
}

void checkZip(){
	if(isZipProtected(filepath)){
		isProtected = 1;
	}
	else if(password != "")
		printf("Password provided but the file is not protected\n");
}


/**
 * Main function
*/
int main(int argc, char *argv[])
{
	//Set UTF-8 locale
	setlocale(LC_ALL, "");
	//Parse options
	parseOpt(argc, argv);
	//Launch the interface
	launchInterface(filepath,isProtected,(strlen(password) ? 1 : 0) );
	return 0;
}