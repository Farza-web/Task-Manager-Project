#include <iostream>
using namespace std;

const int MAX = 100;

string names[MAX];
int priorities[MAX];
float durations[MAX];   // in hours
float values[MAX];      // productivity value
int taskCount = 0;

void inputTasks() {
    cout << "\n\t\t\t************** Task Manager ****************\n\n";
    cout << "How many tasks do you want to enter? " << endl << "Enter Number: ";
    cin >> taskCount;

    while (taskCount <= 0 || taskCount > MAX) {
        cout << "Invalid number of tasks. Please enter a value between 1 and " << MAX << ": ";
        cin >> taskCount;
    }

    for (int i = 0; i < taskCount; i++) {
        cout << "\nEnter details for Task " << (i + 1) << ":\n";
        cout << "Name: ";
       cin>> names[i];

        cout << "Priority (1=High, 5=Low): ";
        cin >> priorities[i];
        while (priorities[i] < 1 || priorities[i] > 5) {
            cout << "Invalid priority. Please enter a value between 1 and 5: ";
            cin >> priorities[i];
        }

        cout << "Duration (in hours): ";
        cin >> durations[i];
        while (durations[i] <= 0) {
            cout << "Invalid duration. Enter a positive number: ";
            cin >> durations[i];
        }

        cout << "Productivity Value: ";
        cin >> values[i];
        while (values[i] < 0) {
            cout << "Invalid value. Enter a non-negative number: ";
            cin >> values[i];
        }
    }
}

void printTasks() {
    cout << "\nTask List:\n";
    cout << "Name\t\tPriority\tDuration\tValue\n";

    for (int i = 0; i < taskCount; i++) {
        cout << names[i] << "\t\t"
             << priorities[i] << "\t\t"
             << durations[i] << "\t\t"
             << values[i] << endl;
    }

    cout << "-------------------------------------------\n";
}

// Insertion Sort by Priority
void insertionSort() {
    for (int i = 1; i < taskCount; i++) {
        int key = priorities[i];
        string n = names[i];
        float d = durations[i];
        float v = values[i];
        int j = i - 1;

        while (j >= 0 && priorities[j] > key) {
            priorities[j + 1] = priorities[j];
            names[j + 1] = names[j];
            durations[j + 1] = durations[j];
            values[j + 1] = values[j];
            j--;
        }

        priorities[j + 1] = key;
        names[j + 1] = n;
        durations[j + 1] = d;
        values[j + 1] = v;
    }
}

// Selection Sort by Duration
void selectionSort() {
    for (int i = 0; i < taskCount - 1; i++) {
        int minIdx = i;
        for (int j = i + 1; j < taskCount; j++) {
            if (durations[j] < durations[minIdx])
                minIdx = j;
        }
        swap(durations[i], durations[minIdx]);
        swap(names[i], names[minIdx]);
        swap(priorities[i], priorities[minIdx]);
        swap(values[i], values[minIdx]);
    }
}

