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
        BSTNode *parent, *left, *right;
        int weight, height, color;
    } root, max, min;

    virtual void insert(T d);
    virtual void remove(T d);
    virtual BSTNode* search(T d);

    bool empty(){
        return root == NULL;
    }
    int size(){
        return root.weight - 1;
    }

    virtual void joinL(BST<T>* t);
    virtual void joinR(BST<T>* t);
    virtual void join();
    BST<T>* split(T k);
    void unify(BST<T>* t);
    void diff(BST<T>* t);
    void intersect(BST<T>* t);
    void filter(bool (*f)(T));

    void rotateL(BSTNode b);
    void rotateR(BSTNode b);
    void rotateLL(BSTNode b);
    void rotateLR(BSTNode b);
    void rotateRL(BSTNode b);
    void rotateRR(BSTNode b);
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