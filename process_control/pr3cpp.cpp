#include <iostream>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

using namespace std;

int main()
{
    pid_t pid;

    pid = fork();

    if (pid < 0) {
        cerr << "Fork Failed" << endl;
        return 1;
    }
    else if (pid == 0) {   // Child process
        execlp("/bin/ls", "ls", nullptr);
        cout << "LINE J" << endl;   // Executes ONLY if execlp fails
    }
    else {   // Parent process
        wait(nullptr);
        cout << "Child Complete" << endl;
    }

    return 0;
}

