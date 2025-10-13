#include <iostream>
using namespace std;

int akm(int m, int n) {
    if (m == 0)//當m=0時，回傳答案為n+1
        return n + 1;
    else if (n == 0)//當m!=0且n=0時，遞迴計算akm(m-1,1)
        return akm(m - 1, 1);
    else//當沒有符合上述的兩個條件，也就是當m!=0且n=!0時，遞迴計算akm(m-1,akm(m,n-1))
        return akm(m - 1, akm(m, n - 1));
}

int main() {
    int m, n;
    cout << "輸入m和n: ";
    cin >> m >> n;//輸入自己要算的數值
    cout << "Ackermann(" << m << ", " << n << ") = " << akm(m, n) << endl;//輸出答案
    return 0;
}
