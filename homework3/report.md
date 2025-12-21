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

多項式(Polynomial)作為數學中的重要概念,常常出現在計算與分析中。而在程式設計中，將多項式抽象化並加以實作，可以幫助我們理解資料結構的核心概念。本次作業以多項式的ADT(抽象資料型態)與運算符多載為核心，實現了多項式的基本運算與評估功能,讓我在實作中收穫良多。

#### 多項式 ADT：資料抽象的實現

ADT(抽象資料型態)是一種程式設計的思維方式，強調操作的行為而非內部細節。在這次作業中，多項式被設計為由「係數」與「指數」構成的一組節點集合，並使用鏈結串列進行實現。透過這種結構，我們實現了多項式的插入(addTerm)、刪除(clear)與顯示內容(oper ator<<)等基本操作。

鏈結串列的使用，讓多項式的項目管理更加靈活。同時透過指數的降序排列，我們可以有效避免不必要的遍歷與冗餘操作，進一步提升程式的效能

#### 運算符多載：

C++的運算符多載是一項強大的功能，它允許我們重新定義運算符的行為，使程式操作更直觀。在這次作業中，我們通過運算符多載實現了輸入(>>)、輸出(<<)、加法(+)、減法(-)與乘法(*)的功能。

例如輸入多項式時，使用cin >> pl,讓程式自動處理係數與指數的輸入;而輸出時透過 cout << pl，以數學表達形式顯示多項式。這種方式不僅貼近數學表達，還讓多項式運算的程式邏輯更符合使用者的直覺需求。加上加減乘的運算符多載，程式中的多項式操作幾乎與數學公式無異，大大提升了程式的易用性和可讀性。

#### 程式設計的價值：

這次作業讓我認識到程式設計的核心價值在於，將抽象的數學概念轉化為具體的程式實現，並透過靈活的資料結構設計，將複雜的運算簡化為簡單直觀的操作。多項式ADT和運算符多載的結合，幫助我加深了對資料結構的理解。

### 開發報告
#### 設計目標

實現多項式的抽象資料型態(ADT),以便對多項式進行高效的數據管理。 支援多項式的基本運算(加法、減法、乘法)與評估功能(Eval)。 使用C++的運算符多載,讓多項式的操作更加直觀,類似數學表達式。

確保程式結構清晰、邏輯完整,並便於擴展。

#### 開發過程

1.程式架構設計
    
    我們設計了一個 Polynomial 類別,使用鏈結串列結構儲存多項式的每一項。
    
    每一個節點包含三個屬性:
    
    係數(coef): 儲存多項式的係數。
    
    指數(exp): 儲存多項式的指數。
    
    指標(link): 指向下一個節點。此外,實現了以下基礎功能:
    
    新增項目(addTerm): 支援按指數降序插入,並合併相同指數的項目。
    
    顯示多項式(operator<<): 支援多項式內容的友好輸出。

2.運算符多載

    為了讓多項式操作更加符合數學習慣,我們透過運算符多載實現了以下功能:
    
    加法(operator+): 計算兩個多項式的和。
    
    減法(operator): 計算兩個多項式的差。
    
    乘法(operator):*計算兩個多項式的積。
    
    輸入(operator>>): 讓多項式的輸入更加簡潔直觀。
    
    輸出(operator<<): 將多項式輸出為數學格式。

3.功能擴展

    在完成多項式的基本運算後,我們進一步實現了多項式評估功能:
    
    評估（浮動x）：
    
    計算多項式在指定變數x值下的結果。
    
    使用迴圈計算公式result+=coefxx exp,確保準確性與效能。

4.程式結構優化

    多項式資料結構: 使用鏈結串列結構表示多項式,支援高效的插入與刪除操作。
    
    多項式的操作: 透過運算符多載實現了輸入、輸出、加減乘運算,以及X的點值計算。
    
    程式設計風格: 每個函數的功能劃分清晰,便於維護與擴展。
