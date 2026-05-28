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
