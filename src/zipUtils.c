#include "zipUtils.h"
#include "main.h"

/**
 * Functions implementation
 * 
*/
int isZipProtected(const char* filepath){
    int isProtected = 0;

    struct zip* zip = zip_open(filepath, ZIP_RDONLY, NULL);
    if (zip != NULL) {
        int numEntries = zip_get_num_entries(zip, 0);
        for (int i = 0; i < numEntries; i++) {
            struct zip_stat fileStat;
            zip_stat_init(&fileStat);
            zip_stat_index(zip, i, 0, &fileStat);
            //Check if zip is protected 
            printf("%ld\n", fileStat.flags);
            if(fileStat.flags & ZIP_STAT_ENCRYPTION_METHOD){
                printf("HELLOOOO");
                isProtected = 1;
                break;
            }
        }
        zip_close(zip);
    }
    else{
        printf("Error while opening the zip file\n");
    }

    return isProtected;
}