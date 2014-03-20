#ifndef _Node_H_
#define _Node_H_

#include <cstdlib>
#include <iostream>

#ifndef MAX
#define MAX(x, y) ((x) > (y) ? (x) : (y))
#endif

template<typename T> 
struct Node{
    T d;
    Node<T> * l;
    Node<T> * r;
    //Copy a Node<T>
    Node(Node<T> * n) : d(n->d), l(n->l), r(n->r) {}
    //Make a Node<T> with all members
    Node(T t, Node<T> * cl = NULL, Node<T> * cr = NULL) 
        : d(t), l(cl), r(cr){}
};

template<typename T, typename unaryFunc> 
void preOrder(Node<T> * root, unaryFunc f){
    if(root == NULL) return;
    f(root);
    preOrder(root->l, f);
    preOrder(root->r, f);
}

template<typename T, typename unaryFunc> 
void inOrder(Node<T> * root, unaryFunc f){
    if(root == NULL) return;
    inOrder(root->l, f);
    f(root);
    inOrder(root->r, f);
}

template<typename T, typename unaryFunc> 
void postOrder(Node<T> * root, unaryFunc f){
    if(root == NULL) return;
    postOrder(root->l, f);
    postOrder(root->r, f);
    f(root);
}

template<typename T>
void deleteTree(Node<T> * root){
    if(root == NULL) return;
    deleteTree(root->l);
    deleteTree(root->r);
    delete root;
}

template<typename T>
Node<T> * find(Node<T> * root, T val){
    if(root == NULL) return NULL;
    if(root->d == val) return root;
    if(root->d > val) return find(root->l, val);
    if(root->d < val) return find(root->r, val);
    return NULL;
}

template<typename T> 
int height(Node<T> * root){
    if(root == NULL) return 0;
    else return 1 + MAX(height(root->l), height(root->r));
}

template<typename T>
int balanceFactor(Node<T> * root){
    if(root == NULL) return 0;
    return height(root->l) - height(root->r);
}

//increase depth of left side by 1.
template<typename T>
Node<T> * rotateLeft(Node<T> * root){
    if(root == NULL) return NULL;
    Node<T> * pivot = root->r;
    if(pivot == NULL) return root; //can't rotate.
    root->r = pivot->l;
    pivot->l = root; 
    return pivot;
}

//increase depth of right side by 1.
template<typename T>
Node<T> * rotateRight(Node<T> * root){
    if(root == NULL) return NULL;
    Node<T> * pivot = root->l;
    if(pivot == NULL) return root; //can't rotate.
    root->l = pivot->r;
    pivot->r = root; 
    return pivot;
    
}

template<typename T>
Node<T> * insert(Node<T> * root, Node<T> * n){
    if(root == NULL) return n;
    if(n == NULL) return root;
    if(n->d > root->d) root->r = insert(root->r, n);
    if(n->d < root->d) root->l = insert(root->l, n);
    int bal = balanceFactor(root);
    if(bal > 1 && n->d < root->l->d) return rotateRight(root);
    if(bal < -1 && n->d > root->r->d) return rotateLeft(root);
    if(bal > 1 && n->d > root->l->d){
        root->l = rotateLeft(root->l);
        return rotateRight(root);
    }
    if(bal < -1 && n->d < root->r->d){
        root->r = rotateRight(root->r);
        return rotateLeft(root);
    }
    return root;
}

template<typename T>
void print(Node<T> * root){
    if(root == NULL) return;
    print(root->l);
    std::cout << root->d << " ";
    print(root->r);
}

template<typename T>
Node<T> * remove(Node<T> * root, T val){
    if(root == NULL) return root;
    if(val < root->d) root->l = remove(root->l, val);
    else if(val > root->d) root->r = remove(root->r, val);
    else{
        if(root->l == NULL || root->r == NULL){
            Node<T> * tmp = root->l?root->l:root->r;
            if(tmp==NULL){
                tmp = root;
                root = NULL;
            } else {
                *root = *tmp;
            }
            delete tmp;
        } else {
            Node<T> * tmp = root->r;
            while(tmp->l) tmp = tmp->l;
            root->d = tmp->d;
            root->r = remove(root->r, tmp->d);
        }
    }
    if(root == NULL) return root;
    int bal = balanceFactor(root);
    if(bal > 1 && balanceFactor(root->l) >= 0) return rotateRight(root);
    if(bal < -1 && balanceFactor(root->r) <= 0) return rotateLeft(root);
    if(bal > 1 && balanceFactor(root->l) < 0){
        root->l = rotateLeft(root->l);
        return rotateRight(root);
    }
    if(bal < -1 && balanceFactor(root->r) > 0){
        root->r = rotateRight(root->r);
        return rotateLeft(root);
    }
    return root;
}

#endif