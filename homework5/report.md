# 41343120
# 41343140

作業2

## 解題說明

本次作業要讓我們透過實作來理解圖(Graph)的表示方式及演算法。首先，將問題建模為圖結構，並依需求選擇合適的表示方法，如鄰接矩陣或鄰接串列，以有效描述節點之間的關係。接著，實作基本圖演算法，包括深度優先搜尋（DFS）與廣度優先搜尋（BFS），以進行圖的走訪與連通性分析，並可進一步找出連通元件或建立生成樹。此外，透過最小生成樹演算法（如 Kruskal 或 Prim）解決最小成本連接問題，並利用最短路徑演算法（如 Dijkstra 或 Floyd-Warshall）計算節點間的最短距離。在進階應用方面，亦可透過拓樸排序處理具先後關係的活動網路問題。透過上述方法與演算法的整合應用，能有效掌握圖在資料結構中的核心概念與實務操作。
### 解題策略
本題先利用 物件導向設計（OOP） 建立 GraphBase 作為抽象基底類別，統一定義圖形基本功能，例如新增邊與輸出圖形，讓不同圖形結構可以透過繼承方式延伸功能，提高程式可重用性與擴充性。

接著分成兩種類型實作：

1.ListGraph 採用鄰接串列（Adjacency List）儲存無權重圖，適合處理稀疏圖，可節省空間。並透過 DFS 以遞迴方式進行深度優先搜尋，用來遍歷節點與找出連通分量；再使用 BFS 搭配 Queue 完成廣度優先搜尋，依層級順序走訪圖中的節點。

2.WeightGraph 則使用鄰接串列搭配權重資訊，處理加權圖問題。最小生成樹部分，實作 Prim 演算法，利用 Priority Queue 每次選取最小權重邊擴展生成樹；同時實作 Kruskal 演算法，先將邊依權重排序，再搭配 Disjoint Set（Union-Find） 判斷是否形成環，避免加入重複連接。

最後在最短路徑部分，使用 Dijkstra 演算法，透過 Priority Queue 持續更新起點到各節點的最短距離，求得單源最短路徑結果。

整體程式藉由將不同演算法模組化，分別展示圖形遍歷、連通分量判斷、最小生成樹與最短路徑等核心圖論功能。

## 程式實作

GraphBase.h
```cpp
#pragma once
#include <iostream>
using namespace std;

class GraphBase {
protected:
    int vertexCount;

public:
    GraphBase(int n) : vertexCount(n) {}
    virtual ~GraphBase() {}

    virtual void addConnection(int a, int b) = 0;
    virtual void printGraph() = 0;
};
```

