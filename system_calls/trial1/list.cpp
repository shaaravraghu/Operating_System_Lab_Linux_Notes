#include <iostream>
#include <dirent.h>

using namespace std;

int main() {
    DIR *dir;
    struct dirent *entry;

    // Open current directory
    dir = opendir(".");

    if (dir == nullptr) {
        perror("opendir");
        return 1;
    }

    // Read directory entries
    while ((entry = readdir(dir)) != nullptr) {
        cout << entry->d_name << endl;
    }

    // Close directory
    closedir(dir);

    return 0;
}

