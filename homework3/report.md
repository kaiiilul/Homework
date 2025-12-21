# 41343140

作業三
# 問題一
## 解題說明
## 開發一個 C++ 類別 Polynomial,這個是用來表示和操作具有整數係數的單變數多項式 (使用帶有頭節點的圓形鏈結串列)

多項式的每一項將以一個節點表示。因此,系統中的每個節點將包含以下三個資料成員:

Polynomial 類別代表多項式,它需要有適當的成員來儲存多項式的係數與指數。

每個多項式將被表示為一個帶有頭節點的圓形鏈結串列。為了高效地刪除多項式,我們需要使用一個可用空間列表及其相關的功能。單變數多項式的外部(舉個例子像是輸入或輸出)表示形式假設為以下整數序列的格式:

## n,c1,e1,c2,e2,c3,e3,...,cn,en

en:代表的是指數

cn:代表的是係數

n:代表的是多項式的項數

### 設計的目標

#### 1.多項式的表示：

    A.使用帶有頭節點的圓形連結串列來表示多項式，每個節點包含以下資料成員：

        (a).係數，也就是coef，所代表的是每項的係數。

        (b).指數，也就是exp，代表的是每一項的指數。

        (c).連結指標，也就是link，用來指向下一個節點。

#### 2.支持高效的操作：

    A.多項式的刪除操作應該要高效，並且使用可用空間列表來管理內存。

#### 3.輸入和輸出的數據格式：

    A.整數序列的格式。

    B.指數e1->e2->en 需要按照降序排列。

### 所需要設計的東西

#### 1.資料結構設計：

    節點結構(Node):其中包含係數、指數、和指向下一節點的指標。

    多項式類別(Polynomial):其中包含操作多項式的方法及鏈結串列的管理。

#### 2.必需功能的實現：

    插入多項式項(AddTerm):

        按指數降序插入新項。

        如果存在相同指數的項,合併其係數。

        如果合併後係數為0,則刪除此項。

    刪除多項式(Clear):

        刪除多項式中的所有項,釋放鏈結串列所佔內存。

#### 3.輸入與輸出：

    輸入多項式: 重載>> 運算子,將輸入格式轉換為鏈結串列。
    
    輸出多項式: 重載<<運算子,將鏈結串列轉換為外部表示形式。

    #### 1.資料結構設計：

    節點結構(Node):其中包含係數、指數、和指向下一節點的指標。

    多項式類別(Polynomial):其中包含操作多項式的方法及鏈結串列的管理。

#### 4.多項式運算：

    加法(+): 計算兩個多項式的和。

    減法(-): 計算兩個多項式的差。

    乘法(*): 計算兩個多項式的積。

#### 5.多項式評估：

    Evaluate(x):輸入變數的值,計算多項式在X處的值。

#### 6.內存管理：

    複製建構子: 複製多項式物件的內容。

    解構子: 釋放多項式的內存。

    賦值運算子重載: 支援多項式的賦值操作。

要完成這份作業,我們需要實現一個Polynomial 類別,並提供多項式的輸入、輸出和基本運算功能(如加法、減法等)。

## 程式實作

以下為hw3 Polynomial主要程式碼：

