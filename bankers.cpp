#include <iostream>
#include <vector>

using namespace std;

// Function to check if the system is in a safe state
bool isSafeState(vector<vector<int>>& allocation, vector<vector<int>>& max, vector<int>& available, int resources) {
    int processes = allocation.size();

    // Calculate the Need matrix
    vector<vector<int>> need(processes, vector<int>(resources));
    for (int i = 0; i < processes; i++) {
        for (int j = 0; j < resources; j++) {
            need[i][j] = max[i][j] - allocation[i][j];
        }
    }

    // Initialize work and finish arrays
    vector<int> work = available;
    vector<bool> finish(processes, false);
    vector<int> safeSequence;

    // Keep checking until all processes are either finished or deadlocked
    int finishedProcesses = 0;
    while (finishedProcesses < processes) {
        bool found = false;

        for (int i = 0; i < processes; i++) {
            if (!finish[i]) {
                // Check if process can execute
                bool canExecute = true;
                for (int j = 0; j < resources; j++) {
                    if (need[i][j] > work[j]) {
                        canExecute = false;
                        break;
                    }
                }

                // If process can execute, mark it as finished and update work
                if (canExecute) {
                    for (int j = 0; j < resources; j++) {
                        work[j] += allocation[i][j];
                    }
                    finish[i] = true;
                    safeSequence.push_back(i);
                    finishedProcesses++;
                    found = true;
                }
            }
        }

        // If no process can execute in this round, the system is not in a safe state
        if (!found) {
            cout << "System is not in a safe state.\n";
            return false;
        }
    }

    // Print the safe sequence
    cout << "System is in a safe state.\nSafe Sequence: ";
    for (int i : safeSequence) {
        cout << "P" << i + 1 << " ";
    }
    cout << endl;
    return true;
}

int main() {
    int processes, resources;

    // Input number of processes and resources
    cout << "Enter the number of processes: ";
    cin >> processes;
    cout << "Enter the number of resources: ";
    cin >> resources;

    // Input total available resources
    vector<int> totalAvailable(resources);
    cout << "Enter the total number of each type of resource: ";
    for (int i = 0; i < resources; i++) {
        cin >> totalAvailable[i];
    }

    // Input Allocation matrix
    vector<vector<int>> allocation(processes, vector<int>(resources));
    cout << "Enter the Allocation matrix (resources allocated to each process):\n";
    for (int i = 0; i < processes; i++) {
        for (int j = 0; j < resources; j++) {
            cin >> allocation[i][j];
        }
    }

    // Input Maximum Need matrix
    vector<vector<int>> max(processes, vector<int>(resources));
    cout << "Enter the Maximum Need matrix (maximum resources each process may require):\n";
    for (int i = 0; i < processes; i++) {
        for (int j = 0; j < resources; j++) {
            cin >> max[i][j];
        }
    }

    // Calculate the Available resources vector
    vector<int> available(resources);
    for (int i = 0; i < resources; i++) {
        int allocated = 0;
        for (int j = 0; j < processes; j++) {
            allocated += allocation[j][i];
        }
        available[i] = totalAvailable[i] - allocated;
    }

    // Check if the system is in a safe state
    isSafeState(allocation, max, available, resources);

    return 0;
}
//5 //3 //total 10 5 7
//allocation
// 0 1 0
//2 0 0
//3 0 2
//2 1 1 
//0 0 2
//max
//7 5 3
//3 2 2
//9 0 2
//4 2 2
//5 3 3
