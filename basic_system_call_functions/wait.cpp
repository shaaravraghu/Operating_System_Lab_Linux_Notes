/* HEADER */
#include <sys/wait.h>

/* SYNTAX */
pid_t wait(int *status);

/* EXAMPLE */
#include <sys/wait.h>

int main() {
    wait(NULL);
}
