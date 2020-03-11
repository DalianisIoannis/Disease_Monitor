#include "../headers/linkedList.h"

Linked_List initlinkedList(){
    Linked_List ll = malloc(sizeof(lList));

    if( ll==NULL ){
        fprintf(stderr, "Couldn't allocate Linked List. Abort...\n");
        return NULL;
    }

    (ll)->front     = NULL;
    (ll)->rear      = NULL;

    return ll;
}

bool checkDup(Linked_List *ll, patientRecord pR){

    listNode tmp = (*ll)->front;
    while ( tmp!=NULL ){
        
        // if(tmp->item->recordId == pR->recordId){
        if( strcmp(tmp->item->recordId, pR->recordId)==0 ){
            printf("Patient with recordId %d already exists. Rejected!\n", atoi(pR->recordId));
            return false;
        }
        tmp = tmp->next;
    }
    return true;

}

// void addNode(Linked_List *ll, patientRecord *pR){
bool addNode(Linked_List *ll, patientRecord pR){
    
    listNode listNode = malloc(sizeof(lNode));
    if(listNode==NULL){ return false; }
    
    // listNode->item = malloc(sizeof( &(*pR) ));
    listNode->item = malloc(sizeof(pRecord));
    if(listNode->item==NULL){ return false; }

    // memcpy(listNode->item, (*pR), sizeof(pRecord));
    memcpy(listNode->item, (pR), sizeof(pRecord));

    if( (*ll)->front==NULL ){   // empty list
        (*ll)->front = listNode;
        (*ll)->front->next = NULL;
        
        (*ll)->rear = listNode;
        (*ll)->rear->next = NULL;
    }
    else{
        if(checkDup(ll, pR)){   // check if already exists
            (*ll)->rear->next = listNode;
            (*ll)->rear = listNode;
            (*ll)->rear->next = NULL;
        }
        else{
            deleteRecord( &(listNode->item) );
            free(listNode);
        }
        
    }
    
    free(pR);

    return true;
}

void emptyLinkedList(Linked_List *ll){

    printf("\n");
    listNode tmp;
    while ( (*ll)->front!=NULL ){

        deleteRecord( &((*ll)->front->item) );

        tmp = (*ll)->front->next;
        
        (*ll)->front->next = NULL;
        free((*ll)->front);
        
        (*ll)->front = tmp;

    }
    
}

void printLinkedList(Linked_List ll){
    listNode tmp = ll->front;
    while(tmp!=NULL){
        
        printRecord(tmp->item);

        tmp = tmp->next;

        printf("\n");
    }
}