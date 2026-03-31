/* HEADER */
#include <unistd.h>

/* SYNTAX */
int unlink(const char *pathname);

/* EXAMPLE */
#include <unistd.h>

int main() {
    unlink("file.txt");
}
