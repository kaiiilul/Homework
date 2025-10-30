# 41343140

作業二
# 問題一
## 實作Polynomial 類別，根據問題1和問題2提供的抽象資料類別（ADT）和私有數據成員，實現一個Polynomial 類別

Polynomial 類別代表的是多項式，它需要正確的成員來儲存每個多項式的指數以及係數。

我來舉個例子：5x²+3x+1

這時候它的指數就為：［2,1,0］

而係數就為：［5,3,1］


這時候就會發現我們的設計目標就知道了

首先：運用私有的成員來儲存指數還有係數。

再來：提供接口添加、刪除又或者操作多項式的項目。

最後：只一個支援多項式的輸入以及輸出。

### 所需要設計的東西

#### 1.多項式的基本結構：

其中包含了指數和係數的儲存，以及提供給多項式輸入以及輸出的功能。

#### 2.多項式的加法功能：

要去完成兩個多項式的加法，當返回一個新的多項式時，視為一個加法結果。

#### 3.多項式的乘法功能：

要去完成兩個多項式的每一項逐項相乘，然後將最後得到的結果去整理成一個新的多項式。

#### 4.Eval 函數在給定的點x，去計算多項式的值：

這個是多項式評估的功能，通常會用在算p(x)的結果。

# 問題二
## 用C++來寫輸入以及輸出多項式，這些函數需要支持多項式的輸入以及輸出，且函數需要重載<<和>>運算符號

### 這個問題我們需要設計兩個重載運算符號：

#### 1.>>運算符號：

這個符號是作用於從輸入來讀取多項式的資料。

#### 2.<<運算符號：

這個符號是作用於輸出多項式的格式化表示。

## 程式實作

以下為Polynomial問題一&二的主要程式碼：

```cpp
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
```

## 效能分析

### 1. 時間複雜度：O(A(m, n))。
    Ackermann函數增長速度真的太快了，這導致了它的時間複雜度真的沒辦法直接計算，但如果m比較小的話那就面前還行，但只要超過4那就是十分的難以計算。

### 2. 空間複雜度：O(A(m, n))。
    而就是因為Ackermann函數有十分高的時間複雜度，而且在大數字下資源消耗也是很恐怖。
    
## 測試與驗證

### 測試案例

| 測試案例 | 輸入參數 $m,n$ | 預期輸出 | 實際輸出 |
|----------|--------------|----------|----------|
| 測試一   | $m=0, n=4$      | 5        | 5        |
| 測試二   | $m=1, n=1$      | 3        | 3        |
| 測試三   | $m=2, n=3$      | 9        | 9        |
| 測試四   | $m=3, n=2$      | 29       | 29       |

### 編譯與執行指令

```shell
$ g++ akm.cpp -std=c++17 -o akm.exe
$ .\akm.exe
輸入m和n:0 4
Ackermann(0, 4) = 5
輸入m和n:2 3
Ackermann(2, 3) = 9
```

### 結論

遞迴和非遞迴的執行結果都相同，但要注意的一個點是當m>=4時程式有可能會崩潰，所以在輸入時可能要多加注意一下。
而m>4我是真的有遇過，考試時教授說太大的要懂得跳過，小考有一題就是（6，0）那個真的完全算不出來。

## 申論及開發報告

### 選擇遞迴的原因

Ackermann函數並不是一個簡單的遞迴，因為m,n的增加會導致結果會有爆炸性的數值增加，這樣不只讓我們在計算複雜度時會十分的不順利，也很考驗我們在編寫時的管理能力。
而如果是我來寫我會使用遞迴，以下有幾個原因：


##  1.程式邏輯簡單直觀
程式邏輯很清楚，因為都只用if/else，所以很簡單就能讀得懂。

## 2.易於理解和實踐
定義即遞迴的關係，所以能清楚的觀察到呼叫過程和堆疊變化，所以也很適合用在教學上。
