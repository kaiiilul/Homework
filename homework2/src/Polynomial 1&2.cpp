#include <iostream>
#include <cmath> // 為了使用 pow 函數計算冪次
using namespace std;

// 定義 Polynomial 類別


class Polynomial {
private:
    struct Term {
        int coefficient; // 係數
        int exponent;    // 指數
    };

    Term terms[100]; // 使用靜態陣列存儲最多 100 項
    int termCount;   // 當前項目數量

public:
    // Constructor
    Polynomial() : termCount(0) {}

    // 添加項目
    void addTerm(int coeff, int exp) {
        if (termCount < 100) { // 確保不超出陣列大小
            terms[termCount].coefficient = coeff;
            terms[termCount].exponent = exp;
            termCount++;
        }
        else {
            cout << "超出多項式最大項數限制！" << endl;
        }
    }

    // 重載輸入運算符 >>
    friend istream& operator>>(istream& in, Polynomial& poly) {
        int coeff, exp;
        cout << "輸入一個項目 (係數 指數)，輸入 -1 -1 結束: \n";
        while (true) {
            in >> coeff >> exp;
            if (coeff == -1 && exp == -1) break;
            poly.addTerm(coeff, exp);
        }
        return in;
    }

    // 重載輸出運算符 <<
    friend ostream& operator<<(ostream& out, const Polynomial& poly) {
        out << "Polynomial Details:\n";
        for (int i = 0; i < poly.termCount; ++i) {
            out << "  Term " << i + 1 << ":\n";
            out << "    Coefficient: " << poly.terms[i].coefficient << "\n";
            out << "    Exponent: " << poly.terms[i].exponent << "\n";
        }
        return out;
    }

    // 加法運算符重載
    Polynomial operator+(const Polynomial& other) const {
        return addOrSubtract(other, true); // 呼叫共用函式
    }

    // 減法運算符重載
    Polynomial operator-(const Polynomial& other) const {
        return addOrSubtract(other, false); // 呼叫共用函式
    }

    // 乘法運算符重載
    Polynomial operator*(const Polynomial& other) const {
        Polynomial result;

        // 逐項相乘
        for (int i = 0; i < termCount; ++i) {
            for (int j = 0; j < other.termCount; ++j) {
                int newCoeff = terms[i].coefficient * other.terms[j].coefficient;
                int newExp = terms[i].exponent + other.terms[j].exponent;

                // 合併相同指數的項
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

    // 評估多項式在點 f 的值
    float Eval(float f) const {
        float result = 0.0;
        for (int i = 0; i < termCount; ++i) {
            result += terms[i].coefficient * pow(f, terms[i].exponent); // a_i * f^e_i
        }
        return result;
    }

private:
    // 共用加法和減法的處理函式
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

    // 輸入兩個多項式
    cout << "輸入第一個多項式:\n";
    cin >> p1;
    cout << "輸入第二個多項式:\n";
    cin >> p2;

    // 加
    Polynomial sum = p1 + p2;
    cout << "加法結果:\n" << sum;

    // 減
    Polynomial diff = p1 - p2;
    cout << "減法結果:\n" << diff;

    // 乘
    Polynomial product = p1 * p2;
    cout << "乘法結果:\n" << product;

    // 讓使用者輸入評估點
    float f;
    cout << "輸入評估點 x 的值: ";
    cin >> f;

    // 評估
    cout << "第一個多項式在 x = " << f << " 的值為: " << p1.Eval(f) << endl;
    cout << "第二個多項式在 x = " << f << " 的值為: " << p2.Eval(f) << endl;

    return 0;
}
