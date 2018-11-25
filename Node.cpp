//
// Created by ezgie on 18.11.2018.
//

#include <regex>
#include "Node.h"
using namespace std;
Node::Node(int identity) {
    this->index = -1;
    this->lowlink = -1;
    this->identity = identity;
    this->onStack=false;
    this->sccIndex=-1;
    this->indegree=0;
}
 Node::~Node() {

}
Node::Node(const Node& node){
    this->identity = node.identity;
    this->lowlink = node.lowlink;
    this->onStack = node.onStack;
    this->index = node.index;
    this->sccIndex = node.sccIndex;
    this->indegree = node.indegree;
    this->keysInIt=node.keysInIt;
}

Node& Node::operator=(const Node& node){
    this->identity = node.identity;
    this->lowlink = node.lowlink;
    this->onStack = node.onStack;
    this->index = node.index;
    this->keysInIt=node.keysInIt;
    this->sccIndex = node.sccIndex;
    this->indegree = node.indegree;

    return *this;
}


Node::Node(Node&& node){
    this->identity = move(node.identity);
    this->lowlink= move(node.lowlink);
    this->onStack= move(node.onStack);
    this->index = move(node.index);
    this->keysInIt=move(node.keysInIt);
    this->sccIndex = move(node.sccIndex);
    this->indegree = move(node.indegree);


}

Node& Node::operator=(Node&& node){
    this->identity = move(node.identity);
    this->lowlink= move(node.lowlink);
    this->onStack= move(node.onStack);
    this->index = move(node.index);
    this->keysInIt=move(node.keysInIt);
    this->sccIndex = move(node.sccIndex);
    this->indegree = move(node.indegree);

    return *this;
}


