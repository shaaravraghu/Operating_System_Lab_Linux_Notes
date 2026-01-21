#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
    // 1. Error checking for command line arguments
    if (argc != 2) {
        std::cerr << "Usage: ./collatz <positive_integer>" << std::endl;
        return 1;
    }

    int n = std::atoi(argv[1]);

    if (n <= 0) {
        std::cerr << "Please enter a positive integer greater than 0." << std::endl;
        return 1;
    }

    // 2. Forking the process
    pid_t pid = fork();

    if (pid < 0) {
        // Fork failed
        perror("Fork failed");
        return 1;
    } 
    else if (pid == 0) {
        // CHILD PROCESS: Performs the Collatz algorithm
        std::cout << "Child process started. Sequence: " << n;
        
        while (n != 1) {
            if (n % 2 == 0) {
                n = n / 2;
            } else {
                n = 3 * n + 1;
            }
            std::cout << ", " << n;
        }
        
        std::cout << std::endl << "Child process complete." << std::endl;
    } 
    else {
        // PARENT PROCESS: Waits for the child to finish
        std::cout << "Parent waiting for child..." << std::endl;
        wait(NULL);
        std::cout << "Parent process exiting." << std::endl;
    }

    return 0;
}
