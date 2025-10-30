#include <iostream>
#include <cmath> // ���F�ϥ� pow ��ƭp�⾭��
using namespace std;

// �w�q Polynomial ���O


class Polynomial {
private:
    struct Term {
        int coefficient; // �Y��
        int exponent;    // ����
    };

    Term terms[100]; // �ϥ��R�A�}�C�s�x�̦h 100 ��
    int termCount;   // ��e���ؼƶq

public:
    // Constructor
    Polynomial() : termCount(0) {}

    // �K�[����
    void addTerm(int coeff, int exp) {
        if (termCount < 100) { // �T�O���W�X�}�C�j�p
            terms[termCount].coefficient = coeff;
            terms[termCount].exponent = exp;
            termCount++;
        }
        else {
            cout << "�W�X�h�����̤j���ƭ���I" << endl;
        }
    }

    // ������J�B��� >>
    friend istream& operator>>(istream& in, Polynomial& poly) {
        int coeff, exp;
        cout << "��J�@�Ӷ��� (�Y�� ����)�A��J -1 -1 ����: \n";
        while (true) {
            in >> coeff >> exp;
            if (coeff == -1 && exp == -1) break;
            poly.addTerm(coeff, exp);
        }
        return in;
    }

    // ������X�B��� <<
    friend ostream& operator<<(ostream& out, const Polynomial& poly) {
        out << "Polynomial Details:\n";
        for (int i = 0; i < poly.termCount; ++i) {
            out << "  Term " << i + 1 << ":\n";
            out << "    Coefficient: " << poly.terms[i].coefficient << "\n";
            out << "    Exponent: " << poly.terms[i].exponent << "\n";
        }
        return out;
    }

    // �[�k�B��ŭ���
    Polynomial operator+(const Polynomial& other) const {
        return addOrSubtract(other, true); // �I�s�@�Ψ禡
    }

    // ��k�B��ŭ���
    Polynomial operator-(const Polynomial& other) const {
        return addOrSubtract(other, false); // �I�s�@�Ψ禡
    }

    // ���k�B��ŭ���
    Polynomial operator*(const Polynomial& other) const {
        Polynomial result;

        // �v���ۭ�
        for (int i = 0; i < termCount; ++i) {
            for (int j = 0; j < other.termCount; ++j) {
                int newCoeff = terms[i].coefficient * other.terms[j].coefficient;
                int newExp = terms[i].exponent + other.terms[j].exponent;

                // �X�֬ۦP���ƪ���
                bool merged = false;
                for (int k = 0; k < result.termCount; ++k) {
                    if (result.terms[k].exponent == newExp) {
                        result.terms[k].coefficient += newCoeff;
                        merged = true;
                        break;
                    }
                }
                if (!merged) result.addTerm(newCoeff, newExp);
            }
        }

        return result;
    }

    // �����h�����b�I f ����
    float Eval(float f) const {
        float result = 0.0;
        for (int i = 0; i < termCount; ++i) {
            result += terms[i].coefficient * pow(f, terms[i].exponent); // a_i * f^e_i
        }
        return result;
    }

private:
    // �@�Υ[�k�M��k���B�z�禡
    Polynomial addOrSubtract(const Polynomial& other, bool isAddition) const {
        Polynomial result;
        int i = 0, j = 0;

        while (i < termCount && j < other.termCount) {
            if (terms[i].exponent == other.terms[j].exponent) {
                int coeff = isAddition ? terms[i].coefficient + other.terms[j].coefficient
                    : terms[i].coefficient - other.terms[j].coefficient;
                if (coeff != 0) result.addTerm(coeff, terms[i].exponent);
                i++;
                j++;
            }
            else if (terms[i].exponent > other.terms[j].exponent) {
                result.addTerm(terms[i].coefficient, terms[i].exponent);
                i++;
            }
            else {
                int coeff = isAddition ? other.terms[j].coefficient : -other.terms[j].coefficient;
                result.addTerm(coeff, other.terms[j].exponent);
                j++;
            }
        }

        while (i < termCount) result.addTerm(terms[i].coefficient, terms[i].exponent), i++;
        while (j < other.termCount) {
            int coeff = isAddition ? other.terms[j].coefficient : -other.terms[j].coefficient;
            result.addTerm(coeff, other.terms[j].exponent), j++;
        }

        return result;
    }
};

int main() {
    Polynomial p1, p2;

    // ��J��Ӧh����
    cout << "��J�Ĥ@�Ӧh����:\n";
    cin >> p1;
    cout << "��J�ĤG�Ӧh����:\n";
    cin >> p2;

    // �[
    Polynomial sum = p1 + p2;
    cout << "�[�k���G:\n" << sum;

    // ��
    Polynomial diff = p1 - p2;
    cout << "��k���G:\n" << diff;

    // ��
    Polynomial product = p1 * p2;
    cout << "���k���G:\n" << product;

    // ���ϥΪ̿�J�����I
    float f;
    cout << "��J�����I x ����: ";
    cin >> f;

    // ����
    cout << "�Ĥ@�Ӧh�����b x = " << f << " ���Ȭ�: " << p1.Eval(f) << endl;
    cout << "�ĤG�Ӧh�����b x = " << f << " ���Ȭ�: " << p2.Eval(f) << endl;

    return 0;
}
