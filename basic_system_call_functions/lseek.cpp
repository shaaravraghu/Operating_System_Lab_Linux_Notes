/* HEADER */
#include <unistd.h>

/* SYNTAX */
off_t lseek(int fd, off_t offset, int whence);

/* EXAMPLE */
#include <unistd.h>
#include <fcntl.h>

int main() {
    int fd = open("file.txt", O_RDONLY);
    lseek(fd, 10, SEEK_SET);
    close(fd);
}
