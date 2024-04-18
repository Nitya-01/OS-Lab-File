// The First-In-First-Out (FIFO) Page Replacement algorithm replaces the oldest page in memory when a page fault occurs.
// It uses a queue to simulate the order of page accesses and a set to keep track of pages currently in memory.
// When a new page needs to be loaded into memory, the algorithm removes the oldest page from the queue and adds the new page to the end of the queue.

#include <iostream>
#include <queue>
#include <unordered_set>

using namespace std;

// Function to perform FIFO Page Replacement
int fifoPageFaults(int pages[], int n, int capacity) {
    queue<int> fifo; // Queue to simulate page frames
    unordered_set<int> memory; // Set to keep track of pages in memory
    int faults = 0; // Counter for page faults

    // Iterate through each page in the reference string
    for (int i = 0; i < n; ++i) {
        // If the page is not in memory, a page fault occurs
        if (memory.find(pages[i]) == memory.end()) {
            // If memory is full, remove the oldest page (front of the queue)
            if (fifo.size() == capacity) {
                int oldest = fifo.front(); // Get the oldest page
                fifo.pop(); // Remove the oldest page from the queue
                memory.erase(oldest); // Remove the oldest page from memory
            }
            // Add the new page into memory (enqueue)
            fifo.push(pages[i]);
            memory.insert(pages[i]);
            faults++; // Increment page fault counter
        }
    }

    return faults; // Return the total number of page faults
}

int main() {
    // Example reference string
    int pages[] = {1, 2, 3, 4, 1, 2, 5, 1, 2, 3, 4, 5};
    int n = sizeof(pages) / sizeof(pages[0]); // Number of elements in reference string
    int capacity = 3; // Number of frames in memory

    // Perform FIFO Page Replacement and display the result
    cout << "Total page faults using FIFO: " << fifoPageFaults(pages, n, capacity) << endl;

    return 0;
}
