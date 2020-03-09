#pragma once
#include "./includer.h"

typedef struct lNode{

    patientRecord item;
    struct lNode *next;

} lNode;

typedef lNode *listNode;

typedef struct{
    listNode front;
    listNode rear;

}lList;

typedef lList *Linked_List;

Linked_List initlinkedList();

void addNode(Linked_List*, patientRecord*);

void emptyLinkedList(Linked_List*);