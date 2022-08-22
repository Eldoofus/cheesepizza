#pragma once
#include<bits/stdc++.h>
using namespace std;

struct Vertex {
    int weight = 0;
    size_t hash;
    static inline mt19937 rblah;

    Vertex(){
        hash = rblah();
    }
    
    Vertex(int a) {
        hash = rblah();
        weight = a;
    }

    Vertex(const Vertex& v) {
        hash = v.hash;
        weight = v.weight;
    }

    bool operator==(const Vertex& v) const {
        return hash == v.hash && weight == v.weight;
    }
};

struct Edge {
    Vertex *u, *v;
    int weight = 0;
    bool directed = false;

    Edge(Vertex& w, Vertex& x, bool d = false){
        u = &w;
        v = &x;
        directed = d;
    }

    Edge(Vertex& w, Vertex& x, int a, bool d = false) {
        u = &w;
        v = &x;
        weight = a;
        directed = d;
    }

    Edge(const Edge& e) {
        u = e.u;
        v = e.v;
        weight = e.weight;
        directed = e.directed;
    }

    bool operator==(const Edge& e) const {
        return (u == e.u && v == e.v) || (u == e.v && v == e.u && !directed);
    }
};

namespace std {
    template <>
    struct hash<Vertex> {
        std::size_t operator()(const Vertex& k) const {
            return k.hash;
        }
    };
    template <>
    struct hash<Edge> {
        std::size_t operator()(const Edge& k) const {
            return (hash<Vertex>()(*k.u) << 16 ^ hash<Vertex>()(*k.u) >> 16) ^ (hash<Vertex>()(*k.v) << 16 ^ hash<Vertex>()(*k.v) >> 16);
        }
    };
};

struct Graph {
    unordered_set<Vertex> V;
    unordered_set<Edge> E;
    unordered_map<Vertex, int> v_;
    unordered_map<Edge, int> e_;

    virtual void addVertex(Vertex& v) {
        V.insert(v);
        v_.emplace(v, v_.size());
    }

    virtual void addEdge(Edge& e) {
        E.insert(e);
        e_.emplace(e, e_.size());
    }

    virtual void removeVertex(Vertex& v) {
        V.erase(v);
        v_.erase(v);
    }

    virtual void removeEdge(Edge& e) {
        E.erase(e);
        e_.erase(e);
    }

    virtual int getDegree(Vertex& v) = 0;

    virtual bool isAdjacent(Vertex& u, Vertex& v) = 0;

    virtual bool isConnected(Vertex& u, Vertex& v) = 0;

    virtual unordered_set<Edge> getNeighbours(Vertex& v) = 0;

    /// Time Complexity: O(1)
    unordered_set<Vertex> vertices() {
        return V;
    }

    /// Time Complexity: O(1)
    unordered_set<Edge> edges() {
        return E;
    }

    /// Time Complexity: O(1)
    int size() {
        return V.size();
    }

};

/// Space Complexity: O(V^2)
struct AdjMtrx : Graph {
    vector<vector<bool>> m;
    vector<Vertex> lv;
    
    /// Time Complexity: O(V)
    void addVertex(Vertex& v) override {
        Graph::addVertex(v);
        for(vector<bool> w : m) w.push_back(false);
        m.emplace_back(V.size());
        lv.push_back(v);
    }

    /// Time Complexity: O(1)
    void addEdge(Edge& e) override {
        Graph::addEdge(e);
        m[v_[*e.u]][v_[*e.v]] = true;
        if(!e.directed) m[v_[*e.u]][v_[*e.v]] = true;
    }

    /// Time Complexity: O(V)
    void removeVertex(Vertex& v) override {
        for(vector<bool> w : m) swap(w.back(), w[v_[v]]);
        swap(m[v_[v]], m.back());
        v_[lv.back()] = v_[v];
        lv[v_[lv.back()]] = lv.back();
        lv.pop_back();
        Graph::removeVertex(v);
    }

    /// Time Complexity: O(1)
    void removeEdge(Edge& e) override {
        m[v_[*e.u]][v_[*e.v]] = false;
        if(!e.directed) m[v_[*e.u]][v_[*e.v]] = false;
        Graph::removeEdge(e);
    }

    /// Time Complexity: O(V)
    int getDegree(Vertex& v) override {
        int d = 0;
        for(bool e : m[v_[v]]) d += e;
        return d;
    }

    /// Time Complexity: O(1)
    bool isAdjacent(Vertex& u, Vertex& v) override {
        return m[v_[u]][v_[v]];
    }

