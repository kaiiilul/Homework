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
