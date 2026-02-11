#include <iostream>
using namespace std;

#define SIZE 5 // buffer size

int buffer[SIZE];
int in = 0;
int out = 0;

// Semaphores
int empty = SIZE;
int full = 0;
int mutex = 1;

// wait function
void wait(int &s) {
    s--;
}

// signal function
void signal(int &s) {
    s++;
}

// Producer
void producer(int item) {

    wait(empty);
    wait(mutex);

    // add item to buffer
    buffer[in] = item;
    cout << "Produced: " << item << endl;
    in = (in + 1) % SIZE;

    signal(mutex);
    signal(full);
}

// Consumer
void consumer() {

    wait(full);
    wait(mutex);

    // remove item from buffer
    int item = buffer[out];
    cout << "Consumed: " << item << endl;
    out = (out + 1) % SIZE;

    signal(mutex);
    signal(empty);
}

int main() {

    // simple simulation
    producer(1);
    producer(2);
    producer(3);

    consumer();
    consumer();

    producer(4);
    consumer();

    return 0;
}
