#pragma once

#include "./disMonitor.h"
#include <stdbool.h>

typedef struct counterNode{

    char *item;
    struct counterNode *next;
} counterNode;

typedef counterNode *cNode;


typedef struct{
    int count;
    cNode start;
} counterList;

typedef counterList *cList;



cList initcList();

bool addcNode(cNode*, char*, int*);

void deletecList(cList*);

void printcList(cNode);