ListGraph.h
```cpp
#pragma once
#include "GraphBase.h"
#include <vector>
#include <queue>

class ListGraph : public GraphBase {
private:
    vector<vector<int> > graphData;

    void explore(int node, vector<bool>& seen) {
        seen[node] = true;
        cout << node << " ";

        for (int next : graphData[node]) {
            if (!seen[next]) {
                explore(next, seen);
            }
        }
    }

public:
    ListGraph(int n) : GraphBase(n) {
        graphData.resize(n);
    }

    void addConnection(int a, int b) override {
        graphData[a].push_back(b);
        graphData[b].push_back(a);
    }

    void printGraph() override {
        for (int i = 0; i < vertexCount; i++) {
            cout << i << " -> ";
            for (int j : graphData[i]) {
                cout << j << " ";
            }
            cout << endl;
        }
    }

    void runDFS(int start) {
        vector<bool> seen(vertexCount, false);
        cout << "DFS order: ";
        explore(start, seen);
        cout << endl;
    }

    void runBFS(int start) {
        vector<bool> seen(vertexCount, false);
        queue<int> q;

        q.push(start);
        seen[start] = true;

        cout << "BFS order: ";

        while (!q.empty()) {
            int cur = q.front();
            q.pop();

            cout << cur << " ";

            for (int next : graphData[cur]) {
                if (!seen[next]) {
                    seen[next] = true;
                    q.push(next);
                }
            }
        }
        cout << endl;
    }

    void countGroups() {
        vector<bool> seen(vertexCount, false);
        int groupID = 0;

        for (int i = 0; i < vertexCount; i++) {
            if (!seen[i]) {
                cout << "Group " << ++groupID << ": ";
                explore(i, seen);
                cout << endl;
            }
        }
    }
};
```
WeightGraph.h
```cpp
#pragma once
#include "GraphBase.h"
#include <vector>
#include <queue>
#include <algorithm>
#include <climits>

class UnionFind {
private:
    vector<int> root;
    vector<int> depth;

public:
    UnionFind(int n) {
        root.resize(n);
        depth.resize(n, 0);
        for (int i = 0; i < n; i++) {
            root[i] = i;
        }
    }

    int findRoot(int x) {
        if (root[x] != x) {
            root[x] = findRoot(root[x]);
        }
        return root[x];
    }

    void merge(int a, int b) {
        int ra = findRoot(a);
        int rb = findRoot(b);

        if (ra == rb) return;

        if (depth[ra] < depth[rb]) {
            root[ra] = rb;
        }
        else if (depth[ra] > depth[rb]) {
            root[rb] = ra;
        }
        else {
            root[rb] = ra;
            depth[ra]++;
        }
    }
};

class WeightGraph : public GraphBase {
private:
    struct Link {
        int from;
        int to;
        int cost;
    };

    vector<vector<pair<int, int>>> data;
    vector<Link> linkList;

public:
    WeightGraph(int n) : GraphBase(n) {
        data.resize(n);
    }

    void addConnection(int a, int b, int w) {
        data[a].push_back(pair<int, int>(b, w));
        data[b].push_back(pair<int, int>(a, w));
        linkList.push_back(Link{ a, b, w });
    }

    void addConnection(int a, int b) override {
        addConnection(a, b, 1);
    }

    void printGraph() override {
        for (int i = 0; i < vertexCount; i++) {
            cout << i << " -> ";
            for (size_t j = 0; j < data[i].size(); j++) {
                cout << "("
                    << data[i][j].first << ","
                    << data[i][j].second << ") ";
            }
            cout << endl;
        }
    }

    void primMST(int start) {
        vector<int> best(vertexCount, INT_MAX);
        vector<int> parent(vertexCount, -1);
        vector<bool> used(vertexCount, false);

        priority_queue<
            pair<int, int>,
            vector<pair<int, int>>,
            greater<pair<int, int>>
        > pq;

        pq.push(pair<int, int>(0, start));
        best[start] = 0;

        while (!pq.empty()) {
            int u = pq.top().second;
            pq.pop();

            if (used[u]) continue;
            used[u] = true;

            for (size_t i = 0; i < data[u].size(); i++) {
                int v = data[u][i].first;
                int w = data[u][i].second;

                if (!used[v] && w < best[v]) {
                    best[v] = w;
                    parent[v] = u;
                    pq.push(pair<int, int>(w, v));
                }
            }
        }

        cout << "Prim MST:\n";
        long long total = 0;

        for (int i = 0; i < vertexCount; i++) {
            if (parent[i] != -1) {
                cout << parent[i] << " - " << i
                    << " : " << best[i] << endl;
                total += best[i];
            }
        }
        cout << "Total = " << total << endl;
    }

    void kruskalMST() {
        sort(linkList.begin(), linkList.end(),
            [](const Link& a, const Link& b) {
                return a.cost < b.cost;
            });

        UnionFind uf(vertexCount);
        long long total = 0;

        cout << "Kruskal MST:\n";

        for (size_t i = 0; i < linkList.size(); i++) {
            Link e = linkList[i];

            if (uf.findRoot(e.from) != uf.findRoot(e.to)) {
                uf.merge(e.from, e.to);
                cout << e.from << " - " << e.to
                    << " : " << e.cost << endl;
                total += e.cost;
            }
        }
        cout << "Total = " << total << endl;
    }

    void shortestPath(int start) {
        vector<int> dist(vertexCount, INT_MAX);

        priority_queue<
            pair<int, int>,
            vector<pair<int, int>>,
            greater<pair<int, int>>
        > pq;

        dist[start] = 0;
        pq.push(pair<int, int>(0, start));

        while (!pq.empty()) {
            int d = pq.top().first;
            int u = pq.top().second;
            pq.pop();

            if (d > dist[u]) continue;

            for (size_t i = 0; i < data[u].size(); i++) {
                int v = data[u][i].first;
                int w = data[u][i].second;

                if (dist[v] > dist[u] + w) {
                    dist[v] = dist[u] + w;
                    pq.push(pair<int, int>(dist[v], v));
                }
            }
        }

        cout << "Shortest paths from " << start << ":\n";
        for (int i = 0; i < vertexCount; i++) {
            cout << "to " << i << " = ";
            if (dist[i] == INT_MAX) cout << "INF\n";
            else cout << dist[i] << endl;
        }
    }
};
```
main.cpp
```cpp
#include <iostream>
#include "ListGraph.h"
#include "WeightGraph.h"
using namespace std;

int main() {
    cout << "=== ListGraph Demo ===\n";

    ListGraph g1(6);
    g1.addConnection(0, 1);
    g1.addConnection(0, 2);
    g1.addConnection(3, 4);
    g1.addConnection(4, 5);

    g1.printGraph();
    g1.runDFS(0);
    g1.runBFS(0);
    g1.countGroups();

    cout << "\n=== WeightGraph Demo ===\n";

    WeightGraph g2(5);
    g2.addConnection(0, 1, 5);
    g2.addConnection(0, 2, 8);
    g2.addConnection(1, 2, 2);
    g2.addConnection(1, 3, 7);
    g2.addConnection(2, 4, 3);
    g2.addConnection(3, 4, 6);
    g2.printGraph();
    cout << endl;

    g2.primMST(0);
    cout << endl;
    g2.kruskalMST();
    cout << endl;
    g2.shortestPath(0);

    return 0;
}
```

