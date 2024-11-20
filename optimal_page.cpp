#include <iostream>
#include <vector>
#include <unordered_set>
#include <unordered_map>

using namespace std;

// Function to calculate page faults using Optimal Page Replacement
int calculatePageFaultsOptimal(vector<int> referenceString, int frameSize) {
    unordered_set<int> pages; // To store the pages in memory
    int pageFaults = 0;

    for (int i = 0; i < referenceString.size(); i++) {
        int page = referenceString[i];

        // If the page is not already in memory
        if (pages.find(page) == pages.end()) {
            // Page fault occurs
            if (pages.size() < frameSize) {
                // If there is space in memory, add the page
                pages.insert(page);
            } else {
                // If no space, replace a page using the Optimal strategy
                int farthest = i, pageToReplace = -1;

                for (int p : pages) {
                    bool found = false;
                    for (int j = i + 1; j < referenceString.size(); j++) {
                        if (referenceString[j] == p) {
                            if (j > farthest) {
                                farthest = j;
                                pageToReplace = p;
                            }
                            found = true;
                            break;
                        }
                    }
                    if (!found) { // If page is not used in the future
                        pageToReplace = p;
                        break;
                    }
                }

                // Remove the page to be replaced and add the new page
                pages.erase(pageToReplace);
                pages.insert(page);
            }
            pageFaults++;
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

    int pageFaults = calculatePageFaultsOptimal(referenceString, frameSize);

    cout << "\nNumber of page faults using Optimal Page Replacement: " << pageFaults << endl;

    return 0;
}

//20
//7 0 1 2 0 3 0 4 2 3 0 3 2 1 2 0 1 7 0 1
