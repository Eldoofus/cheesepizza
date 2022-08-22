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

int v = 10000, ops = 130000;

int main(){
    ofstream oo("out.txt"), ii("in.txt");
    ii << v << ' ' << ops << endl;
    random_device rd;
    int rr = rd();
    mt19937 rng(rd());
    uniform_int_distribution<int> uni(1, 3);
    uniform_int_distribution<int> rnd(0, v-1);
    vector<dynTreeNode> V;
    vector<Vertex> VV;
    unordered_set<long long> E;
    dynTreeNode* dummy;
    Graph* g = new IncList();
    for(int i=0;i<v;i++){
        V.emplace_back(i);
        VV.emplace_back(i);
        //cout << VV.back().hash << " ";
        g->addVertex(VV.back());
    } //cout << endl;
    vector<int> falses;
    int a, b;
    int cc = 3;
    for(int i=0;i<ops;i++){
        a = rnd(rng);
        b = rnd(rng);
        if(a == b){
            i--;
            continue;
        }
        //cout << a << ' ' << b << endl;
        int c = i<100000?uni(rng):3;
        switch(c){
            case 1:
                if(E.contains((((long long)a) << 32) | ((long long)b))){
                    i--;
                    continue;
                } else {
                    //cout << "-----------------------------------\n";
                    ii << "I " << a << ' ' << b << endl;
                    //printf("%d. Insert Edge: %d - %d\n", i+1, a, b);
                    E.insert((((long long)a) << 32) | ((long long)b));
                    E.insert((((long long)b) << 32) | ((long long)a));
                    //insertEdge(&V[a], &V[b]);
                    g->addEdge(*new Edge(VV[a], VV[b]));
                    // for(auto d : V){
                    //     //d.print();
                    // }
                }
                break;
            case 2:
                if(!E.contains((((long long)a) << 32) | ((long long)b))){
                    i--;
                    continue;
                } else {
                    //cout << "-----------------------------------\n";
                    ii << "D " << a << ' ' << b << endl;
                    //printf("%d. Delete Edge: %d - %d\n", i+1, a, b);
                    E.erase((((long long)a) << 32) | ((long long)b));
                    E.erase((((long long)b) << 32) | ((long long)a));
                    //removeEdge(&V[a], &V[b], dummy);
                    // for(auto d : V){
                    //     //d.print();
                    // }
                    g->removeEdge(*new Edge(VV[a], VV[b]));
                }
                break;
            case 3:
                //if(cc != 3) cout << "-----------------------------------\n";
                //bool success1 = isConnected(&V[a], &V[b]);
                bool success2 = g->isConnected(VV[a], VV[b]);
                ii << "Q " << a << ' ' << b << endl;
                oo << (success2? "True": "False") << endl;
                //if(success1 != success2) falses.push_back(i+1);
                //printf("%d. Query Edge: %d - %d: BFS says %s, DTree says %s\n", i+1, a, b, success2? "True": "False", success1? "True": "False");
                break;
        };
        cc = c;
        if(i%1000==999){// for(auto d : V){
            cout << (i+1)/1000 << endl;//d.print();
        }
    }
    // for(auto i : falses){
    //     //printf("%d ", i);
    // } //cout << endl;
    // int m[100][100];
    // for(int i=0;i<v;i++){
    //     for(int j=0;j<v;j++){
    //         m[i][j] = isAdjacent(&V[i], &V[j]);
    //     }
    // }
    // for(int i=0;i<v;i++){
    //     //cout << m[i][0];
    //     for(int j=1;j<v;j++){
    //         //cout << ", " << m[i][j];
    //     } //cout << endl;
    // }
    //cout << endl << rr;
    return 0;
}