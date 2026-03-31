/* HEADER */
#include <sys/stat.h>

/* SYNTAX */
int stat(const char *pathname, struct stat *statbuf);

/* EXAMPLE */
#include <sys/stat.h>

int main() {
    struct stat info;
    stat("file.txt", &info);
}
