# 41343140

作業一
# 問題一
## 解題說明
## Max/Min Heap
Write a C++ abstract class similar to ADT 5.2 for the ADT MinPQ, which defines a min priority queue. Now write a C++ class MinHeap that derives from this abstract class and implements all the virtual functions of MinPQ. The complexity of each function should be the same as that for the corresponding function of MaxHeap.

寫一個 MinPQ抽象類別

然後做一個 MinHeap 類別，繼承 MinPQ 並完成所有功能

## 解題策略
需要做的函式:

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

| 測試案例 | 輸入參數 | 預計輸出 |實際輸出|
|----------|--------------|----------|----------|
| 測試一 | 5 2 8 6 1 | 1 2 8 6 5 |1 2 8 6 5 |
| 測試二 | 3 2 7 1 9 4 6 8 | 1 2 4 3 9 7 6 8 |1 2 4 3 9 7 6 8|





## 申論及開發報告

### 申論

優先佇列是一種抽象資料型態，它的特點是每次取出的元素都具有最高或最低優先權。在這題我們要做「最小優先佇列（MinPQ）」，即每次取出的元素為最小值。

Heap 是實作優先佇列最常見的資料結構之一，其中 Min Heap 具有以下特性：

    1.為一棵完全二元樹
    2.每個節點的值皆小於或等於其子節點
    3.根節點為整個結構中的最小值

透過這樣的結構，可以有效率地支援以下操作：

    插入元素（Push）
    刪除最小值（Pop）
    取得最小值（Top）

### 開發報告

#### 1.抽象類別設計（MinPQ）
    定義虛擬函式：
        IsEmpty()：判斷是否為空
        Top()：回傳最小元素
        Push(x)：插入元素
        Pop()：刪除最小元素

#### 2.MinHeap 資料結構設計

    採用陣列（Array）實作完全二元樹：
        父節點：i / 2
        左子節點：2*i
        右子節點：2*i + 1

#### 3.核心演算法

    插入（Push）
    刪除最小值（Pop）
    取得最小值（Top）

### 優點
    1.搜尋效率佳（平均情況）
    2.支援有序資料操作
    3.操作靈活
    4.結構直觀
    
### 缺點
    1.最壞情況效率差
    2.高度不穩定
    3.需要額外記憶體
    4.效能不如平衡樹穩定
    
# 問題二
## 解題說明
## Binary Search Tree
(a.)Write a program to start with an initially empty binary search tree and make n random insertions. Use a uniform random number generator to obtain the values to be inserted. Measure the height of the resulting binary search tree and divide this height by log₂n. Do this for n = 100, 500, 1000, 2000, 3000, ..., 10,000. Plot the ratio height / log₂n as a function of n. The ratio should be approximately constant (around 2). Verify that this is so.

隨機插入 + 高度分析

## 解題策略
需要做的東西:

    1.建立空 BST
    2.插入 n 個「隨機數」
    3.計算樹的高度
    4.計算height / log₂(n)
    5.畫圖並觀察是否接近常數（約 ≈ 2）

#### 然後(b.)刪除節點<，其實就是從 BST 刪除 key = k 的節點並分析時間複雜度
## 解題策略

    1.沒有子節點 → 直接刪除
    2.有一個子節點 → 用子節點取代
    3.有兩個子節點 → 找右子樹最小值（或左子最大值）取代，然後遞迴刪除

## 程式實作

以下為hw1 Binary Search Tree(a.)主要程式碼：

```cpp
#include <iostream>
#include <cmath>
#include <cstdlib>
#include <ctime>
using namespace std;

struct Node {
    int val;  // node 值 
    Node* left;   //左子樹
    Node* right;  //右子樹
};

Node* insert(Node* root, int x) {
    if (root == nullptr) {
        root = new Node;
        root->val = x;
        root->left = nullptr;
        root->right = nullptr;
        return root;
    }
    if (x < root->val)
        root->left = insert(root->left, x);
    else
        root->right = insert(root->right, x);
    return root;
}

int getHeight(Node* root) {
    if (root == nullptr) return 0;
    int l = getHeight(root->left);
    int r = getHeight(root->right);
    return max(l, r) + 1;
}

int getRandom(int min, int max) {
    return rand() % (max - min + 1) + min;
}

int main() {
    srand(time(0));

    for (int n =100; n <= 500; n += 400) {
    	
        Node* root = nullptr;
        for (int i = 0; i < n; i++) {
            int x = getRandom(1, n * 10);
            root = insert(root, x);
        }
        int h = getHeight(root);
        double logn = log2(n);
        double ratio = h / logn;
        cout << "n = " << n << ", height = " << h << ", log2(n) = " << logn << ", ratio = " << ratio << endl;
    }
    
    
    

    for (int n =1000; n <= 10000; n += 1000) {
    	
        Node* root = nullptr;
        for (int i = 0; i < n; i++) {
            int x = getRandom(1, n * 10);
            root = insert(root, x);
        }
        int h = getHeight(root);
        double logn = log2(n);
        double ratio = h / logn;
        cout << "n = " << n << ", height = " << h << ", log2(n) = " << logn << ", ratio = " << ratio << endl;
    }
    return 0;
}
```
以下為hw1 Binary Search Tree(b.)主要程式碼：

