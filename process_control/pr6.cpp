#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>

int main() {
    pid_t pid = fork();

    if (pid < 0) {
        // Error occurred
        perror("Fork failed");
        return 1;
    } 
    else if (pid == 0) {
        // CHILD PROCESS
        std::cout << "Child process (PID: " << getpid() << ") is exiting to become a zombie..." << std::endl;
        exit(0); 
    } 
    else {
        // PARENT PROCESS
        std::cout << "Parent process (PID: " << getpid() << ") is sleeping for 20 seconds." << std::endl;
        std::cout << "Child (PID: " << pid << ") should now be in a zombie state." << std::endl;
        
        // Parent sleeps, keeping the process alive so the child stays a zombie
        sleep(20); 
        
        std::cout << "Parent is waking up and exiting. Zombie should be cleared by init/launchd." << std::endl;
    }

    return 0;
}
