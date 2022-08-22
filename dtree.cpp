#pragma once
#include<bits/stdc++.h>
using namespace std;


struct dynTreeNode {
    size_t hash, size;
    dynTreeNode* parent;
    unordered_set<dynTreeNode*> children, nte;

    dynTreeNode* root(){
        dynTreeNode* n = this;
        for(;n->parent;n = n->parent);
        return n;
    }
    int depth(){
        int du;
        dynTreeNode* ru = this;
        for(du = 0;ru->parent;du++) ru = ru->parent;
        return du;
    }
};

dynTreeNode* reroot(dynTreeNode* d){
    dynTreeNode* n = d, *p = n->parent, *g;
    n->parent = nullptr;
    while(p){
        g = p->parent;
        p->parent = n;
        p->children.erase(n);
        n->children.insert(p);
        n = p;
        p = g;
    }
    while(n->parent){
        n->size = n->size - n->parent->size;
        n->parent->size = n->parent->size + n->size;
        n = n->parent;
    }
    return d;
}
dynTreeNode* link(dynTreeNode* n, dynTreeNode* d){
    n->children.insert(d);
    d->parent = n;
    dynTreeNode* m = nullptr, *j = n, *root = n->root();
    while(j){
        j->size = j->size + d->size;
        if(j->size > (root->size + d->size) && !m) m = j;
        j = j->parent;
    }
    if(m && m != root) return reroot(m);
    else return root;
}
dynTreeNode* unlink(dynTreeNode* n){
    dynTreeNode* j = n;
    while(j->parent){
        j = j->parent;
        j->size = j->size - n->size;
    }
    n->parent->children.erase(n);
    n->parent = nullptr;
    return n;
}
bool isConnected(dynTreeNode* u, dynTreeNode* v){
    dynTreeNode* n = nullptr;
    while(u->parent){
        n = u;
        u = u->parent;
    }
    if(n && n->size > u->size/2) u = reroot(n);
    n = nullptr;
    while(v->parent){
        n = v;
        v = v->parent;
    }
    if(n && n->size > v->size/2) v = reroot(n);
    return u == v;
}
dynTreeNode* insertEdge(dynTreeNode* nu, dynTreeNode* nv){
    dynTreeNode* ru = nu, *rv = nv;
    int du = ru->depth(), dv = rv->depth();
    if(isConnected(nu, nv)){
        dynTreeNode* l = du <= dv? nu : nv, *h = du <= dv? nv : nu;
        int delta = abs(du - dv);
        if(delta < 2){
            nu->nte.insert(nv);
            nv->nte.insert(nu);
            return nu->root();
        } else {
            nu = h;
            for(int x = 1; x < delta - 1; x++) nu = nu->parent;
            nu->parent->nte.insert(nu);
            nu->nte.insert(nu->parent);
            unlink(nu);
            return link(l, reroot(h));
        }
    } else {
        if(ru->size < rv->size) return link(nv, reroot(nu));
        else return link(nu, reroot(nv));
    }
}
dynTreeNode* removeEdge(dynTreeNode* u, dynTreeNode* v, dynTreeNode*& d){
    dynTreeNode* n, *root = u->root();
    if(u->parent == v || v->parent == u){
        if(u == v->parent) n = v;
        else n = u;
        n = unlink(n);
        dynTreeNode* m = nullptr, *rs = root->size > n->size? n : root, *rl = root->size > n->size? root : n;
        unordered_multimap<dynTreeNode*, dynTreeNode*> R;
        vector<dynTreeNode*> q = {rs};
        unordered_set<dynTreeNode*> st({rs});
        for(dynTreeNode* it : st){
            for(dynTreeNode* c : it->children) {
                q.push_back(c);
                st.insert(c);
                if(c->size > rs->size/2) m = c;
            }
        }
        for(dynTreeNode* s : st) for(dynTreeNode* t : s->nte) if(!st.contains(t)) R.emplace(s, t);
        if(R.empty()){
            if(m) reroot(m);
            d = rl;
            return rs;
        } else {
            int md = 2147000000;
            dynTreeNode* nrs = nullptr, *nrl = nullptr;
            for(pair<dynTreeNode*, dynTreeNode*> nr : R){
                int dd = nr.second->depth();
                if(dd < md){
                    md = dd;
                    nrs = nr.first;
                    nrl = nr.second;
                }
            }
            removeEdge(nrs, nrl, n);
            return insertEdge(nrs, nrl);
        }
    } else {
        v->nte.erase(u);
        u->nte.erase(v);
        return root;
    }
}