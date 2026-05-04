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
