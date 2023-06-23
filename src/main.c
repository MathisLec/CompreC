#include "main.h"
#include "main_internal.h"

char* filepath = "";
char* password = "";
int isProtected = 0;

void printUsage(){
	printf("Usage: ./compreC [-h] -f file [-p password]\n");
	printf("Options:\n");
	printf("\t-h\t\tShow this help message\n");
	printf("\t-f file\t\tSpecify the file to open\n");
	printf("\t-p password\tSpecify the password to use\n");
}

/**
 * parseOpt(int argc, char** argv)
 * argc: number of arguments
 * argv: array of arguments
*/
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
		if(password != ""){
			if(isPasswordCorrect(filepath, password)){
				printf("Password provided and correct\n");
				exit(EXIT_SUCCESS);
			}
			else{
				printf("Password provided but incorrect\n");
				exit(EXIT_FAILURE);
			}
		}
	}
	else if(password != "")
		printf("Password provided but the file is not protected\n");
}


/**
 * Main function
*/
/**
 * int main(int argc, char *argv[])
 * argc: number of arguments
 * argv: array of arguments
 * return: 0 if success, 1 if failure
*/
int main(int argc, char *argv[])
{
	//Set UTF-8 locale
	setlocale(LC_ALL, "");
	//Parse options
	parseOpt(argc, argv);
	//Launch the interface
	launchInterface(filepath,isProtected,password);
	return 0;
}