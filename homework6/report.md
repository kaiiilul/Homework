# 41343120
# 41343140

作業3

## 解題說明
本題要求實作四種排序演算法：Insertion Sort、Quick Sort（Median-of-Three）、Iterative Merge Sort 以及 Heap Sort，並比較它們在最差情況（Worst Case）下的執行效能。首先完成各排序演算法的程式設計，並利用測試資料驗證排序結果是否正確。接著針對不同資料規模（500、1000、2000、3000、4000、5000）產生對應的最差情況測試資料，利用高精度計時器量測執行時間。由於部分排序時間可能小於計時器精度，因此透過重複執行多次取平均值的方式提高量測準確度。最後將各演算法在不同資料量下的最差情況執行時間進行比較與分析，找出在 Worst Case 條件下表現最佳的排序方法，作為複合排序函式設計的依據。

### 解題策略
本程式以模組化方式實作 Insertion Sort、Quick Sort、Merge Sort、Heap Sort 及 Composite Sort。利用亂數產生不同規模的測試資料，並使用高精度計時器量測各排序演算法的執行時間。為降低計時誤差，先預先建立多組測試資料，再重複執行排序多次並取平均值作為結果。Composite Sort 根據資料量大小選擇不同排序方式，小型資料使用 Insertion Sort，大型資料使用 Heap Sort，以兼顧執行效率與穩定性。透過實驗結果比較各演算法效能，分析其在不同資料規模下的表現。
## 程式實作
Header.h
```cpp
// Header.h
#ifndef HEADER_H
#define HEADER_H

#include <vector>
using namespace std;

// 排序函式
void insertionSort(vector<int>& arr);
void quickSort(vector<int>& arr);
void mergeSort(vector<int>& arr);
void heapSort(vector<int>& arr);
void compositeSort(vector<int>& arr);

// 工具函式
vector<int> generateRandomData(int size);
void printData(const vector<int>& data);

// 測量時間模板
template<typename Func>
double timeSortingAverage(Func sortFunc, int size, int M) {
    // 1. 為了不把「產生隨機數據」的時間算進去，我們先把 M 組隨機數據通通生好
    vector<vector<int>> testData(M);
    for (int i = 0; i < M; ++i) {
        testData[i] = generateRandomData(size);
    }

    // 2. 開始計時（只把「純排序」的過程包進去）
    auto start = chrono::high_resolution_clock::now();
    for (int i = 0; i < M; ++i) {
        sortFunc(testData[i]); // 每組隨機排列只排序一次
    }
    auto end = chrono::high_resolution_clock::now();

    // 3. 計算總執行時間（秒）
    chrono::duration<double> elapsed = end - start;
    
    // 4. 回傳平均時間（如果你想輸出總時間也可以，通常回傳 平均 = 總時間 / M）
    return elapsed.count() / M; 
}

#endif // HEADER_H
```
sorting
```cpp
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

//這個版本是印「全部」資料
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
```

## 效能分析
    
Insertion Sort:

最佳情況:O(n) 

平均情況:O(n²)

最差情況:O(n²)      
Quick Sort（Median-of-Three）:

最佳情況:O(n log n)

平均情況:O(n log n) 

最差情況:O(n²)

Merge Sort:

最佳情況:O(n log n)

平均情況:O(n log n)

最差情況:O(n log n)

Heap Sort:

最佳情況:O(n log n)

平均情況:O(n log n)

最差情況:O(n log n) 

Composite Sort:

最佳情況:視資料量所選演算法而定

平均情況:視資料量所選演算法而定

最差情況:O(n log n)

Insertion Sort

Insertion Sort 的實作方式簡單且額外空間需求低，當資料量較小時具有不錯的效率，但隨著資料量增加，其時間複雜度為 O(n²)，執行時間會明顯增加，因此不適合大型資料排序。

Quick Sort

Quick Sort 採用 Median-of-Three 方法選擇 Pivot，可降低因資料分布不均而造成效能下降的機率。在大多數情況下可達到 O(n log n) 的效率，但理論上的最差情況仍可能退化至 O(n²)。

Merge Sort

Merge Sort 採用 Iterative Bottom-Up 方式實作，其時間複雜度在所有情況下皆為 O(n log n)，效能穩定且不受資料排列方式影響，但需要額外 O(n) 的暫存空間。

Heap Sort

Heap Sort 利用最大堆積（Max Heap）進行排序，在最佳、平均及最差情況下皆能維持 O(n log n) 的時間複雜度，且只需 O(1) 額外空間，因此適合處理大型資料。

Composite Sort

Composite Sort 根據資料量大小選擇不同排序方法。當資料量小於等於 1000 筆時使用 Insertion Sort，以減少演算法額外開銷；當資料量大於 1000 筆時改用 Heap Sort，以獲得穩定的 O(n log n) 效能。因此 Composite Sort 能兼顧小型資料的執行速度與大型資料的穩定性，在整體效能上較為均衡。

## 測試與驗證



測試結果為:

|資料數|Insertion Sort|Quick Sort|Merge Sort|Heap Sort|Composite Sort|
|----------|----------|--------------|----------|----------|--------------|
|500|0.003784|0.002677|0.000427|0.001062|0.003360|
|1000|0.013351|0.005167|0.000912|0.002208|0.013419|
|2000|0.051605|0.010360|0.001738|0.004690|0.004677|
|3000|0.107093|0.015902|0.002687|0.007792|0.007449|
|4000|0.209377|0.021954|0.003690|0.010441|0.010231|
|5000|0.329844|0.026545|0.004715|0.013257|0.013027|

<img width="1919" height="1137" alt="image" src="https://github.com/user-attachments/assets/f751de03-d675-4911-8323-55077456af39" />

以下是比較圖:

<img width="855" height="547" alt="sorting_chart" src="https://github.com/user-attachments/assets/dba49483-e194-4728-9b11-ca8363399fa8" />


## 結論
本專題成功實作 Insertion Sort、Quick Sort（Median-of-Three）、Iterative Merge Sort、Heap Sort 以及 Composite Sort，並透過不同規模的隨機資料進行效能測試與分析。實驗結果顯示，各排序演算法在時間複雜度上的理論差異與實際執行時間大致相符，其中 Insertion Sort 僅適合小規模資料，在資料量增加時效能明顯下降；Quick Sort 在一般情況下表現良好，但仍可能因資料分布而退化；Merge Sort 與 Heap Sort 則在最佳、平均與最差情況下皆維持 O(n log n)，具有較穩定的效能表現。

## 申論及開發報告
1. 為何 Insertion Sort 適合小資料:因為其在資料接近有序時接近 O(n)，且常數開銷小，但在大資料下會退化為 O(n²)。
2. 為何 Merge Sort 較穩定:因為不論資料排列如何，都會固定進行分割與合併，因此時間複雜度始終為 O(n log n)。
3. 為何 Heap Sort 可以保證 O(n log n):因為每次取出最大值與維護堆結構的操作皆為 O(log n)，整體固定進行 n 次。
4. 為何要使用 Composite Sort:因為不同排序演算法在不同資料規模下效率不同，透過混合策略可以提升整體效能。
5. 為何 Quick Sort 仍可能退化:因為在極端或特殊資料分布下，即使使用 Median-of-Three，仍可能造成不均勻分割。

## 分工
41343140黃鉑凱:程式實作以及測試與驗證

41343120洪宸偉:解題說明、解題策略、效能分析、結論申論及開發報告

