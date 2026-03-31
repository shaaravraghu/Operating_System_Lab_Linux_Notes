/* HEADER */
#include <dirent.h>

/* SYNTAX */
struct dirent *readdir(DIR *dirp);

/* EXAMPLE */
#include <dirent.h>

int main() {
    DIR *d = opendir(".");
    struct dirent *entry = readdir(d);
}
