#include <iostream>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

using namespace std;

#define SIZE 5

int nums[SIZE] = {0, 1, 2, 3, 4};

int main()
{
    int i;
    pid_t pid;

    pid = fork();

    if (pid == 0) {   // Child process
        for (i = 0; i < SIZE; i++) {
            nums[i] *= -i;
            cout << "CHILD: " << nums[i] << " ";   // LINE X
        }
        cout << endl;
    }
    else if (pid > 0) {   // Parent process
        wait(nullptr);
        for (i = 0; i < SIZE; i++) {
            cout << "PARENT: " << nums[i] << " ";  // LINE Y
        }
        cout << endl;
    }

    return 0;
}

