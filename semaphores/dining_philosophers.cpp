#include <iostream>
using namespace std;

#define N 5   // number of philosophers

/* ----------- CUSTOM SEMAPHORE ----------- */

class Semaphore {
public:
    int value;

    Semaphore(int v) {
        value = v;
    }

    bool wait() {
        if (value > 0) {
            value--;
            return true;
        }
        return false;  // cannot acquire
    }

    void signal() {
        value++;
    }
};

/* ----------- GLOBAL FORKS ----------- */

// each fork is a binary semaphore
Semaphore forkSem[N] = {1, 1, 1, 1, 1};

/* ----------- PHILOSOPHER ACTION ----------- */

void dine(int id) {
    int left = id;
    int right = (id + 1) % N;

    cout << "\nPhilosopher " << id << " is HUNGRY\n";

    // try to pick left fork
    if (!forkSem[left].wait()) {
        cout << "Philosopher " << id << " waiting for left fork\n";
        return;
    }

    cout << "Philosopher " << id << " picked LEFT fork " << left << endl;

    // try to pick right fork

    if (!forkSem[right].wait()) {
        cout << "Philosopher " << id << " waiting for right fork\n";
        forkSem[left].signal(); // release left fork
        return;
    }

    cout << "Philosopher " << id << " picked RIGHT fork " << right << endl;

    // critical section
    cout << "Philosopher " << id << " is EATING\n";

    // release forks
    forkSem[left].signal();
    forkSem[right].signal();

    cout << "Philosopher " << id << " finished and released forks\n";
}

/* ----------- MAIN SIMULATION ----------- */

int main() {

    /*
      Instruction array → order of philosophers trying to eat
      (0–4 represent philosopher IDs)
    */

    int instruction[] = {0, 1, 2, 3, 4, 1, 3, 0, 2};
    int size = sizeof(instruction) / sizeof(instruction[0]);

    cout << "===== Dining Philosophers Simulation =====\n";

    for (int i = 0; i < size; i++) {
        dine(instruction[i]);
    }

    return 0;
}