```cpp
#include <iostream>
#include <cmath>
using namespace std;

struct Node {
    int coef; // 系數
    int exp;  // 指數
    Node* link; // 指向下一個節點的指標
};

class Polynomial {
private:
    Node* head; // 頭節點

public:
    // 預設建構子
    Polynomial() {
        head = new Node{ 0, 0, nullptr };
        head->link = head; // 圓形鏈結
    }

    // 複製建構子
    Polynomial(const Polynomial& a) {
        head = new Node{ 0, 0, nullptr };
        head->link = head;
        Node* temp = a.head->link;
        while (temp != a.head) {
            addTerm(temp->coef, temp->exp);
            temp = temp->link;
        }
    }

    // 解構子
    ~Polynomial() {
        clear();
        delete head;
    }

    // 清除鏈結串列
    void clear() {
        Node* temp = head->link;
        while (temp != head) {
            Node* del = temp;
            temp = temp->link;
            delete del;
        }
        head->link = head;
    }

    // 插入多項式項
    void addTerm(int coef, int exp) {
        Node* prev = head;
        Node* curr = head->link;
        while (curr != head && curr->exp > exp) {
            prev = curr;
            curr = curr->link;
        }
        if (curr != head && curr->exp == exp) {
            curr->coef += coef; // 合併同類項
            if (curr->coef == 0) {
                prev->link = curr->link;
                delete curr;
            }
        }
        else {
            Node* newNode = new Node{ coef, exp, curr };
            prev->link = newNode;
        }
    }

    // 輸入運算子重載
    friend std::istream& operator>>(std::istream& is, Polynomial& x) {
        int n, coef, exp;
        is >> n;
        for (int i = 0; i < n; ++i) {
            is >> coef >> exp;
            x.addTerm(coef, exp);
        }
        return is;
    }

    // 輸出運算子重載
    friend std::ostream& operator<<(std::ostream& os, const Polynomial& x) {
        Node* temp = x.head->link;
        while (temp != x.head) {
            if (temp != x.head->link && temp->coef > 0) os << " + ";
            os << temp->coef << "x^" << temp->exp;
            temp = temp->link;
        }
        return os;
    }

    // 加法運算子重載
    Polynomial operator+(const Polynomial& b) const {
        Polynomial result;
        Node* p1 = head->link;
        Node* p2 = b.head->link;
        while (p1 != head || p2 != b.head) {
            if (p1 == head) {
                result.addTerm(p2->coef, p2->exp);
                p2 = p2->link;
            }
            else if (p2 == b.head || p1->exp > p2->exp) {
                result.addTerm(p1->coef, p1->exp);
                p1 = p1->link;
            }
            else if (p1->exp < p2->exp) {
                result.addTerm(p2->coef, p2->exp);
                p2 = p2->link;
            }
            else {
                result.addTerm(p1->coef + p2->coef, p1->exp);
                p1 = p1->link;
                p2 = p2->link;
            }
        }
        return result;
    }

    // 減法運算子重載
    Polynomial operator-(const Polynomial& b) const {
        Polynomial result;
        Node* temp = b.head->link;
        while (temp != b.head) {
            result.addTerm(-temp->coef, temp->exp);
            temp = temp->link;
        }
        return *this + result;
    }

    // 乘法運算子重載
    Polynomial operator*(const Polynomial& b) const {
        Polynomial result;
        Node* temp1 = head->link;
        while (temp1 != head) {
            Node* temp2 = b.head->link;
            while (temp2 != b.head) {
                result.addTerm(temp1->coef * temp2->coef, temp1->exp + temp2->exp);
                temp2 = temp2->link;
            }
            temp1 = temp1->link;
        }
        return result;
    }

    // 賦值運算子重載
    Polynomial& operator=(const Polynomial& a) {
        if (this != &a) {
            clear();
            Node* temp = a.head->link;
            while (temp != a.head) {
                addTerm(temp->coef, temp->exp);
                temp = temp->link;
            }
        }
        return *this;
    }

    // 多項式計算
    float Evaluate(float x) const {
        float result = 0;
        Node* temp = head->link;
        while (temp != head) {
            result += temp->coef * pow(x, temp->exp);
            temp = temp->link;
        }
        return result;
    }
};

int main() {
    Polynomial p1, p2;
    cout << "輸入第一個多項式 (n c1 e1 c2 e2 ...): ";
    cin >> p1;
    cout << "輸入第二個多項式 (n c1 e1 c2 e2 ...): ";
    cin >> p2;

    cout << "P1: " << p1 << endl;
    cout << "P2: " << p2 << endl;

    Polynomial sum = p1 + p2;
    cout << "P1 + P2: " << sum << endl;

    Polynomial diff = p1 - p2;
    cout << "P1 - P2: " << diff << endl;

    Polynomial prod = p1 * p2;
    cout << "P1 * P2: " << prod << endl;

    float x;
    cout << "輸入x的質來計算P1: ";
    cin >> x;
    cout << "P1(" << x << ") = " << p1.Evaluate(x) << endl;

    return 0;
}
```

## 效能分析

### 時間複雜度（輸入/輸出運算子重載）：

輸入/輸出運算子重載：O(n)

