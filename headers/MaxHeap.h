#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct HeapNode{
    char* occurence;
    int total;
    int id;
    struct HeapNode *right;
    struct HeapNode *left;
} HeapNode;

typedef struct HeapNode *HeapNodePtr;

typedef struct{
    HeapNodePtr root;
    int heapHeight; // total floors of heap
} MaxHeap;

typedef MaxHeap *MaxHeapPtr;




MaxHeapPtr initMaxHeap();

void emptyMaxHeap(MaxHeapPtr);

void emptyMaxHeapNode(HeapNodePtr);

void printMaxHeapNode(HeapNodePtr, int);

void printMaxHeapTree(MaxHeapPtr);

bool addMaxHeapNode(MaxHeapPtr, char*, HeapNodePtr*, int*);

bool searchAllexisting(HeapNodePtr*, char*);

void findParentOfInsertedNode(HeapNodePtr, int, HeapNodePtr*);

void insertNodetoMaxHeap(HeapNodePtr*, HeapNodePtr);

void reheapify(HeapNodePtr*);