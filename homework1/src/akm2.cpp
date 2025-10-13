#include <iostream>
using namespace std;

int akmnr(int m, int n) {
    const int MAX = 1000;//定義堆疊的上限，不能太小不然會堆疊溢出
    int stack[MAX];//宣告一個整數陣列用來模擬堆疊
    int top = 0;//記錄堆疊頂端，然後把初始設為0

    stack[top++] = m;//把m給推到堆疊裡面

    while (top > 0) {    //當堆疊有東西的時候才繼續執行
        m = stack[--top]; // pop

        if (m == 0) {    //當m=0時，n=n+1
            n = n + 1;
        }
        else if (n == 0) {    //當m!=0且n=0時
            n = 1;
            stack[top++] = m - 1;//將m-1推入堆疊，準備計算A(m-1, 1)
        }
        else {
            stack[top++] = m - 1;//A(m-1, ...)
            stack[top++] = m;//先處理A(m, n-1)
            n = n - 1; //計算A(m, n-1)
        }
    }

    return n;
}

int main() {
    int m, n;
    cout << "輸入m和n: ";
    cin >> m >> n;//輸入自己要算的數值
    cout << "Ackermann(" << m << ", " << n << ") = " << akmnr(m, n) << endl;//輸出答案
    return 0;
}
