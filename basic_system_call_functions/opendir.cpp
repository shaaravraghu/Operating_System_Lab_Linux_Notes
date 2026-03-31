/* HEADER */
#include <dirent.h>

/* SYNTAX */
DIR *opendir(const char *dirname);

/* EXAMPLE */
#include <dirent.h>

int main() {
    DIR *d = opendir(".");
}
