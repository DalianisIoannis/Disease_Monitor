#include "../headers/counterList.h"

cList initcList(){
    cList l = malloc(sizeof(counterList));
    if( l==NULL ){
        fprintf(stderr, "Couldn't allocate counter List. Abort...\n");
        return NULL;
    }
    l->start = NULL;
    l->count = 0;

    return l;
}

void deletecList(cList *l){
    cNode tmp;
    while( (*l)->start!=NULL ){
        free((*l)->start->item);

        tmp = (*l)->start->next;

        (*l)->start->next = NULL;
        free((*l)->start);

        (*l)->start = tmp;
    }
    free(*l);
}

bool addcNode(cNode *node, char *s, int *count){

    if((*node)==NULL){
        cNode cN = malloc(sizeof(counterNode));
        if(cN==NULL){ return false; }
        cN->item = strdup(s);
        if(cN->item==NULL){ free(cN); return false; }

        (*node) = cN;
        (*node)->next = NULL;
        (*count)++;
        return true;
    }
    else{
        // printf("Compare %s with %s.\n", (*node)->item, s);
        if( strcmp((*node)->item, s)==0 ){
            return false;
        }
        else{
            return addcNode( &((*node)->next), s, count);
        }
    }
}

void printcList(cNode node){
    if(node==NULL){
        return;
    }
    printf("%s\n", node->item);
    printcList(node->next);
}