## 效能分析
1. ListGraph（鄰接串列）
   
   (1) addConnection(a, b)
   
   時間複雜度： O(1)（均攤）
   
   空間影響： 每條邊儲存兩次（無向圖）→ O(V + E)

   (2) printGraph()
   
   時間複雜度： O(V + E)
   
   空間複雜度： O(1)

   (3) runDFS(start)
   
   本質為 DFS（遞迴）
   
   時間複雜度： O(V + E)
   
   空間複雜度：visited 陣列：O(V)
   
   遞迴堆疊：最壞 O(V)
   
   (4) runBFS(start)
   
   使用 queue

   時間複雜度： O(V + E)

   空間複雜度：queue：O(V)

   visited：O(V)
           
   (5) countGroups()（連通元件）

   會對每個未拜訪節點呼叫 DFS

   時間複雜度： O(V + E)

   空間複雜度： O(V)

2. WeightGraph（加權圖）
   
   (1) addConnection(a, b, w)

   時間複雜度： O(1)

   空間複雜度： O(E)

   (2) printGraph()

   時間複雜度： O(V + E)

   最小生成樹（MST）

   (3) primMST(start)

   使用 priority queue（min-heap）

   時間複雜度：

   O((V + E) log V)

   空間複雜度：

   heap：O(V)

   陣列：O(V)

   (4) kruskalMST()

   排序 + Union-Find

   時間複雜度：

   排序：O(E log E)

   Union-Find：近似 O(E α(V))

   總體：O(E log E)

   空間複雜度：

   邊列表：O(E)

   Union-Find：O(V)

   最短路徑
 
   (5) shortestPath(start)（Dijkstra）

   使用 priority queue

   時間複雜度：
 
   O((V + E) log V)

   空間複雜度：

   dist：O(V)

   heap：O(V)


## 測試與驗證
| 測試案例 | 輸入參數 |
|----------|--------------|
| 測試一 | ListGraph g1(6);|
|   | g1.addConnection(0, 1);|
|   |g1.addConnection(0, 2);|
|   |g1.addConnection(3, 4);|
|   | g1.addConnection(4, 5);|
|    |WeightGraph g2(5);|
|   | g2.addConnection(0, 1, 5);|
|   | g2.addConnection(0, 2, 8);|
|   | g2.addConnection(1, 2, 2);|
|   | g2.addConnection(1, 3, 7);|
|   | g2.addConnection(2, 4, 3);|
|   | g2.addConnection(3, 4, 6);|

預計輸出

1 -> (0, 5)(2, 2)(3, 7)

2 -> (0, 8)(1, 2)(4, 3)

3 -> (1, 7)(4, 6)

4 -> (2, 3)(3, 6)

Prim MST:

0 - 1:5

1 - 2:2

4 - 3:6

2 - 4:3

Total = 16

Kruskal MST:

1 - 2:2 

2 - 4:3 

0 - 1:5

3 - 4:6

Total = 16

Shortest paths from 0:

to 0 = 0

to 1 = 5

to 2 = 7

to 3 = 12

to 4 = 10

實際輸出


1 -> (0, 5)(2, 2)(3, 7)

2 -> (0, 8)(1, 2)(4, 3)

3 -> (1, 7)(4, 6)

4 -> (2, 3)(3, 6)

Prim MST:

0 - 1:5

1 - 2:2

4 - 3:6

2 - 4:3

Total = 16

Kruskal MST:

1 - 2:2 

2 - 4:3 

0 - 1:5

3 - 4:6

Total = 16

Shortest paths from 0:

to 0 = 0

to 1 = 5

to 2 = 7

to 3 = 12

to 4 = 10


<img width="972" height="512" alt="h" src="https://github.com/user-attachments/assets/ba2bcece-558f-4598-9be3-e40bdbe5735f" />



## 結論
本作業透過實作圖（Graph）的基礎架構與多種經典演算法，深入理解圖在資料結構中的表示方式與應用。藉由鄰接串列建立無向圖，以及加權圖結構的設計，成功實現 DFS、BFS、連通元件分析、最小生成樹（Prim 與 Kruskal）與最短路徑（Dijkstra）等核心功能。從測試結果可知，各演算法皆能正確運作並符合其理論時間複雜度，顯示所設計之程式具備良好的正確性與效率。整體而言，本作業不僅強化了對圖論演算法的理解，也提升了將理論轉化為程式實作的能力。

## 申論及開發報告
1.為何 Dijkstra 不適用負權重:演算法基於「已選最短路徑不會再變」的假設且負權重可能讓已確定的最短路徑被推翻，最終會導致錯誤結果

2.為何採用「鄰接串列」而非「鄰接矩陣」:因為鄰接串列在稀疏圖下空間為 O(V+E)，比鄰接矩陣的 O(V²) 更節省記憶體且遍歷效率較高。

3.為何 DFS 使用遞迴實作:因為 DFS 的深度優先特性符合遞迴結構，可自然利用系統 stack 完成深入與回溯。

4.為何 BFS 使用 Queue:因為 BFS 需依層級進行節點擴展，而 Queue 的先進先出特性可正確實現此流程並保證最短步數搜尋。

## 分工
41343140黃鉑凱:程式實作以及測試與驗證

41343120洪辰偉:解題說明、效能分析、結論申論及開發報告
