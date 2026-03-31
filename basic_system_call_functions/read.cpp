/* HEADER */
#include <unistd.h>

/* SYNTAX */
ssize_t read(int fd, void *buffer, size_t count);

/* EXAMPLE */
#include <unistd.h>
#include <fcntl.h>

int main() {
    char buf[100];
    int fd = open("file.txt", O_RDONLY);
    read(fd, buf, 100);
    close(fd);
}
