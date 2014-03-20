#include <cstdio>
#include "avltreenode.h"
#include <cassert>

//standard use case
Node<int> * makeTree1(){
    return new Node<int>(10, 
        new Node<int>(5, 
            new Node<int>(3, 
                NULL, 
                NULL), 
            new Node<int>(7, 
                NULL, 
                NULL)), 
        new Node<int>(15, 
            new Node<int>(13, 
                NULL, 
                NULL), 
            new Node<int>(17, 
                NULL, 
                NULL)));
}

//unbalanced to the left by -1.
Node<int> * makeTree2(){
    return new Node<int>(10, 
        new Node<int>(5, 
            NULL, 
            NULL), 
        new Node<int>(15, 
            new Node<int>(13, 
                NULL, 
                NULL), 
            new Node<int>(17, 
                NULL, 
                NULL)));
}

//unbalanced to the right by -1.
Node<int> * makeTree3(){
    return new Node<int>(10, 
        new Node<int>(5, 
            new Node<int>(3, 
                NULL, 
                NULL), 
            new Node<int>(7, 
                NULL, 
                NULL)), 
        new Node<int>(15, 
            NULL, 
            NULL));
}

//NULL tree
Node<int> * makeTree4(){
    return NULL;
}

void printNode(Node<int> * n){
    printf("%d ", n->d);
}

void TestOrders(Node<int> * tree){
    preOrder(tree, printNode);
    printf("\n");
    inOrder(tree, printNode);
    printf("\n");
    postOrder(tree, printNode);
    printf("\n");
}

void TestRotations(Node<int> * root){
    inOrder(root, printNode);
    printf(": balanceFactor: %d\n", balanceFactor(root));
    root = rotateLeft(root);
    inOrder(root, printNode);
    printf(": balanceFactor: %d\n", balanceFactor(root));
    root = rotateLeft(root);
    inOrder(root, printNode);
    printf(": balanceFactor: %d\n", balanceFactor(root));
    root = rotateRight(root);
    inOrder(root, printNode);
    printf(": balanceFactor: %d\n", balanceFactor(root));
    root = rotateRight(root);
    inOrder(root, printNode);
    printf(": balanceFactor: %d\n", balanceFactor(root));
    root = rotateRight(root);
    inOrder(root, printNode);
    printf(": balanceFactor: %d\n", balanceFactor(root));
    root = rotateRight(root);
    inOrder(root, printNode);
    printf(": balanceFactor: %d\n", balanceFactor(root));
}

#define TREE(i) makeTree ## i()

int main(){
    //Test inOrder, preOrder and postOrder
    printf("Testing orders for tree 1\n");
    TestOrders(TREE(1));
    printf("Testing orders for tree 2\n");
    TestOrders(TREE(2));
    printf("Testing orders for tree 3\n");
    TestOrders(TREE(3));
    printf("Testing orders for tree 4\n");
    TestOrders(TREE(4));
    //test find
    assert(find(TREE(1), 5)->d == 5);
    assert(find(TREE(4), 0) == NULL);
    assert(find(TREE(2), 10)->d == 10);
    assert(find(TREE(3), 100) == NULL);
    //test height:
    assert(height(TREE(1)) == 3);
    assert(height(TREE(3)) == 3);
    assert(height(TREE(4)) == 0);
    assert(height(TREE(3)) == 3);
    //test balanceFactor
    assert(balanceFactor(TREE(1)) == 0);
    assert(balanceFactor(TREE(2)) == -1);
    assert(balanceFactor(TREE(3)) == 1);
    assert(balanceFactor(TREE(4)) == 0);
    //test rotateLeft and rotateRight
    printf("Testing rotations for tree 1\n");
    TestRotations(TREE(1));
    printf("Testing rotations for tree 2\n");
    TestRotations(TREE(2));
    printf("Testing rotations for tree 3\n");
    TestRotations(TREE(3));
    printf("Testing rotations for tree 4\n");
    TestRotations(TREE(4));
    //test insert
    Node<int> * root = new Node<int>(0);
    TestOrders(root);
    for(int i = 1; i < 16; i++){
        root = insert(root, new Node<int>(i));
        preOrder(root, printNode);
        printf(": %d\n", height(root));
    }
    //test remove
    for(int i = 0; i < 16; i++){
        root = remove(root, i);
        preOrder(root, printNode);
        printf(": %d\n", height(root));
    }
}