#include "zipUtils_internal.h"

/**
 * Internal functions
*/
/**
 * filePathToZip(const char* filepath)
 * filepath: the path of the zip file
 * return: a pointer to the zip structure
*/
struct zip* filePathToZip(const char* filepath){
    struct zip* zip = zip_open(filepath, ZIP_RDONLY, NULL);
    if (zip == NULL) {
        printf("Error while opening the zip file\n");
        exit(EXIT_FAILURE);
    }
    return zip;
}


/**
 * Functions implementation
 * 
*/
/**
 * isZipProtected(const char* filepath)
 * filepath: the path of the zip file
 * return: 1 if the zip is protected, 0 otherwise
*/
int isZipProtected(const char* filepath){
    int isProtected = 0;

    struct zip* zip = filePathToZip(filepath);
    //Get the number of entries in the zip
    int numEntries = zip_get_num_entries(zip, 0);
    for (int i = 0; i < numEntries; i++) {
        struct zip_stat fileStat;
        zip_stat_init(&fileStat);
        zip_stat_index(zip, i, 0, &fileStat);
        if(fileStat.encryption_method > 0){
            isProtected = 1;
            break;
        }
    }
    zip_close(zip);

    return isProtected;
}

/**
 * isPasswordCorrect(const char* filepath, const char* password)
 * filepath: the path of the zip file
 * password: the password to test
 * return: 1 if the password is correct, 0 otherwise
*/
int isPasswordCorrect(const char* filepath, const char* password){
    int isCorrect = 1;

    struct zip* zip = filePathToZip(filepath);
    //Get the number of entries in the zip
    int numEntries = zip_get_num_entries(zip, 0);
    for (int i = 0; i < numEntries; i++) {
        struct zip_stat fileStat;
        zip_stat_init(&fileStat);
        zip_stat_index(zip, i, 0, &fileStat);
        if(fileStat.encryption_method > 0){
            if(zip_fopen_index_encrypted(zip, i, 0, password) == NULL){
                isCorrect = 0;
                break;
            }
        }
    }
    zip_close(zip);

    return isCorrect;
}

/**
 * openZip(const char* filepath, const char* password)
 * filepath: the path of the zip file
 * password: the password of the zip file
 * return: a pointer to the zip structure
*/
struct zip* openZip(const char* filepath, const char* password){
    struct zip* zip = zip_open(filepath, ZIP_RDONLY, NULL);
    if (zip == NULL) {
        printf("Error while opening the zip file\n");
        exit(EXIT_FAILURE);
    }
    else{
        if(isPasswordCorrect(filepath, password)){
            printf("Error while opening the zip file\n");
            exit(EXIT_FAILURE);
        }
    }
    return zip;
}