```cpp
#include <iostream>
using namespace std;

struct Node {
    int key;
    Node* left;
    Node* right;
};

Node* findMin(Node* root) {
    while (root->left != nullptr)
        root = root->left;
    return root;
}

Node* deleteNode(Node* root, int k) {
    if (root == nullptr) return nullptr;

    if (k < root->key) {
        root->left = deleteNode(root->left, k);
    } else if (k > root->key) {
        root->right = deleteNode(root->right, k);
    } else {
        // 找到節點
        if (root->left == nullptr && root->right == nullptr) {
            delete root;
            return nullptr;
        } else if (root->left == nullptr) {
            Node* temp = root->right;
            delete root;
            return temp;
        } else if (root->right == nullptr) {
            Node* temp = root->left;
            delete root;
            return temp;
        } else {
            Node* temp = findMin(root->right);
            root->key = temp->key;
            root->right = deleteNode(root->right, temp->key);
        }
    }
    return root;
}
```

## 效能分析

### 時間複雜度：

(a.)

    insert	 平均時間:O(log n)	最壞時間:O(n)
    插入n次   平均時間:O(log n)	最壞時間:O(n*n) 
    height   平均時間:O(n)	    最壞時間:O(n)
(b.)

    delete Ｎode	平均時間:O(log n)	最壞時間:O(n)
    
### 空間複雜度：
    BST：O(n)
    總空間複雜度：O(n)

## 測試與驗證

### 測試案例

| 測試案例 | 輸入參數n | 預計輸出 |實際輸出|
|----------|--------------|----------|----------|
| 測試一 | 100 | 14,2.10721 | 14,2.10721 |
| 測試二 | 500 | 18,2.00763 | 18,2.00763 |
| 測試三 | 1000 | 22,2.20755 | 22,2.20755 |
| 測試四 | 2000 | 25,2.27982 | 25,2.27982 |
| 測試五 | 3000 | 26,2.25094 | 26,2.25094 |
| 測試六 | 4000 | 26,2.17286 | 26,2.17286 |
| 測試七 | 5000 | 29,2.36008 | 29,2.36008 |
| 測試八 | 6000 | 31,2.46997 | 31,2.46997 |
| 測試九 | 7000 | 27,2.11381 | 27,2.11381 |
| 測試十 | 8000 | 33,2.54516 | 33,2.54516 |
| 測試十一 | 9000 | 29,2.20772| 29,2.20772 |
| 測試十二 | 10000 | 33,2.4835 | 33,2.4835 |


測試輸出

    n = 100, height = 14, log2(n) = 6.64386, ratio = 2.10721
    n = 500, height = 18, log2(n) = 8.96578, ratio = 2.00763
    n = 1000, height = 22, log2(n) = 9.96578, ratio = 2.20755
    n = 2000, height = 25, log2(n) = 10.9658, ratio = 2.27982
    n = 3000, height = 26, log2(n) = 11.5507, ratio = 2.25094
    n = 4000, height = 26, log2(n) = 11.9658, ratio = 2.17286
    n = 5000, height = 29, log2(n) = 12.2877, ratio = 2.36008
    n = 6000, height = 31, log2(n) = 12.5507, ratio = 2.46997
    n = 7000, height = 27, log2(n) = 12.7731, ratio = 2.11381
    n = 8000, height = 33, log2(n) = 12.9658, ratio = 2.54516
    n = 9000, height = 29, log2(n) = 13.1357, ratio = 2.20772
    n = 10000, height = 33, log2(n) = 13.2877, ratio = 2.4835
