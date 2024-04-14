// The Banker's Algorithm is a resource allocation and deadlock avoidance algorithm used in operating systems to ensure that the system can allocate resources to processes in a safe manner without causing deadlocks. 
// The algorithm works by simulating the resource allocation process and checking for safety before granting the resources to a process. Each process declares the maximum number of resources of each type it may need. 
// The system maintains the number of available resources of each type. The system also maintains the number of resources allocated to each process. The algorithm checks if granting the requested resources to a process can lead to a safe state or not. 
// A state is considered safe if there exists a sequence of processes such that each process can obtain its maximum resources and terminate, allowing the next process to complete. 
// The Banker's Algorithm is a practical algorithm used in real-world operating systems to prevent deadlocks and ensure safe resource allocation.





#include <iostream>
using namespace std;

// Number of processes
#define N 5

// Number of resources
#define M 3

// Function to check if the system is in a safe state
bool isSafe(int allocation[N][M], int max[N][M], int need[N][M], int available[M]) {
    int work[M], finish[N];

    // Initialize work and finish arrays
    for (int i = 0; i < M; i++)
        work[i] = available[i];
    for (int i = 0; i < N; i++)
        finish[i] = 0;

    // Find an index i such that both conditions are satisfied
    int count = 0;
    while (count < N) {
        bool found = false;
        for (int i = 0; i < N; i++) {
            if (finish[i] == 0) {
                int j;
                found = true;
                for (j = 0; j < M; j++)
                    if (need[i][j] > work[j])
                        break;
                if (j == M) {
                    for (j = 0; j < M; j++)
                        work[j] += allocation[i][j];
                    finish[i] = 1;
                    count++;
                }
            }
        }

        // If no process can be executed, the system is in an unsafe state
        if (!found)
            return false;
    }

    // If all processes have been executed, the system is in a safe state
    return true;
}

int main() {
    int allocation[N][M] = { { 0, 1, 0 }, { 2, 0, 0 }, { 3, 0, 2 }, { 2, 1, 1 }, { 0, 0, 2 } };
    int max[N][M] = { { 0, 2, 2 }, { 3, 0, 2 }, { 4, 0, 3 }, { 3, 2, 2 }, { 2, 0, 2 } };
    int need[N][M];
    int available[M] = { 2, 2, 2 };

    // Calculate the need matrix
    for (int i = 0; i < N; i++)
        for (int j = 0; j < M; j++)
            need[i][j] = max[i][j] - allocation[i][j];

    // Check if the system is in a safe state
    if (isSafe(allocation, max, need, available))
        cout << "System is in safe state.\n";
    else
        cout << "System is in unsafe state.\n";

    return 0;
}
