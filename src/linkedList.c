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
        if( strcmp(tmp->item->recordId, pR->recordId)==0 ){
            fprintf(stderr, "Patient with recordId %d already exists. Rejected!\n", atoi(pR->recordId));
            return false;
        }
        tmp = tmp->next;
    }
    return true;
}

bool addNode(Linked_List *ll, patientRecord pR){
    listNode llNode = malloc(sizeof(lNode));
    if(llNode==NULL){ return false; }
    
    llNode->item = pR;

    if( (*ll)->front==NULL ){   // empty list
        (*ll)->front = llNode;
        (*ll)->front->next = NULL;
        
        (*ll)->rear = llNode;
        (*ll)->rear->next = NULL;
    }
    else{
        if(checkDup(ll, pR)){   // check if already exists
            (*ll)->rear->next = llNode;
            (*ll)->rear = llNode;
            (*ll)->rear->next = NULL;
        }
        else{
            deleteRecord( &(llNode->item) );
            free(llNode);
            return false;
        }
    }
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

bool updateExitDate(Linked_List *ll, char *Id, char *date){
    listNode tmp = (*ll)->front;
    while(tmp!=NULL){
        if(strcmp(tmp->item->recordId, Id)==0){
            int comparer = compareDates(tmp->item->entryDate, date);
            if( comparer==0 || comparer==2 ){
                changePatientExitDate( &(tmp->item), date );
            }
            else{
                printf("Can't have exited on that date!\n");
            }
            return true;
        }
        tmp = tmp->next;
    }
    return false;
}