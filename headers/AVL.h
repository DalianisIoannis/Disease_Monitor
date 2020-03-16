#pragma once

#include "./patients.h"
#include "./disMonitor.h"
#include <stdbool.h>

typedef struct AVLNode{

    patientRecord item;

    struct AVLNode *left;
    struct AVLNode *right;
    int nodeHeight; // root is height 1

} AVLNode;

typedef AVLNode *AVLNodePtr;




typedef struct{

    AVLNodePtr root;

} AVLTree;

typedef AVLTree *AVLTreePtr;




AVLTreePtr initAVLTree();

void emptyAVLTree(AVLTreePtr);

void emptyAVLnodes(AVLNodePtr);

bool addAVLNode(AVLTreePtr, patientRecord);

bool compareAdd(AVLNodePtr*, AVLNodePtr*);

void printAVLTree(AVLTreePtr);

void recPrintAVLNode(AVLNodePtr, int);

void performRotations(AVLNodePtr*, AVLNodePtr*);

int ReturnNodeHeight(AVLNodePtr);

void get_child_nodes(AVLNodePtr, int*, char*, char*);

AVLNodePtr rotateNodeRight(AVLNodePtr);

AVLNodePtr rotateNodeLeft(AVLNodePtr);

int getBalanceFactor(AVLNodePtr);

void RR_rotation(AVLNodePtr*);

void LL_rotation(AVLNodePtr*);

void RL_Rotation(AVLNodePtr*);

void LR_Rotation(AVLNodePtr*);