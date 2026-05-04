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
