#include <iostream>
using namespace std;

int akm(int m, int n) {
    if (m == 0)//��m=0�ɡA�^�ǵ��׬�n+1
        return n + 1;
    else if (n == 0)//��m!=0�Bn=0�ɡA���j�p��akm(m-1,1)
        return akm(m - 1, 1);
    else//��S���ŦX�W�z����ӱ���A�]�N�O��m!=0�Bn=!0�ɡA���j�p��akm(m-1,akm(m,n-1))
        return akm(m - 1, akm(m, n - 1));
}

int main() {
    int m, n;
    cout << "��Jm�Mn: ";
    cin >> m >> n;//��J�ۤv�n�⪺�ƭ�
    cout << "Ackermann(" << m << ", " << n << ") = " << akm(m, n) << endl;//��X����
    return 0;
}
