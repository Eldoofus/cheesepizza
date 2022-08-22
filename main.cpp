#include <bits/stdc++.h>
#include "graph.cpp"
#include "bst.cpp"
#include "dtree.cpp"
using namespace std;

template <typename T>
constexpr auto type_name() {
  string_view name, prefix, suffix;
  name = __PRETTY_FUNCTION__;
  prefix = "constexpr auto type_name() [with T = ";
  suffix = "]";
  name.remove_prefix(prefix.size());
  name.remove_suffix(suffix.size());
  return name;
}

int v = 10, ops = 100;

int main(){
    random_device rd;
    mt19937 rng(rd());
    uniform_int_distribution<int> uni(1,3);
    uniform_int_distribution<int> rnd(0, v-1);
    vector<dynTreeNode> V;
    vector<Vertex> VV;
    unordered_set<long long> E;
    dynTreeNode* dummy;
    Graph* g = new IncList();
    for(int i=0;i<v;i++){
        V.emplace_back();
        VV.emplace_back();
        cout << VV.back().hash << " ";
        g->addVertex(VV.back());
    } cout << endl;
    int a, b;
    for(long long i : E){
        cout << i << endl;
    }
    for(int i=0;i<ops;i++){
        a = rnd(rng);
        b = rnd(rng);
        if(a == b){
            i--;
            continue;
        }
        cout << a << ' ' << b << endl;
        int c = i<0?1:uni(rng);
        switch(c){
            case 1:
                if(E.contains((((long long)a) << 32) | ((long long)b))){
                    i--;
                    continue;
                } else {
                    E.insert((((long long)a) << 32) | ((long long)b));
                    insertEdge(&V[a], &V[b]);
                    g->addEdge(*new Edge(VV[a], VV[b]));
                }
                printf("Insert Edge: %d - %d\n", a, b);
                break;
            case 2:
                if(!E.contains((((long long)a) << 32) | ((long long)b))){
                    i--;
                    continue;
                } else {
                    E.erase((((long long)a) << 32) | ((long long)b));
                    removeEdge(&V[a], &V[b], dummy);
                    g->removeEdge(*new Edge(VV[a], VV[b]));
                }
                printf("Delete Edge: %d - %d\n", a, b);
                break;
            case 3:
                printf("Query Edge: %d - %d: DTree says %s\n", a, b, isConnected(&V[a], &V[b])? "True": "False");
                printf("Query Edge: %d - %d: BFS says %s\n", a, b, g->isConnected(VV[a], VV[b])? "True": "False");
                break;
        };
    }
    return 0;
}