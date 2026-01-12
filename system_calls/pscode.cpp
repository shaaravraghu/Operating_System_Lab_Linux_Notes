#include <iostream>
#include <sys/sysctl.h>
#include <vector>

using namespace std;

int main()
{
    int mib[4];
    size_t bufSize;
    struct kinfo_proc *procList = NULL;

    // sysctl MIB array: get all processes
    mib[0] = CTL_KERN;
    mib[1] = KERN_PROC;
    mib[2] = KERN_PROC_ALL;
    mib[3] = 0;

    // First call: get buffer size needed
    if (sysctl(mib, 4, NULL, &bufSize, NULL, 0) == -1) {
        perror("sysctl");
        return 1;
    }

    // Allocate buffer
    procList = (kinfo_proc*)malloc(bufSize);

    if (procList == NULL) {
        cerr << "Memory allocation failed\n";
        return 1;
    }

    // Second call: get actual process list into buffer
    if (sysctl(mib, 4, procList, &bufSize, NULL, 0) == -1) {
        perror("sysctl");
        free(procList);
        return 1;
    }

    // Number of processes
    int count = (int)(bufSize / sizeof(struct kinfo_proc));

    cout << "PID" << endl;

    for (int i = 0; i < count; i++) {
        cout << procList[i].kp_proc.p_pid << endl;
    }

    free(procList);
    return 0;
}