// Merge Sort by Priority
void merge(int l, int m, int r) {
    int n1 = m - l + 1;
    int n2 = r - m;

    int Lp[MAX], Rp[MAX];
    float Ld[MAX], Rd[MAX], Lv[MAX], Rv[MAX];
    string Ln[MAX], Rn[MAX];

    for (int i = 0; i < n1; i++) {
        Lp[i] = priorities[l + i];
        Ld[i] = durations[l + i];
        Lv[i] = values[l + i];
        Ln[i] = names[l + i];
    }

    for (int j = 0; j < n2; j++) {
        Rp[j] = priorities[m + 1 + j];
        Rd[j] = durations[m + 1 + j];
        Rv[j] = values[m + 1 + j];
        Rn[j] = names[m + 1 + j];
    }

    int i = 0, j = 0, k = l;

    while (i < n1 && j < n2) {
        if (Lp[i] <= Rp[j]) {
            priorities[k] = Lp[i];
            durations[k] = Ld[i];
            values[k] = Lv[i];
            names[k] = Ln[i];
            i++;
        } else {
            priorities[k] = Rp[j];
            durations[k] = Rd[j];
            values[k] = Rv[j];
            names[k] = Rn[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        priorities[k] = Lp[i];
        durations[k] = Ld[i];
        values[k] = Lv[i];
        names[k] = Ln[i];
        i++;
        k++;
    }

    while (j < n2) {
        priorities[k] = Rp[j];
        durations[k] = Rd[j];
        values[k] = Rv[j];
        names[k] = Rn[j];
        j++;
        k++;
    }
}

void mergeSort(int l, int r) {
    if (l < r) {
        int m = (l + r) / 2;
        mergeSort(l, m);
        mergeSort(m + 1, r);
        merge(l, m, r);
    }
}

// Quick Sort by Priority
int partition(int low, int high) {
    int pivot = priorities[high];
    int i = low - 1;
    for (int j = low; j < high; j++) {
        if (priorities[j] < pivot) {
            i++;
            swap(priorities[i], priorities[j]);
            swap(durations[i], durations[j]);
            swap(values[i], values[j]);
            swap(names[i], names[j]);
        }
    }
    swap(priorities[i + 1], priorities[high]);
    swap(durations[i + 1], durations[high]);
    swap(values[i + 1], values[high]);
    swap(names[i + 1], names[high]);
    return i + 1;
}

void quickSort(int low, int high) {
    if (low < high) {
        int pi = partition(low, high);
        quickSort(low, pi - 1);
        quickSort(pi + 1, high);
    }
}

// Fractional Knapsack based on value/duration
void fractionalKnapsack(float maxTime) {
    float ratio[MAX];
    for (int i = 0; i < taskCount; i++)
        ratio[i] = values[i] / durations[i];

    // Sort by ratio descending
    for (int i = 0; i < taskCount - 1; i++) {
        for (int j = i + 1; j < taskCount; j++) {
            if (ratio[j] > ratio[i]) {
                swap(ratio[i], ratio[j]);
                swap(values[i], values[j]);
                swap(durations[i], durations[j]);
                swap(names[i], names[j]);
                swap(priorities[i], priorities[j]);
            }
        }
    }

    float totalValue = 0.0;
    float timeUsed = 0.0;

    cout << "\nTasks selected for " << maxTime << " hours:\n";
    for (int i = 0; i < taskCount && timeUsed < maxTime; i++) {
        if (durations[i] + timeUsed <= maxTime) {
            cout << names[i] << " (Full) - " << durations[i] << " hrs\n";
            totalValue += values[i];
            timeUsed += durations[i];
        } else {
            float remain = maxTime - timeUsed;
            cout << names[i] << " (Partial) - " << remain << " hrs\n";
            totalValue += values[i] * (remain / durations[i]);
            timeUsed = maxTime;
        }
    }

    cout << "Total Productivity Value Achieved: " << totalValue << "\n";
}

int main() {
    inputTasks();  // Fill the task arrays

    int choice = -1;

    while (choice != 0) {
        cout << "\nMenu:\n";
        cout << "1. Print Tasks\n";
        cout << "2. Sort by Priority (Merge Sort)\n";
        cout << "3. Sort by Priority (Quick Sort)\n";
        cout << "4. Sort by Priority (Insertion Sort)\n";
        cout << "5. Sort by Duration (Selection Sort)\n";
        cout << "6. Fractional Knapsack (Optimize tasks by time)\n";
        cout << "0. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                printTasks();
                break;
            case 2:
                mergeSort(0, taskCount - 1);
                printTasks();
                break;
            case 3:
                quickSort(0, taskCount - 1);
                printTasks();
                break;
            case 4:
                insertionSort();
                printTasks();
                break;
            case 5:
                selectionSort();
                printTasks();
                break;
            case 6: {
                float maxTime;
                cout << "Enter available time (in hours): ";
                cin >> maxTime;
                if (maxTime <= 0) {
                    cout << "Time must be positive.\n";
                } else {
                    fractionalKnapsack(maxTime);
                }
                break;
            }
            case 0:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid option.\n";
        }
    }

    return 0;
}

