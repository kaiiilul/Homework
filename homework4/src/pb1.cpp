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
