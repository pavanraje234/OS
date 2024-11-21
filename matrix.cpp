#include <iostream>
#include <pthread.h>
#include <vector>

using namespace std;

// Matrices and dimensions
vector<vector<int>> matA, matB, matC;
int rowsA, colsA, rowsB, colsB;

// Structure to hold row and column for each thread
struct ThreadData {
    int row;
    int col;
};

// Thread function to compute a single element in the result matrix
void* multiplyElement(void* arg) {
    ThreadData* data = (ThreadData*)arg;
    int row = data->row;
    int col = data->col;

    matC[row][col] = 0;
    for (int i = 0; i < colsA; i++) {
        matC[row][col] += matA[row][i] * matB[i][col];
    }

    pthread_exit(0);
}

int main() {
    // Input dimensions of Matrix A
    cout << "Enter the dimensions of Matrix A (rows and columns): ";
    cin >> rowsA >> colsA;

    // Input dimensions of Matrix B
    cout << "Enter the dimensions of Matrix B (rows and columns): ";
    cin >> rowsB >> colsB;

    // Check if multiplication is possible
    if (colsA != rowsB) {
        cerr << "Error: Number of columns in Matrix A must equal number of rows in Matrix B for multiplication.\n";
        return 1;
    }

    // Initialize matrices
    matA.resize(rowsA, vector<int>(colsA));
    matB.resize(rowsB, vector<int>(colsB));
    matC.resize(rowsA, vector<int>(colsB));

    // Input elements for Matrix A
    cout << "Enter elements of Matrix A:\n";
    for (int i = 0; i < rowsA; i++) {
        for (int j = 0; j < colsA; j++) {
            cin >> matA[i][j];
        }
    }

    // Input elements for Matrix B
    cout << "Enter elements of Matrix B:\n";
    for (int i = 0; i < rowsB; i++) {
        for (int j = 0; j < colsB; j++) {
            cin >> matB[i][j];
        }
    }

    // Create threads
    vector<vector<pthread_t>> threads(rowsA, vector<pthread_t>(colsB)); //store thread id
    vector<vector<ThreadData>> threadData(rowsA, vector<ThreadData>(colsB)); //2d vector to store data

    // Create a thread for each element in the result matrix
    for (int i = 0; i < rowsA; i++) {
        for (int j = 0; j < colsB; j++) {
            threadData[i][j] = {i, j};
            pthread_create(&threads[i][j], nullptr, multiplyElement, &threadData[i][j]);

        }
    }

    // Join all threads
    for (int i = 0; i < rowsA; i++) {
        for (int j = 0; j < colsB; j++) {
            pthread_join(threads[i][j], nullptr);
        }
    }

    // Display the result matrix
    cout << "\nResultant Matrix (C = A * B):\n";
    for (int i = 0; i < rowsA; i++) {
        for (int j = 0; j < colsB; j++) {
            cout << matC[i][j] << " ";
        }
        cout << endl;
    }

    return 0;
}
