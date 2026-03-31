/* HEADER */
#include <dirent.h>

/* SYNTAX */
int closedir(DIR *dirp);

/* EXAMPLE */
#include <dirent.h>

int main() {
    DIR *d = opendir(".");
    closedir(d);
}
