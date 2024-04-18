// The Least Recently Used (LRU) Page Replacement algorithm replaces the page that has not been used for the longest period of time.
// It uses a doubly linked list to maintain the order of page accesses and a map to store the positions of pages in the list.
// When a page needs to be replaced, the algorithm selects the page at the tail of the linked list, which represents the least recently used page.

#include <iostream>
using namespace std;

int main() {
    // Variables to store input values and count page faults
    int n_pages, n_faults, pages[20], i, count = 0;

    // Input: number of pages
    cout << "\nEnter the number of pages: ";
    cin >> n_pages;

    // Input: reference string
    cout << "\nEnter the reference string: ";
    for (i = 0; i < n_pages; i++) {
        cout << "\t";
        cin >> pages[i];
    }

    // Input: number of frames
    cout << "\nEnter the number of frames: ";
    cin >> n_faults;

    // Arrays to represent frames and their counts
    int frames[n_faults], f_count[n_faults];
    for (i = 0; i < n_faults; i++) {
        frames[i] = -1; // Initialize frames with -1
        f_count[i] = 0; // Initialize frame count to 0
    }

    // Loop through each page in the reference string
    i = 0;
    while (i < n_pages) {
        int j = 0, flag = 0;
        
        // Check if page is already in frame
        while (j < n_faults) {
            if (pages[i] == frames[j]) {
                flag = 1; // Set flag if page is found
                f_count[j] = i + 1; // Update page access count
            }
            j++;
        }

        j = 0;
        cout << "\n***\n";
        cout << pages[i] << "-->";

        // If page not found in frame (page fault)
        if (flag == 0) {
            int min = 0, k = 0;

            // Find the least recently used frame
            while (k < n_faults - 1) {
                if (f_count[min] > f_count[k + 1])
                    min = k + 1;
                k++;
            }

            // Replace the least recently used frame with current page
            frames[min] = pages[i];
            f_count[min] = i + 1; // Update page access count
            count++; // Increment page fault count

            // Display frames after page replacement
            while (j < n_faults) {
                cout << "\t|" << frames[j] << "|";
                j++;
            }
        }
        i++; // Move to the next page in reference string
    }

    // Output total number of page faults
    cout << "\n***\n";
    cout << "\nPage Faults: " << count << "\n";

    return 0;
}
