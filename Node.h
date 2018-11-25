//
// Created by ezgie on 18.11.2018.
//

#include <list>
#include <vector>

class Node {
public:
    int index;
    int lowlink;
    int identity;
    int sccIndex;
    int indegree;
    std::vector<Node> keysInIt;
    Node(int identity);
    Node(const Node& node);
    Node& operator=(const Node& node);
    Node(Node&& node);
    Node& operator=(Node&& node);
    bool onStack;
    bool operator==(const Node &s) const { return this->identity == s.identity; }
    ~Node();
};