    /// Time Complexity: O(V)
    unordered_set<Edge> getNeighbours(Vertex& v) override {
        unordered_set<Edge> n;
        for(Vertex w : V) if(isAdjacent(v, w)) n.insert(*new Edge(v, w));
        return n;
    }
};

/// Space Complexity: O(V+E)
struct AdjList : Graph {
    vector<vector<int>> l;

    /// Time Complexity: O(1)
    void addVertex(Vertex& v) override {
        Graph::addVertex(v);
        l.emplace_back();
    }

    /// Time Complexity: O(1)
    void addEdge(Edge& e) override {
        Graph::addEdge(e);
        l[v_[*e.u]].push_back(v_[*e.v]);
        if(e.directed) l[v_[*e.v]].push_back(v_[*e.u]);
    }

    /// Time Complexity: O()
    void removeVertex(Vertex& v) override {
        for(int w : l[v_[v]])
            for(int i=0;i<l[v_[w]].size();i++)
                if(l[v_[w]][i] == v_[v]) swap(l[v_[w]][i], l[v_[w]].back());
        //l[v_[w]].pop_back();
        Graph::removeVertex(v);
    }

    /// Time Complexity: O()
    void removeEdge(Edge& e) override {
        Graph::removeEdge(e);
    }

    /// Time Complexity: O()
    int getDegree(Vertex& v) override {
    }

    /// Time Complexity: O()
    bool isAdjacent(Vertex& u, Vertex& v) override {
    }

    /// Time Complexity: O()
    unordered_set<Edge> getNeighbours(Vertex& v) override {
    }
};

/// Space Complexity: O()
struct IncMtrx : Graph {
    /// Time Complexity: O()
    void addVertex(Vertex& v) override {
        Graph::addVertex(v);
    }

    /// Time Complexity: O()
    void addEdge(Edge& e) override {
        Graph::addEdge(e);
    }

    /// Time Complexity: O()
    void removeVertex(Vertex& v) override {
        Graph::removeVertex(v);
    }

    /// Time Complexity: O()
    void removeEdge(Edge& e) override {
        Graph::removeEdge(e);
    }

    /// Time Complexity: O()
    int getDegree(Vertex& v) override {
    }

    /// Time Complexity: O()
    bool isAdjacent(Vertex& u, Vertex& v) override {
    }

    /// Time Complexity: O()
    unordered_set<Edge> getNeighbours(Vertex& v) override {
    }
};

/// Space Complexity: O(V+E)
struct IncList : Graph {
    unordered_map<Vertex, unordered_set<Edge>> l;

    /// Time Complexity: O(1)
    void addVertex(Vertex& v) override {
        Graph::addVertex(v);
        l[v];
    }

    /// Time Complexity: O(1)
    void addEdge(Edge& e) override {
        Graph::addEdge(e);
        l[*e.u].insert(e);
        if(!e.directed) l[*e.v].insert(e);
    }

    /// Time Complexity: O(deg(v))
    void removeVertex(Vertex& v) override {
        Graph::removeVertex(v);
        for(auto e : l[v]) removeEdge(e);
        l.erase(v);
    }

    /// Time Complexity: O(1)
    void removeEdge(Edge& e) override {
        Graph::removeEdge(e);
        l[*e.u].erase(e);
        if(!e.directed) l[*e.v].erase(e);
    }

    /// Time Complexity: O(1)
    int getDegree(Vertex& v) override {
        return l[v].size();
    }

    /// Time Complexity: O(1)
    bool isAdjacent(Vertex& u, Vertex& v) override {
        return l[u].contains(*new Edge(u, v));
    }

    ///Time Complexity: O(V+E)
    bool isConnected(Vertex& u, Vertex& v) override {
        //cout << "test1" << endl;
        deque<Vertex> q;
        unordered_set<Vertex> vs;
        Vertex x;
        vs.insert(u);
        q.push_back(u);
        //cout << "test2 " << u.hash << endl;
        while(!q.empty()){
            //cout << "test5" << endl;
            x = q.front();
            //cout << "test3 " << x.hash << ' ' << q.front().hash << endl;
            q.pop_front();
            if(x == v) return true;
            if(l[x].empty()) continue;
            for(Edge e : l[x]){
                //cout << "test4" << endl;
                Vertex w = *(x == *e.u? e.v : e.u);
                if(!vs.contains(w)){
                    vs.insert(w);
                    q.push_back(w);
                }
            }
        }
        return false;
    }

    /// Time Complexity: O(1)
    unordered_set<Edge> getNeighbours(Vertex& v) override {
        return l[v];
    }
};