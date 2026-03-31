/* HEADER */
#include <unistd.h>

/* SYNTAX */
pid_t fork(void);

/* EXAMPLE */
#include <unistd.h>

int main() {
    pid_t pid = fork();
}
