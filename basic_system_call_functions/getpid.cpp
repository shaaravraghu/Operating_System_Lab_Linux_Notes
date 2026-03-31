/* HEADER */
#include <unistd.h>

/* SYNTAX */
pid_t getpid(void);

/* EXAMPLE */
#include <unistd.h>

int main() {
    pid_t id = getpid();
}
