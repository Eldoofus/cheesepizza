#pragma once
#include<bits/stdc++.h>
using namespace std;

enum color : int {
    black,
    red,
    null = -1
};

template<typename T>
struct BST {
    struct BSTNode {
        T key;
        BSTNode *parent = nullptr, *left = nullptr, *right = nullptr;
        int weight = -1, height = -2, color = -1;

        BSTNode* setLeft(BSTNode* l){
            if(left) left->parent = nullptr;
            left = l;
            if(!l) return this;
            if(l->parent) l->parent->left = nullptr;
            l->parent = this;
            return this;
        }
        BSTNode* setRight(BSTNode* r){
            if(right) right->parent = nullptr;
            right = r;
            if(!r) return this;
            if(r->parent) r->parent->right = nullptr;
            r->parent = this;
            return this;
        }
        bool isRoot(){
            return !parent;
        }
        bool isLeft(){
            return !isRoot() && parent->left == this;
        }
        bool isRight(){
            return !isRoot() && parent->right == this;
        }
        BSTNode* update(){
            weight = (left? left->weight - 1 : 0) + (right? right->weight - 1 : 0) + 2;
            height = height < 0? -1 : std::max(left? left->height : -1, right? right->height : -1) + 1;
        }
        BSTNode* pred(){
            BSTNode* r;
            if(left) for(r=left;r->right;r=r->right);
            return r;
            for(r=this;r->isRight();r=r->parent);
            return r->parent;
        }
        BSTNode* succ(){
            BSTNode* r;
            if(right) for(r=right;r->left;r=r->left);
            return r;
            for(r=this;r->isLeft();r=r->parent);
            return r->parent;
        }
        BSTNode* sibling(){
            if(isRoot()) return nullptr;
            if(isLeft()) return parent->right;
            if(isRight()) return parent->left;
        }
    } *root, *max, *min;

    BSTNode* replace(BSTNode* b, BSTNode* a){
        if(b->isRoot()) root = a;
        if(b->isLeft()) b->parent->setLeft(a);
        if(b->isRight()) b->parent->setRight(a);
        return b;
    }

    virtual BSTNode* insert(T d){
        if(!root) return root = new BSTNode{d};
        BSTNode* b = root;
        while(d != b->key){
            if(d < b->key){
                if(b->left) b = b->left;
                else b = b->setLeft(new BSTNode{d})->left;
            } else {
                if(b->right) b = b->right;
                else b = b->setRight(new BSTNode{d})->right;
            }
        }
        if(b->key < min->key) return min = b;
        if(b->key > max->key) return max = b;
        return b;
        
    }
    virtual BSTNode* remove(T d){
        BSTNode* b = root;
        while(b && d != b->key){
            if(d < b->key) b = b->left;
            else b = b->right;
        }
        if(!b) return nullptr;
        if(!b->left && !b->right) return nullptr;
        if(!b->right) return nullptr;
        if(!b->left) return nullptr;
        
    }
    BSTNode* search(T d){
        BSTNode* b = root;
        while(b && d != b->key){
            if(d < b->key) b = b->left;
            else b = b->right;
        }
        return b;
    }

    bool empty(){
        return !root;
    }
    int size(){
        return root->weight - 1;
    }

    virtual BST<T>* join(T k, BST<T>* t){
        if(max->key < k && k < t->min->key){
            
        } else if(t->max->key < k && k < min->key){
            
        }
        return this;
    }
    void join(BST<T>* t);
    BST<T>* split(T k);
    void unify(BST<T>* t);
    void diff(BST<T>* t);
    void intersect(BST<T>* t);
    void filter(bool (*f)(T));

    void rotateL(BSTNode* b){
        if(!b->isRight()) return;
        replace(b->parent, b->setLeft(b->parent->setRight(b->left)));
        b->left->update()->parent->update();
    }
    void rotateR(BSTNode* b){
        if(!b->isLeft()) return;
        replace(b->parent, b->setRight(b->parent->setLeft(b->right)));
        b->left->update()->parent->update();
    }
    void rotateLL(BSTNode* b){
        if(!b->isRight() && !b->parent->isRight()) return;
        replace(b->parent, b->setRight(b->parent->parent->setLeft(b->setRight(b->parent->setLeft(b->right))->right)));
        b->right->right->update()->parent->update()->parent->update();
    }
    void rotateLR(BSTNode* b){
        if(!b->isRight() && !b->parent->isLeft()) return;
        if(b->parent->parent->isRoot()) b->setRight(b->parent->parent->setLeft(b->setLeft(b->parent->setRight(b->right))->right));
        if(b->parent->parent->isLeft()) b->parent->parent->parent->setLeft(b->setRight(b->parent->parent->setLeft(b->setLeft(b->parent->setRight(b->left))->right)));
        if(b->parent->parent->isRight()) b->parent->parent->parent->setRight(b->setRight(b->parent->parent->setLeft(b->setLeft(b->parent->setRight(b->left))->right)));
        b->right->update()->parent->left->update()->parent->update();
    }
    void rotateRL(BSTNode* b){
        if(!b->isLeft() && !b->parent->isRight()) return;
        if(b->parent->parent->isRoot()) b->setLeft(b->parent->parent->setRight(b->setRight(b->parent->setLeft(b->right))->left));
        if(b->parent->parent->isLeft()) b->parent->parent->parent->setLeft(b->setLeft(b->parent->parent->setRight(b->setRight(b->parent->setLeft(b->right))->left)));
        if(b->parent->parent->isRight()) b->parent->parent->parent->setRight(b->setLeft(b->parent->parent->setRight(b->setRight(b->parent->setLeft(b->right))->left)));
        b->left->update()->parent->right->update()->parent->update();
    }
    void rotateRR(BSTNode* b){
        if(!b->isLeft() && !b->parent->isLeft()) return;
        if(b->parent->parent->isRoot()) b->setLeft(b->parent->parent->setRight(b->setLeft(b->parent->setRight(b->left))->left));
        if(b->parent->parent->isLeft()) b->parent->parent->parent->setLeft(b->setLeft(b->parent->parent->setRight(b->setLeft(b->parent->setRight(b->left))->left)));
        if(b->parent->parent->isRight()) b->parent->parent->parent->setRight(b->setLeft(b->parent->parent->setRight(b->setLeft(b->parent->setRight(b->left))->left)));
        b->left->left->update()->parent->update()->parent->update();
    }
};

template<typename T>
struct AVL : BST<T> {
    
};

template<typename T>
struct WBT : BST<T> {
    
};

template<typename T>
struct RBT : BST<T> {
    
};