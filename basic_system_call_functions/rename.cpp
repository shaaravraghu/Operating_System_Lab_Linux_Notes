/* HEADER */
#include <stdio.h>

/* SYNTAX */
int rename(const char *oldname, const char *newname);

/* EXAMPLE */
#include <stdio.h>

int main() {
    rename("old.txt", "new.txt");
}
