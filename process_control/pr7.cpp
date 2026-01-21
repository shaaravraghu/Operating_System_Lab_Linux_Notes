#include <iostream>
#include <vector>

#define MIN_PID 300
#define MAX_PID 5000
#define PID_COUNT (MAX_PID - MIN_PID + 1)

// Using a vector of bools for simplicity, which acts like a bitmap 
// and is memory-optimized in the C++ Standard Library.
std::vector<bool> pid_map;

/**
 * Creates and initializes the data structure.
 * Returns 1 if successful, -1 if unsuccessful.
 */
int allocate_map(void) {
    try {
        // Initialize the map with all PIDs set to 0 (available)
        pid_map.assign(PID_COUNT, false);
        return 1;
    } catch (...) {
        return -1;
    }
}

/**
 * Allocates and returns a pid.
 * Returns -1 if unable to allocate (all pids in use).
 */
int allocate_pid(void) {
    if (pid_map.empty()) return -1;

    for (int i = 0; i < PID_COUNT; i++) {
        if (pid_map[i] == false) { // Found an available PID
            pid_map[i] = true;     // Mark as in use
            return i + MIN_PID;    // Return the actual PID value
        }
    }
    return -1; // No PIDs available
}

/**
 * Releases a pid so it can be reused.
 */
void release_pid(int pid) {
    if (pid < MIN_PID || pid > MAX_PID) {
        std::cout << "Invalid PID release attempt: " << pid << std::endl;
        return;
    }
    
    // Map the actual PID back to the index (0 to 4700)
    int index = pid - MIN_PID;
    pid_map[index] = false;
}

int main() {
    // 1. Initialize the map
    if (allocate_map() == 1) {
        std::cout << "PID map initialized successfully." << std::endl;
    }

    // 2. Test allocation
    int my_pid = allocate_pid();
    std::cout << "Allocated PID: " << my_pid << std::endl;

    int another_pid = allocate_pid();
    std::cout << "Allocated PID: " << another_pid << std::endl;

    // 3. Test release
    std::cout << "Releasing PID: " << my_pid << std::endl;
    release_pid(my_pid);

    // 4. Verify the released PID is reused
    int reused_pid = allocate_pid();
    std::cout << "Allocated PID (should be " << my_pid << "): " << reused_pid << std::endl;

    return 0;
}
