#include <zip.h>

int isZipProtected(const char* filepath);
int isPasswordCorrect(const char* filepath, const char* password);
struct zip* openZip(const char* filepath, const char* password);