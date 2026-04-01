#include <iostream>
using namespace std;

int main() {
    int frames, n;
    cout << "Enter number of frames: ";
    cin >> frames;
    cout << "Enter number of page references: ";
    cin >> n;

    int pages[n];
    cout << "Enter page reference string: ";
    for (int i = 0; i < n; i++) cin >> pages[i];

    int memory[frames];
    for (int i = 0; i < frames; i++) memory[i] = -1;  // -1 means empty

    int pageFaults = 0;
    int pointer = 0;  // points to the oldest page (next to evict)

    for (int i = 0; i < n; i++) {
        int page = pages[i];

        // Check if page is already in memory
        bool found = false;
        for (int j = 0; j < frames; j++) {
            if (memory[j] == page) { found = true; break; }
        }

        if (!found) {
            // Page fault — replace at pointer position
            memory[pointer] = page;
            pointer = (pointer + 1) % frames;  // move pointer circularly
            pageFaults++;
            cout << "Page " << page << " loaded  -> Page Fault\n";
        } else {
            cout << "Page " << page << " -> HIT\n";
        }
    }

    cout << "\nTotal Page Faults (FIFO): " << pageFaults << endl;
    return 0;
}
