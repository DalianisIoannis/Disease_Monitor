#pragma once

#include "./patients.h"
#include "./disMonitor.h"
#include <stdbool.h>

typedef struct AVLNode{

    patientRecord item;

    struct AVLNode *left;
    struct AVLNode *right;

} AVLNode;

typedef AVLNode *AVLNodePtr;




typedef struct{

    AVLNodePtr root;

} AVLTree;

typedef AVLTree *AVLTreePtr;




AVLTreePtr initAVLTree();

// void emptyAVLTree(AVLTreePtr*);
void emptyAVLTree(AVLTreePtr);

void emptyAVLnodes(AVLNodePtr);

bool addAVLNode(AVLTreePtr, patientRecord);

bool compareAdd(AVLNodePtr*, AVLNodePtr*);

void printAVLTree(AVLTreePtr);

void recPrintAVLNode(AVLNodePtr, int);