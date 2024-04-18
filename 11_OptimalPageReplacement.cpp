#include <iostream>
#include <unordered_map>

using namespace std;

// Function to search for a key in frame items
int search(int key, int frame_items[], int frame_occupied) {
    // Iterate through the frame items
    for (int i = 0; i < frame_occupied; i++) {
        // If key found in frame items, return true (1)
        if (frame_items[i] == key)
            return 1;
    }
    // If key not found, return false (0)
    return 0;
}

// Function to predict the page to replace based on future accesses
int predict(int ref_str[], int frame_items[], int refStrLen,
            int index, int frame_occupied) {
    int result = -1, farthest = index;
    // Iterate through the frame items
    for (int i = 0; i < frame_occupied; i++) {
        int j;
        // Iterate through future accesses
        for (j = index; j < refStrLen; j++) {
            // If the current frame item is accessed in the future
            if (frame_items[i] == ref_str[j]) {
                // Update farthest access and store the index of frame item
                if (j > farthest) {
                    farthest = j;
                    result = i;
                }
                break;
            }
        }
        // If the frame item is not accessed in the future, return its index
        if (j == refStrLen)
            return i;
    }
    // Return the index of the frame item to replace
    return (result == -1) ? 0 : result;
}

// Function to perform Optimal Page Replacement
void optimalPage(int ref_str[], int refStrLen, int frame_items[], int max_frames) {
    int frame_occupied = 0; // Number of frames occupied
    int hits = 0; // Number of page hits

    // Iterate through the reference string
    for (int i = 0; i < refStrLen; i++) {
        // If page is already in memory (page hit)
        if (search(ref_str[i], frame_items, frame_occupied)) {
            hits++; // Increment page hit count
            continue;
        }
        // If there's still space in memory
        if (frame_occupied < max_frames) {
            frame_items[frame_occupied++] = ref_str[i]; // Add page to memory
        } else {
            // If memory is full, predict the page to replace
            int pos = predict(ref_str, frame_items, refStrLen, i + 1, frame_occupied);
            frame_items[pos] = ref_str[i]; // Replace page in memory
        }
    }

    // Output the number of hits and misses
    cout << "Hits: " << hits << endl;
    cout << "Misses: " << refStrLen - hits << endl;
}

int main() {
    // Example reference string
    int ref_str[] = {1, 2, 3, 4, 1, 5, 1, 6, 1, 7, 8, 7, 8, 9, 7, 8, 9, 5};
    int refStrLen = sizeof(ref_str) / sizeof(ref_str[0]); // Length of reference string
    int max_frames = 3; // Maximum number of frames in memory
    int frame_items[max_frames] = {0}; // Array to store frame items

    // Perform Optimal Page Replacement
    optimalPage(ref_str, refStrLen, frame_items, max_frames);

    return 0;
}
