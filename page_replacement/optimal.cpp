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
    for (int i = 0; i < frames; i++) memory[i] = -1;

    int pageFaults = 0;

    for (int i = 0; i < n; i++) {
        int page = pages[i];

        // Check if page is in memory
        bool found = false;
        for (int j = 0; j < frames; j++) {
            if (memory[j] == page) { found = true; break; }
        }

        if (!found) {
            pageFaults++;

            // Check if there is an empty frame
            int emptySlot = -1;
            for (int j = 0; j < frames; j++) {
                if (memory[j] == -1) { emptySlot = j; break; }
            }

            if (emptySlot != -1) {
                memory[emptySlot] = page;
                cout << "Page " << page << " loaded (empty frame) -> Page Fault\n";
            } else {
                // Find which page in memory is used farthest in future
                int evictSlot = 0;
                int farthest = -1;

                for (int j = 0; j < frames; j++) {
                    int nextUse = n;  // assume never used again (infinity)
                    for (int k = i + 1; k < n; k++) {
                        if (pages[k] == memory[j]) { nextUse = k; break; }
                    }
                    if (nextUse > farthest) {
                        farthest = nextUse;
                        evictSlot = j;
                    }
                }

                cout << "Page " << page << " loaded, evicted " << memory[evictSlot] << " -> Page Fault\n";
                memory[evictSlot] = page;
            }
        } else {
            cout << "Page " << page << " -> HIT\n";
        }
    }

    cout << "\nTotal Page Faults (Optimal): " << pageFaults << endl;
    return 0;
}
