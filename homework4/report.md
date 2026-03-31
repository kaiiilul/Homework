# 41343140

作業一
# 問題一
## 解題說明
## Max/Min Heap
Write a C++ abstract class similar to ADT 5.2 for the ADT MinPQ, which defines a min priority queue. Now write a C++ class MinHeap that derives from this abstract class and implements all the virtual functions of MinPQ. The complexity of each function should be the same as that for the corresponding function of MaxHeap.

寫一個 MinPQ抽象類別

然後做一個 MinHeap 類別，繼承 MinPQ 並完成所有功能

## 解題策略
需要實作的函式:

IsEmpty():用來判斷是否為空

Top():取最小值

Push(x):插入元素

Pop():用來刪除最小值

### 1.用陣列做Heap：

    parent = i / 2
    left child = 2*i
    right child = 2*i + 1

#### 2.插入（Push）：

    1.把元素加到最後
    2.與 parent 比較
    3.若較小 → 交換

#### 3.刪除最小值（Pop）：

    1.把 root 換成最後一個元素
    2.刪掉最後一個
    3.與較小的子節點比較
    4.若較大 → 交換


## 程式實作

以下為hw1 Max/Min Heap主要程式碼：

```cpp
#include <iostream>
#include <vector>
#include <stdexcept>

using namespace std;

template <class T>
class MinPQ {
public:
    virtual ~MinPQ() {}
    virtual bool IsEmpty() const = 0;             // 檢查是否為空
    virtual const T& Top() const = 0;             // 取得最小值
    virtual void Push(const T& item) = 0;         // 插入
    virtual void Pop() = 0;                       //彈出
};

template <class T>
class MinHeap : public MinPQ<T> {
private:
    vector<T> heap; 
    void HeapUp(int index) {
        while (index > 0) {
            int parent = (index - 1) / 2;
            if (heap[index] >= heap[parent]) break;
            swap(heap[index], heap[parent]);
            index = parent;
        }
    }

    void HeapDown(int index) {
        int size = heap.size();
        while (2 * index + 1 < size) {
            int left = 2 * index + 1;
            int right = 2 * index + 2;
            int smallest = left;

            if (right < size && heap[right] < heap[left])
                smallest = right;

            if (heap[index] <= heap[smallest]) break;
            swap(heap[index], heap[smallest]);
            index = smallest;
        }
    }

public:
    bool IsEmpty() const override {  //（override）覆寫父類別的虛擬函式
        return heap.empty();
    }

    // 取得最小值
    const T& Top() const override {
        if (IsEmpty()) throw runtime_error("Heap 是空的");
        return heap[0];
    }

    void Push(const T& item) override {
        heap.push_back(item);
        HeapUp(heap.size() - 1);
    }

    void Pop() override {
        if (IsEmpty()) throw runtime_error("Heap 是空的");
        heap[0] = heap.back();
        heap.pop_back();
        if (!IsEmpty())
            HeapDown(0);
    }


    void Print() const {
        cout << "陣列內容為: ";
        for (int i = 0; i < heap.size(); i++) {
            cout << heap[i] << " ";
        }
        cout << endl;
    }
};
int main() {
    MinHeap<int> h;

    h.Push(5);  
    h.Push(2); 
    h.Push(8);  
    h.Push(6);
    h.Push(1);  

    cout << "Heap content: ";
    h.Print();  // 應該是 1 在最前面

    cout << "Top: " << h.Top() << endl;  
    h.Pop();
    cout<<"------------"<<endl;
    cout << "Top: " << h.Top() << endl; 

    return 0;
}
```

## 效能分析

### 時間複雜度：

    Top():O(1)
    Push(x):O(log n)
    Pop():O(log n)
    所以全部的時間複雜度為：O(n log n)

### 空間複雜度：
    heap：O(n)

## 測試與驗證

### 測試案例

| 測試案例 | 輸入參數P1  | 輸入參數P2 | 預計輸出 |實際輸出|輸入X|輸出P1數值|
|----------|--------------|----------|----------|----------|----------|----------|
| 測試一   |  3 4 3 -2 2 3 1     | 2 5 2 -1 0        | P1: 4x^3-2x^2 + 3x^1       |P1: 4x^3-2x^2 + 3x^1|2|30|
|    |       |        | P2: 5x^2-1x^0       |P2: 5x^2-1x^0|||
|    |      |        | P1 + P2: 4x^3 + 3x^2 + 3x^1-1x^0       |P1 + P2: 4x^3 + 3x^2 + 3x^1-1x^0|||
|    |      |         | P1 - P2: 4x^3-7x^2 + 3x^1 + 1x^0      |P1 - P2: 4x^3-7x^2 + 3x^1 + 1x^0|||
|    |      |         | P1 * P2: 20x^5-10x^4 + 11x^3 + 2x^2-3x^      |P1 * P2: 20x^5-10x^4 + 11x^3 + 2x^2-3x^|||



