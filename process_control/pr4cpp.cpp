#include <iostream>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

using namespace std;

int main()
{
    pid_t pid, pid1;

    // fork a child process
    pid = fork();

    if (pid < 0) {   // error occurred
        cerr << "Fork Failed" << endl;
        return 1;
    }
    else if (pid == 0) {   // child process
        pid1 = getpid();
        cout << "child: pid = " << pid << endl;    // LINE A
        cout << "child: pid1 = " << pid1 << endl;  // LINE B
    }
    else {   // parent process
        pid1 = getpid();
        cout << "parent: pid = " << pid << endl;   // LINE C
        cout << "parent: pid1 = " << pid1 << endl; // LINE D
        wait(nullptr);
    }

    return 0;
}

