
#include <iostream>
#include <vector>
#include <stack>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <iomanip>
#include "Header.h"

using namespace std;

// ---------- Insertion Sort ----------
void insertionSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 1; i < n; ++i) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            --j;
        }
        arr[j + 1] = key;
    }
}

// ---------- Quick Sort (median-of-three, iterative) ----------
int medianOfThree(vector<int>& arr, int low, int high) {
    int mid = (low + high) / 2;
    if (arr[mid] < arr[low]) swap(arr[mid], arr[low]);
    if (arr[high] < arr[low]) swap(arr[high], arr[low]);
    if (arr[high] < arr[mid]) swap(arr[high], arr[mid]);
    return arr[mid];
}

int partition(vector<int>& arr, int low, int high) {
    int pivot = medianOfThree(arr, low, high);
    int left = low, right = high;
    while (true) {
        while (arr[left] < pivot) left++;
        while (arr[right] > pivot) right--;
        if (left >= right) return right;
        swap(arr[left++], arr[right--]);
    }
}

void quickSort(vector<int>& arr) {
    int n = arr.size();
    stack<pair<int, int>> s;
    s.push({ 0, n - 1 });
    while (!s.empty()) {
        int low = s.top().first;
        int high = s.top().second;
        s.pop();
        if (low < high) {
            int p = partition(arr, low, high);
            s.push({ low, p });
            s.push({ p + 1, high });
        }
    }
}

// ---------- Merge Sort (iterative bottom-up) ----------
void mergePass(vector<int>& arr, vector<int>& temp, int left, int mid, int right) {
    int i = left, j = mid, k = left;
    while (i < mid && j < right) {
        if (arr[i] <= arr[j])
            temp[k++] = arr[i++];
        else
            temp[k++] = arr[j++];
    }
    while (i < mid) temp[k++] = arr[i++];
    while (j < right) temp[k++] = arr[j++];
}

void mergeSort(vector<int>& arr) {
    int n = arr.size();
    vector<int> temp(n);
    for (int width = 1; width < n; width *= 2) {
        for (int i = 0; i < n; i += 2 * width) {
            int left = i;
            int mid = min(i + width, n);
            int right = min(i + 2 * width, n);
            mergePass(arr, temp, left, mid, right);
        }
        arr = temp;
    }
}

// ---------- Heap Sort ----------
void heapify(vector<int>& arr, int n, int i) {
    int largest = i, l = 2 * i + 1, r = 2 * i + 2;
    if (l < n && arr[l] > arr[largest]) largest = l;
    if (r < n && arr[r] > arr[largest]) largest = r;
    if (largest != i) {
        swap(arr[i], arr[largest]);
        heapify(arr, n, largest);
    }
}

void heapSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = n / 2 - 1; i >= 0; i--) heapify(arr, n, i);
    for (int i = n - 1; i > 0; i--) {
        swap(arr[0], arr[i]);
        heapify(arr, i, 0);
    }
}

// ---------- Composite Sort ----------
void compositeSort(vector<int>& arr) {
    if (arr.size() <= 1000) insertionSort(arr);
    else heapSort(arr);
}

// ---------- 工具函式 ----------
vector<int> generateRandomData(int size) {
    vector<int> data(size);
    for (int i = 0; i < size; i++) {
        data[i] = rand() % (size * 10) + 1;
    }
    return data;
}

// ⭐ 這個版本是印「全部」資料
void printData(const vector<int>& data) {
    cout << "[";
    for (size_t i = 0; i < data.size(); ++i) {
        cout << data[i];
        if (i != data.size() - 1) cout << ", ";
    }
    cout << "]" << endl;
}

// ---------- 主程式 ----------
int main() {
    srand(time(0));
    vector<int> sizes = { 500, 1000, 2000, 3000, 4000, 5000 };
    int M = 100; // 題目要求的實驗次數，可以設 100 或更高來確保時鐘精確

    cout << fixed << setprecision(6);
    cout << left << setw(10) << "Size"
         << setw(20) << "Insertion Sort"
         << setw(20) << "Quick Sort"
         << setw(20) << "Merge Sort"
         << setw(20) << "Heap Sort"
         << setw(20) << "Composite Sort" << endl;

    for (auto size : sizes) {
        // 呼叫改版後的函數，它內部會生出 M 個不同序列並累加時間
        double insertionTime = timeSortingAverage(insertionSort, size, M);
        double quickTime     = timeSortingAverage(quickSort, size, M);
        double mergeTime     = timeSortingAverage(mergeSort, size, M);
        double heapTime      = timeSortingAverage(heapSort, size, M);
        double compositeTime = timeSortingAverage(compositeSort, size, M);

        cout << left << setw(10) << size
             << setw(20) << insertionTime
             << setw(20) << quickTime
             << setw(20) << mergeTime
             << setw(20) << heapTime
             << setw(20) << compositeTime << endl;
    }
    return 0;
}
