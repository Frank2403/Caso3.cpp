#include <iostream>
#include <vector>
#include <chrono>
#include <algorithm>

// Funciones de ordenamiento
void bubbleSort(std::vector<int>& arr) {
    for (size_t i = 0; i < arr.size() - 1; ++i) {
        for (size_t j = 0; j < arr.size() - i - 1; ++j) {
            if (arr[j] > arr[j + 1]) {
                std::swap(arr[j], arr[j + 1]);
            }
        }
    }
}

void insertionSort(std::vector<int>& arr) {
    for (size_t i = 1; i < arr.size(); ++i) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            --j;
        }
        arr[j + 1] = key;
    }
}

void merge(std::vector<int>& arr, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;
    std::vector<int> L(n1), R(n2);
    for (int i = 0; i < n1; ++i) L[i] = arr[left + i];
    for (int i = 0; i < n2; ++i) R[i] = arr[mid + 1 + i];
    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) arr[k++] = L[i++];
        else arr[k++] = R[j++];
    }
    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];
}


void mergeSort(std::vector<int>& arr, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

int partition(std::vector<int>& arr, int low, int high) {
    int pivot = arr[high];
    int i = low - 1;
    for (int j = low; j < high; ++j) {
        if (arr[j] < pivot) {
            std::swap(arr[++i], arr[j]);
        }
    }
    std::swap(arr[i + 1], arr[high]);
    return i + 1;
}


void quickSort(std::vector<int>& arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

// Funciones de búsqueda
int linearSearch(const std::vector<int>& arr, int x) {
    for (size_t i = 0; i < arr.size(); ++i) {
        if (arr[i] == x) return i;
    }
    return -1;
}

int binarySearch(const std::vector<int>& arr, int x) {
    int left = 0, right = arr.size() - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (arr[mid] == x) return mid;
        if (arr[mid] < x) left = mid + 1;
        else right = mid - 1;
    }
    return -1;
}

// Función para medir el tiempo de ejecución
template <typename Func, typename... Args>
double measureTime(Func func, Args&&... args) {
    auto start = std::chrono::high_resolution_clock::now();
    func(std::forward<Args>(args)...);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;
    return duration.count();
}

int main() {
    std::vector<int> arr = {64, 34, 25, 12, 22, 11, 90};
    std::vector<int> arrCopy;

    // Medir tiempos de ordenamiento
    arrCopy = arr;
    double bubbleTime = measureTime(bubbleSort, arrCopy);

    arrCopy = arr;
    double insertionTime = measureTime(insertionSort, arrCopy);

    arrCopy = arr;
    double mergeTime = measureTime(mergeSort, arrCopy, 0, arrCopy.size() - 1);

    arrCopy = arr;
    double quickTime = measureTime(quickSort, arrCopy, 0, arrCopy.size() - 1);

    // Medir tiempos de búsqueda
    double linearTime = measureTime(linearSearch, arr, 22);
    std::sort(arr.begin(), arr.end());
    double binaryTime = measureTime(binarySearch, arr, 22);

    // Imprimir resultados
    std::cout << "Algoritmo\t\tTiempo (s)\n";
    std::cout << "Bubble Sort\t\t" << bubbleTime << "\n";
    std::cout << "Insertion Sort\t\t" << insertionTime << "\n";
    std::cout << "Merge Sort\t\t" << mergeTime << "\n";
    std::cout << "Quick Sort\t\t" << quickTime << "\n";
    std::cout << "Linear Search\t\t" << linearTime << "\n";
    std::cout << "Binary Search\t\t" << binaryTime << "\n";

    return 0;
}
