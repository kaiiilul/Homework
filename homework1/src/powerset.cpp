#include <iostream>
#include <string>
using namespace std;

/*
 * X[]�G��l���X�����}�C
 * Y[]�G�ثe�զ������l���X
 * i�G�ثe�B�z�쪺���ަ�m
 * n�G��l���X���j�p
 * t�G�ثe�l���X�����ס]Y[] ����ڦ��Ī��ס^
 */

void ps(string X[], string Y[], int i, int n, int t) {    
    if (i == n) {//���j�פ����
        cout << "{";
        for (int j = 0; j < t; j++) {
            cout << Y[j];
            if (j != t - 1) cout << ",";
        }
        cout << "}" << endl; //��X�l���X�����ô���
        return;
    }
    ps(X, Y, i + 1, n, t);//�����X[i]�A�������j��U�@�Ӥ���
                          //���X[i]�A�N��[�J�l���XY[]�A�A���j
    Y[t] = X[i];                    
    ps(X, Y, i + 1, n, t + 1);     
}

int main() {
    int n;
    cout << "�п�J�X�Ӽ� : ";
    cin >> n;//��J���X�j�p
    string* X = new string[n];
    string* Y = new string[n];
    cout << "��J�n�����X���� : ";
    for (int i = 0; i < n; i++) {
        cin >> X[i];
    }
    cout << "���X�������O:" << endl;
    ps(X, Y, 0, n, 0);
    
    delete[] X; //�M���ʺA�t�m���O����
    delete[] Y;

    return 0;
}
