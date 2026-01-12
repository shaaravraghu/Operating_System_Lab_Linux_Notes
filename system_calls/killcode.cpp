#include <iostream>
#include <signal.h>
#include <cstdlib>
#include <cstring>

using namespace std;

int main(int argc, char *argv[])
{
    if (argc < 2) {
        cerr << "Usage: " << argv[0] << " <pid>\n";
        return 1;
    }

    int pid = atoi(argv[1]);

    // Send SIGKILL (force terminate). You can use SIGTERM for graceful terminate.
    if (kill(pid, SIGKILL) == 0) {
        cout << "Process terminated successfully." << endl;
    } else {
        perror("kill");
        return 1;
    }

    return 0;
}
