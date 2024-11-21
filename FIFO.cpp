#include <iostream>
#include <vector>
#include <queue>
#include <unordered_set>

using namespace std;

// Function to calculate page faults using FIFO
int calculatePageFaultsFIFO(vector<int> referenceString, int frameSize) {
    unordered_set<int> pages; // To store the pages in memory
    queue<int> fifoQueue;     // To maintain the order of pages
    int pageFaults = 0;

    for (int page : referenceString) {
        // If the page is not in memory
        if (pages.find(page) == pages.end()) {
            // If there is space in memory
            if (pages.size() < frameSize) {
                pages.insert(page);
                fifoQueue.push(page);
            } else {
                // Replace the oldest page using FIFO
                int oldestPage = fifoQueue.front();
                fifoQueue.pop();
                pages.erase(oldestPage);
                pages.insert(page);
                fifoQueue.push(page);
            }
            pageFaults++; // Increment page fault count
        }
    }

    return pageFaults;
}

// Main function
int main() {
    int n, frameSize;

    cout << "Enter the number of pages in the reference string: ";
    cin >> n;

    vector<int> referenceString(n);
    cout << "Enter the reference string (space-separated integers): ";
    for (int i = 0; i < n; i++) {
        cin >> referenceString[i];
    }

    cout << "Enter the frame size: ";
    cin >> frameSize;

    int pageFaults = calculatePageFaultsFIFO(referenceString, frameSize);

    cout << "\nNumber of page faults using FIFO: " << pageFaults << endl;

    return 0;
}
//total 15
//7 0 1 2 0 3 0 4 2 3 0 3 1 2 0
