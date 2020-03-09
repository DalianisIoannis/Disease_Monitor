#include "../headers/linkedList.h"

Linked_List initlinkedList(){
    Linked_List ll;

    ll = malloc(sizeof(lList));
    (ll)->front     = NULL;
    (ll)->rear      = NULL;

    return ll;
}

void addNode(Linked_List *ll, patientRecord *pR){

    listNode listNode = malloc(sizeof(lNode));
    
    listNode->item = malloc(sizeof(pRecord));

    memcpy(listNode->item, (*pR), sizeof(pRecord));

    if( (*ll)->front==NULL ){   // empty list
        (*ll)->front = listNode;
        (*ll)->front->next = NULL;
        
        (*ll)->rear = listNode;
        (*ll)->rear->next = NULL;
    }
    else{
        (*ll)->rear->next = listNode;
        (*ll)->rear = listNode;
        (*ll)->rear->next = NULL;
    }
    
    
    free(*pR);
    return;
}

void emptyLinkedList(Linked_List *ll){

    listNode tmp;
    while ( (*ll)->front!=NULL ){

        // free((*ll)->front->item->recordId);
        // free( (*ll)->front->item );

        deleteRecord( &((*ll)->front->item) );

        tmp = (*ll)->front->next;
        
        (*ll)->front->next = NULL;
        free((*ll)->front);
        
        (*ll)->front = tmp;

    }
    

}