### 空間複雜度（加法）：

輸入/輸出運算子重載：O(1)

### 時間複雜度（加法）：

加法：O(n+m)，其中n和m是兩個多項式的項數。

### 空間複雜度（加法）：
加法：O(k)

### 空間複雜度（加法）：

輸入/輸出運算子重載：O(1)

### 時間複雜度（減法）：

減法：O(m(n+m))

### 時間複雜度（乘法）：
乘法：O(n²*m²)

## 測試與驗證

### 測試案例

| 測試案例 | 輸入參數P1  | 輸入參數P2 | 預計輸出 |實際輸出|輸入X|輸出P1數值|
|----------|--------------|----------|----------|----------|----------|----------|
| 測試一   |  3 4 3 -2 2 3 1     | 2 5 2 -1 0        | P1: 4x^3-2x^2 + 3x^1       |P1: 4x^3-2x^2 + 3x^1|2|30|
|    |       |        | P2: 5x^2-1x^0       |P2: 5x^2-1x^0|||
|    |      |        | P1 + P2: 4x^3 + 3x^2 + 3x^1-1x^0       |P1 + P2: 4x^3 + 3x^2 + 3x^1-1x^0|||
|    |      |         | P1 - P2: 4x^3-7x^2 + 3x^1 + 1x^0      |P1 - P2: 4x^3-7x^2 + 3x^1 + 1x^0|||
|    |      |         | P1 * P2: 20x^5-10x^4 + 11x^3 + 2x^2-3x^      |P1 * P2: 20x^5-10x^4 + 11x^3 + 2x^2-3x^|||



### 編譯與執行指令

```shell
$ g++ hw3 Polynomial.cpp -std=c++17 -o hw3 Polynomial.exe
$ .\hw3 Polynomial.exe
輸入第一個多項式 (n c1 e1 c2 e2 ...): 3 4 3 -2 2 3 1
輸入第二個多項式 (n c1 e1 c2 e2 ...): 2 5 2 -1 0
P1: 4x^3-2x^2 + 3x^1
P2: 5x^2-1x^0
P1 + P2: 4x^3 + 3x^2 + 3x^1-1x^0
P1 - P2: 4x^3-7x^2 + 3x^1 + 1x^0
P1 * P2: 20x^5-10x^4 + 11x^3 + 2x^2-3x^1
輸入x的質來計算P1: 2
P1(2) = 30
```


## 申論及開發報告

### 申論

#### 多項式與程式設計意義
多項式是數學的核心概念，也常見於計算與分析中。在程式設計上，將多項式抽象化可幫助理解資料結構與演算法，並展現設計的靈活性與抽象思維。作業是用以多項式的 ADT（抽象資料型態）與運算符多載實作為主要，來去強化寫程式的人的程式設計能力。

#### 資料抽象的實現
ADT 是設計的思維方式，主要是在強調定義操作行為而非內部細節。多項式可視為多個「項」的集合，每項包含係數與指數。實作上利用鏈結結構儲存項目，並設計插入、顯示等基本操作，使結構更清晰、易懂且易於管理。

#### 運算符多載可以讓操作更直觀
C++ 的運算符多載可重新定義運算符，使程式更具可讀性與數學直觀性。本作業實作輸入 (>>)、輸出 (<<)、加法 (+)、減法 (-) 與乘法 (*) 等多載。
例如輸入 cin >> p1 自動讀取係數與指數，cout << p1 以數學形式輸出多項式，使操作貼近數學表達。


### 開發報告
#### 設計目標

實現多項式的抽象資料型態，其中包括加法、減法、乘法，且使用C++的運算符多載，讓多項式更簡單和接近數學的表達。

#### 開發過程

首先先設計了一個Polynomial 類別來儲存多項式的每一項。

接下來做新增項目以及顯示多項式內容的功能

為了讓多項式操作更直觀，我用了運算符多載實現了加法、減法、乘法。

同時輸入和輸出也被重新定義，讓輸入輸出更符合數學的習慣。

當時在debug時有借助到chatgpt的幫忙，當時就問我說要不要加Eval這個功能，這功能能讓我們去設定x的值來去確保程式的正確性，所以就把它也加上去了。
