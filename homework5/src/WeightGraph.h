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
