#include <iostream>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

using namespace std;

int value = 5;

int main()
{
    pid_t pid;
    pid = fork();

    if (pid == 0) {   // child process
        value += 15;
        return 0;
    }
    else if (pid > 0) {   // parent process
        wait(nullptr);
        cout << "PARENT: value = " << value << endl;  // LINE A
        return 0;
    }

    return 0;
}

