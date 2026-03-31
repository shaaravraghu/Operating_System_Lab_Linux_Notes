/* HEADER */
#include <fcntl.h>

/* SYNTAX */
int open(const char *pathname, int flags);
int open(const char *pathname, int flags, mode_t mode);

/* EXAMPLE */
#include <fcntl.h>
#include <unistd.h>

int main() {
    int fd = open("file.txt", O_CREAT | O_RDWR, 0644);
    close(fd);
}
