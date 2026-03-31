/* HEADER */
#include <unistd.h>

/* SYNTAX */
ssize_t write(int fd, const void *buffer, size_t count);

/* EXAMPLE */
#include <unistd.h>
#include <fcntl.h>

int main() {
    int fd = open("file.txt", O_WRONLY);
    write(fd, "Hello", 5);
    close(fd);
}
