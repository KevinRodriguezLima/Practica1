#include <iostream>
#include <vector>
#include <chrono>
#include <fstream>
#include <algorithm>
#include <sstream>

using namespace std;


void bubbleSort(vector<float>& arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; i++)
        for (int j = 0; j < n - i - 1; j++)
            if (arr[j] > arr[j + 1])
                swap(arr[j], arr[j + 1]);
}

void insertionSort(vector<float>& arr) {
    int n = arr.size();
    for (int i = 1; i < n; i++) {
        float key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

void shellSort(vector<float>& arr) {
    int n = arr.size();
    for (int x = n / 2; x > 0; x /= 2) {
        for (int i = x; i < n; i++) {
            float temp = arr[i];
            int j;
            for (j = i; j >= x && arr[j - x] > temp; j -= x)
                arr[j] = arr[j - x];
            arr[j] = temp;
        }
    }
}

void selectionSort(vector<float>& arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; i++) {
        int minIdx = i;
        for (int j = i + 1; j < n; j++)
            if (arr[j] < arr[minIdx])
                minIdx = j;
        swap(arr[minIdx], arr[i]);
    }
}

int partition(vector<float>& arr, int low, int high) {
    float pivot = arr[high];
    int i = (low - 1);
    for (int j = low; j <= high - 1; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return (i + 1);
}

void quickSort(vector<float>& arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

void heapify(vector<float>& arr, int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left] > arr[largest])
        largest = left;

    if (right < n && arr[right] > arr[largest])
        largest = right;

    if (largest != i) {
        swap(arr[i], arr[largest]);
        heapify(arr, n, largest);
    }
}

void heapSort(vector<float>& arr) {
    int n = arr.size();
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);
    for (int i = n - 1; i > 0; i--) {
        swap(arr[0], arr[i]);
        heapify(arr, i, 0);
    }
}

void merge(vector<float>& arr, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    vector<float> L(n1), R(n2);
    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort(vector<float>& arr, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

template <typename Func>
double tiempo(Func sortingFunction, vector<float>& arr) {
    auto start = chrono::high_resolution_clock::now();
    sortingFunction(arr);
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> duration = end - start;
    return duration.count();
}

vector<float> cargarDatos(const string& filename) {
    vector<float> datos;
    ifstream file(filename);
    float value;
    while (file >> value) {
        datos.push_back(value);
    }
    return datos;
}

int main() {
    //vector<string> filenames = {"DataGen1.txt", "DataGen05.txt", "DataGen025.txt"};
    vector<string> filenames = {"DataGen05.txt"};
    ofstream resultados("resultados22.csv");

    for (const auto& filename : filenames) {
        vector<float> datos = cargarDatos(filename);

        vector<float> aux = datos;
        /*double Bubble = tiempo(bubbleSort, aux);
        resultados << "Bubble Sort," << filename << "," << Bubble << "\n";

        aux = datos;
        double Insertion = tiempo(insertionSort, aux);
        resultados << "Insertion Sort," << filename << "," << Insertion << "\n";*/

        aux = datos;
        double Shell = tiempo(shellSort, aux);
        resultados << "Shell Sort," << filename << "," << Shell << "\n";

        /*aux = datos;
        double Selection = tiempo(selectionSort, aux);
        resultados << "Selection Sort," << filename << "," << Selection << "\n";

        aux = datos;
        double Quick = tiempo([](vector<float>& arr) { quickSort(arr, 0, arr.size() - 1); }, aux);
        resultados << "Quick Sort," << filename << "," << Quick << "\n";

        aux = datos;
        double Heap = tiempo(heapSort, aux);
        resultados << "Heap Sort," << filename << "," << Heap << "\n";

        aux = datos;
        double Merge = tiempo([](vector<float>& arr) { mergeSort(arr, 0, arr.size() - 1); }, aux);
        resultados << "Merge Sort," << filename << "," << Merge << "\n";*/
    }

    resultados.close();
    //cout << "Resultados guardados en resultados.csv" << endl;

    return 0;
}

