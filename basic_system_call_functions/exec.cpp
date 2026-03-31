/* HEADER */
#include <unistd.h>

/* SYNTAX */
int execl(const char *path, const char *arg0, ..., NULL);

/* EXAMPLE */
#include <unistd.h>

int main() {
    execl("/bin/ls", "ls", NULL);
}
