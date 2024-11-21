#include <iostream>
#include <vector>
#include <unordered_map>
#include<climits>
using namespace std;

// Function to calculate page faults using LRU
int calculatePageFaultsLRU(vector<int> referenceString, int frameSize) {
    unordered_map<int, int> pageMap; // To store page and its last used time
    int pageFaults = 0;
    int currentTime = 0;

    for (int page : referenceString) {
        // Check if the page is in memory
        if (pageMap.find(page) == pageMap.end()) {
            // Page not in memory, so page fault occurs
            if (pageMap.size() < frameSize) {
                // If there is space in memory, add the page
                pageMap[page] = currentTime;
            } else {
                // Find the least recently used page
                int lruPage = -1, minTime = INT_MAX;
                for (auto &entry : pageMap) {
                    if (entry.second < minTime) {
                        minTime = entry.second;
                        lruPage = entry.first;
                    }
                }
                // Remove the least recently used page
                pageMap.erase(lruPage);
                // Add the new page
                pageMap[page] = currentTime;
            }
            pageFaults++; // Increment page fault counter
        } else {
            // If page is already in memory, update its last used time
            pageMap[page] = currentTime;
        }
        currentTime++;
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

    int pageFaults = calculatePageFaultsLRU(referenceString, frameSize);

    cout << "\nNumber of page faults using LRU: " << pageFaults << endl;

    return 0;
}
//20
//7 0 1 2 0 3 0 4 2 3 0 3 2 1 2 0 1 7 0 1