### 編譯與執行指令

```shell
$ g++ hw3 Polynomial.cpp -std=c++17 -o hw3 Polynomial.exe
$ .\hw3 Polynomial.exe
輸入第一個多項式 (n c1 e1 c2 e2 ...): 3 4 3 -2 2 3 1
輸入第二個多項式 (n c1 e1 c2 e2 ...): 2 5 2 -1 0
P1: 4x^3-2x^2 + 3x^1
P2: 5x^2-1x^0
P1 + P2: 4x^3 + 3x^2 + 3x^1-1x^0
P1 - P2: 4x^3-7x^2 + 3x^1 + 1x^0
P1 * P2: 20x^5-10x^4 + 11x^3 + 2x^2-3x^1
輸入x的質來計算P1: 2
P1(2) = 30
```


## 申論及開發報告

### 申論

多項式(Polynomial)作為數學中的重要概念,常常出現在計算與分析中。而在程式設計中，將多項式抽象化並加以實作，可以幫助我們理解資料結構的核心概念。本次作業以多項式的ADT(抽象資料型態)與運算符多載為核心，實現了多項式的基本運算與評估功能,讓我在實作中收穫良多。

#### 多項式 ADT：資料抽象的實現

ADT(抽象資料型態)是一種程式設計的思維方式，強調操作的行為而非內部細節。在這次作業中，多項式被設計為由「係數」與「指數」構成的一組節點集合，並使用鏈結串列進行實現。透過這種結構，我們實現了多項式的插入(addTerm)、刪除(clear)與顯示內容(oper ator<<)等基本操作。

鏈結串列的使用，讓多項式的項目管理更加靈活。同時透過指數的降序排列，我們可以有效避免不必要的遍歷與冗餘操作，進一步提升程式的效能

#### 運算符多載：

C++的運算符多載是一項強大的功能，它允許我們重新定義運算符的行為，使程式操作更直觀。在這次作業中，我們通過運算符多載實現了輸入(>>)、輸出(<<)、加法(+)、減法(-)與乘法(*)的功能。

例如輸入多項式時，使用cin >> pl,讓程式自動處理係數與指數的輸入;而輸出時透過 cout << pl，以數學表達形式顯示多項式。這種方式不僅貼近數學表達，還讓多項式運算的程式邏輯更符合使用者的直覺需求。加上加減乘的運算符多載，程式中的多項式操作幾乎與數學公式無異，大大提升了程式的易用性和可讀性。

#### 程式設計的價值：

這次作業讓我認識到程式設計的核心價值在於，將抽象的數學概念轉化為具體的程式實現，並透過靈活的資料結構設計，將複雜的運算簡化為簡單直觀的操作。多項式ADT和運算符多載的結合，幫助我加深了對資料結構的理解。

### 開發報告
#### 設計目標

實現多項式的抽象資料型態(ADT),以便對多項式進行高效的數據管理。 支援多項式的基本運算(加法、減法、乘法)與評估功能(Eval)。 使用C++的運算符多載,讓多項式的操作更加直觀,類似數學表達式。

確保程式結構清晰、邏輯完整,並便於擴展。

#### 開發過程

1.程式架構設計
    
    我們設計了一個 Polynomial 類別,使用鏈結串列結構儲存多項式的每一項。
    
    每一個節點包含三個屬性:
    
    係數(coef): 儲存多項式的係數。
    
    指數(exp): 儲存多項式的指數。
    
    指標(link): 指向下一個節點。此外,實現了以下基礎功能:
    
    新增項目(addTerm): 支援按指數降序插入,並合併相同指數的項目。
    
    顯示多項式(operator<<): 支援多項式內容的友好輸出。

2.運算符多載

    為了讓多項式操作更加符合數學習慣,我們透過運算符多載實現了以下功能:
    
    加法(operator+): 計算兩個多項式的和。
    
    減法(operator): 計算兩個多項式的差。
    
    乘法(operator):*計算兩個多項式的積。
    
    輸入(operator>>): 讓多項式的輸入更加簡潔直觀。
    
    輸出(operator<<): 將多項式輸出為數學格式。

3.功能擴展

    在完成多項式的基本運算後,我們進一步實現了多項式評估功能:
    
    評估（浮動x）：
    
    計算多項式在指定變數x值下的結果。
    
    使用迴圈計算公式result+=coefxx exp,確保準確性與效能。

4.程式結構優化

    多項式資料結構: 使用鏈結串列結構表示多項式,支援高效的插入與刪除操作。
    
    多項式的操作: 透過運算符多載實現了輸入、輸出、加減乘運算,以及X的點值計算。
    
    程式設計風格: 每個函數的功能劃分清晰,便於維護與擴展。
