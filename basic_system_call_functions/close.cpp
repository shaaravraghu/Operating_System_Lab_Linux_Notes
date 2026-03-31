/* HEADER */
#include <unistd.h>

/* SYNTAX */
int close(int fd);

/* EXAMPLE */
#include <unistd.h>
#include <fcntl.h>

int main() {
    int fd = open("file.txt", O_RDONLY);
    close(fd);
}
