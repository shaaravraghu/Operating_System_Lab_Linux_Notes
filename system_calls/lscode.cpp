#include <iostream>
#include <dirent.h>

using namespace std;

int main()
{
    DIR *dir;
    struct dirent *entry;

    // Open current working directory
    dir = opendir(".");

    if (dir == NULL) {
        perror("opendir");
        return 1;
    }

    // Read entries
    while ((entry = readdir(dir)) != NULL)
    {
        cout << entry->d_name << endl;
    }

    // Close directory
    closedir(dir);
    return 0;
}

