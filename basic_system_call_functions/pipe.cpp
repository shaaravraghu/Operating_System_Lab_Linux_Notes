/* HEADER */
#include <unistd.h>

/* SYNTAX */
int pipe(int fd[2]);

/* EXAMPLE */
#include <unistd.h>

int main() {
    int fd[2];
    pipe(fd);
}
