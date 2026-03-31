/* HEADER */
#include <unistd.h>

/* SYNTAX */
int dup(int oldfd);

/* EXAMPLE */
#include <unistd.h>
#include <fcntl.h>

int main() {
    int fd = open("file.txt", O_RDONLY);
    int newfd = dup(fd);
}
