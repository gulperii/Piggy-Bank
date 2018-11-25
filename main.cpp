#include <string>
#include <sstream>
#include <regex>
#include <fstream>
#include <iostream>
#include "Node.h"

using namespace std;

template<class Container>
void split(const string &str, Container &cont) {
    istringstream iss(str);
    copy(istream_iterator<string>(iss), istream_iterator<string>(), back_inserter(cont));
}


void strongConnect(vector<Node> &piggyBanks, Node &node, int index, stack<int> &stack, ofstream &myfile,
                   vector<vector<Node>> &sccs, vector<vector<int>> &sccsWithIdentities) {
    vector<Node> sccItem;
    vector<int> sccWithIdentities;
    node.index = index;
    node.lowlink = index;
    index++;
    stack.push(node.identity);
    node.onStack = true;
    int numKeys = node.keysInIt.size();
    for (int b = 0; b < numKeys; b++) {
        int indexOfSucessor = node.keysInIt.at(b).identity;
        Node &successor = piggyBanks.at(indexOfSucessor - 1);
        if (successor.index == -1) {
            strongConnect(piggyBanks, successor, index, stack, myfile, sccs, sccsWithIdentities);
            node.lowlink = min(node.lowlink, successor.lowlink);
        } else if (successor.onStack) {
            node.lowlink = min(node.lowlink, successor.index);
        }
    }
    if (node.lowlink == node.index) {
        int identityOfSucessor = stack.top();
        while (node.identity != identityOfSucessor) {
            identityOfSucessor = stack.top();
            stack.pop();
            Node &item = piggyBanks.at(identityOfSucessor - 1);
            item.sccIndex = sccs.size();
            item.onStack = false;
            sccWithIdentities.push_back(item.identity);
            sccItem.push_back(item);
        }
        if (!stack.empty()) {
            identityOfSucessor = stack.top();
            stack.pop();
            Node &item = piggyBanks.at(identityOfSucessor - 1);
            item.onStack = false;
            item.sccIndex = sccs.size();
            sccWithIdentities.push_back(item.identity);
            sccItem.push_back(item);
        }
        sccs.push_back(sccItem);

    }
}

void tarjan(vector<Node> &piggyBanks, ofstream &myfile, vector<vector<Node>> &sccs,
            vector<vector<int>> &sccsWithIdentities) {
    stack<int> stack;
    for (int a = 0; a < piggyBanks.size(); a++) {
        Node &node = piggyBanks.at(a);
        if (node.index == -1)
            strongConnect(piggyBanks, node, a, stack, myfile, sccs, sccsWithIdentities);
    }
}


int main(int argc, char *argv[]) {
    vector<vector<Node>> sccs;
    vector<vector<int>> sccsWithIdentities;
    ifstream infile(argv[1]);
    string line;
    vector<string> firstLine;
    getline(infile, line);
    int numPiggyBanks = stoi(line);
    std::vector<Node> piggyBanks;

    for (int i = 0; i < numPiggyBanks; i++) {
        getline(infile, line);
        vector<string> words;
        split(line, words);
        int numKeys = stoi(words[0]);
        Node node(i + 1);
        for (int a = 1; a < numKeys + 1; a++) {
            node.keysInIt.push_back(Node(stoi(words[a])));
        }
        piggyBanks.push_back(node);
    }

    ofstream myfile;
    myfile.open(argv[2]);
    vector<int> indegreeZero;
    tarjan(piggyBanks, myfile, sccs, sccsWithIdentities);
    for (int a = 0; a < sccs.size(); a++) {
        for (int b = 0; b < sccs.at(a).size(); b++) {
            for (Node node : sccs.at(a).at(b).keysInIt) {
                if (piggyBanks.at(node.identity - 1).sccIndex != sccs.at(a).at(b).sccIndex) {
                    piggyBanks.at(node.identity - 1).indegree++;
                }
            }
        }
    }

    for (int a = 0; a < sccs.size(); a++) {
        bool zero=true;
        for (int b = 0; b < sccs.at(a).size(); b++) {
            if (piggyBanks.at(sccs.at(a).at(b).identity-1).indegree!= 0){
                zero=false;
                break;

            }
        }
        if(zero)
        indegreeZero.push_back(sccs.at(a).at(0).identity);
    }
    myfile<<indegreeZero.size()<<" ";
    for(int a =0;a<indegreeZero.size();a++){
        myfile<<indegreeZero.at(a)<<" ";
    }
}