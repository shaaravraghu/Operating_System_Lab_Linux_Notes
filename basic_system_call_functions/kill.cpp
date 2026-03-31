/* HEADER */
#include <signal.h>

/* SYNTAX */
int kill(pid_t pid, int sig);

/* EXAMPLE */
#include <signal.h>

int main() {
    kill(1234, SIGKILL);
}
