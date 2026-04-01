#include <iostream>
using namespace std;

/* ---------- CUSTOM SEMAPHORE ---------- */

class Semaphore {
public:
    int value;

    Semaphore(int v) {
        value = v;
    }

    void wait() {
        if (value > 0)
            value--;
        else
            cout << "Process blocked (semaphore = 0)\n";
    }

    void signal() {
        value++;
    }
};

/* ---------- GLOBAL VARIABLES ---------- */

int readCount = 0;
Semaphore mutexSem(1);  // protects readCount
Semaphore wrt(1);       // controls shared resource

/* ---------- READER OPERATION ---------- */

void reader(int id) {
    cout << "\nReader " << id << " arrives\n";

    // entry section
    mutexSem.wait();
    readCount++;

    if (readCount == 1)
        wrt.wait();   // first reader blocks writer

    mutexSem.signal();

    // critical section
    cout << "Reader " << id << " is READING\n";

    // exit section
    mutexSem.wait();
    readCount--;

    if (readCount == 0)
        wrt.signal();  // last reader releases writer

    mutexSem.signal();

    cout << "Reader " << id << " leaves\n";
}

/* ---------- WRITER OPERATION ---------- */

void writer(int id) {
    cout << "\nWriter " << id << " arrives\n";

    wrt.wait();

    cout << "Writer " << id << " is WRITING\n";

    wrt.signal();

    cout << "Writer " << id << " leaves\n";
}

/* ---------- MAIN SIMULATION ---------- */

int main() {

    /*
      Instruction array:
      0 → Reader
      1 → Writer
    */

    int instruction[] = {0, 0, 1, 0, 1, 1, 0};
    int size = sizeof(instruction) / sizeof(instruction[0]);

    int readerID = 1, writerID = 1;

    cout << "===== Readers-Writers Simulation =====\n";

    for (int i = 0; i < size; i++) {

        if (instruction[i] == 0)
            reader(readerID++);

        else
            writer(writerID++);
    }

    return 0;
}
