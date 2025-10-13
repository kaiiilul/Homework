#include <iostream>
using namespace std;

int akmnr(int m, int n) {
    const int MAX = 1000;//�w�q���|���W���A����Ӥp���M�|���|���X
    int stack[MAX];//�ŧi�@�Ӿ�ư}�C�ΨӼ������|
    int top = 0;//�O�����|���ݡA�M����l�]��0

    stack[top++] = m;//��m��������|�̭�

    while (top > 0) {    //����|���F�誺�ɭԤ~�~�����
        m = stack[--top]; // pop

        if (m == 0) {    //��m=0�ɡAn=n+1
            n = n + 1;
        }
        else if (n == 0) {    //��m!=0�Bn=0��
            n = 1;
            stack[top++] = m - 1;//�Nm-1���J���|�A�ǳƭp��A(m-1, 1)
        }
        else {
            stack[top++] = m - 1;//A(m-1, ...)
            stack[top++] = m;//���B�zA(m, n-1)
            n = n - 1; //�p��A(m, n-1)
        }
    }

    return n;
}

int main() {
    int m, n;
    cout << "��Jm�Mn: ";
    cin >> m >> n;//��J�ۤv�n�⪺�ƭ�
    cout << "Ackermann(" << m << ", " << n << ") = " << akmnr(m, n) << endl;//��X����
    return 0;
}
