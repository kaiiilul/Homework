#include <iostream>
#include <string>
using namespace std;

/*
 * X[]：原始集合元素陣列
 * Y[]：目前組成中的子集合
 * i：目前處理到的索引位置
 * n：原始集合的大小
 * t：目前子集合的長度（Y[] 的實際有效長度）
 */

void ps(string X[], string Y[], int i, int n, int t) {    
    if (i == n) {//遞迴終止條件
        cout << "{";
        for (int j = 0; j < t; j++) {
            cout << Y[j];
            if (j != t - 1) cout << ",";
        }
        cout << "}" << endl; //輸出子集合結尾並換行
        return;
    }
    ps(X, Y, i + 1, n, t);//不選擇X[i]，直接遞迴到下一個元素
                          //選擇X[i]，將其加入子集合Y[]，再遞迴
    Y[t] = X[i];                    
    ps(X, Y, i + 1, n, t + 1);     
}

int main() {
    int n;
    cout << "請輸入幾個數 : ";
    cin >> n;//輸入集合大小
    string* X = new string[n];
    string* Y = new string[n];
    cout << "輸入要的集合元素 : ";
    for (int i = 0; i < n; i++) {
        cin >> X[i];
    }
    cout << "集合的冪集是:" << endl;
    ps(X, Y, 0, n, 0);
    
    delete[] X; //清除動態配置的記憶體
    delete[] Y;

    return 0;
}
