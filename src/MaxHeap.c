#include "../headers/MaxHeap.h"

MaxHeapPtr initMaxHeap(){
    MaxHeapPtr tree = malloc(sizeof(MaxHeap));
    if(tree==NULL){
        return NULL;
    }
    tree->root = NULL;
    return tree;
}

void emptyMaxHeapNode(HeapNodePtr node){
    if(node==NULL){
        return;
    }
    else{
        emptyMaxHeapNode(node->left);
        emptyMaxHeapNode(node->right);
        node->occurence = NULL;
        free(node);
    }
}

void emptyMaxHeap(MaxHeapPtr tree){
    emptyMaxHeapNode(tree->root);
    free(tree);
}

void printMaxHeapNode(HeapNodePtr node, int space){
    int i;
    if(node==NULL){
        space += 10;
        for(i=10; i<space; i++){
            printf(" ");
        }
        printf("NULL");
        return;
    }
    space += 10;
    printMaxHeapNode(node->right, space);
    printf("\n");
    for(i=10; i<space; i++){
        printf(" ");
    }
    if( strcmp(node->occurence, "$$$$$$$$$$$")!=0 ){
        printf("D:%s, Num:%d\n", node->occurence, node->total);
    }
    else{
        printf("NULL");
    }
    printMaxHeapNode(node->left, space);
}

void printMaxHeapTree(MaxHeapPtr tree){
    printMaxHeapNode(tree->root, 0);
}

// incresases total of occurences 
bool searchAllexisting(HeapNodePtr *father, char *item){
    if( (*father)==NULL ){
        return false;
    }
    else{
        // printf("Compare %s with %s\n", (*father)->occurence, item);
        if( strcmp( (*father)->occurence, item )==0 ){
            (*father)->total++;
            return true;
        }
        bool tmp = searchAllexisting( &(*father)->left, item );
        if(tmp==true){
            return true;
        }
        return searchAllexisting( &(*father)->right, item );
    }
    return false;
}

void findParentOfInsertedNode(HeapNodePtr node, int insId, HeapNodePtr *father){
    if( node->id==(insId/2) ){
        (*father) = node;   // under this father we insert the node
    }
    if( node->left!=NULL ){
        findParentOfInsertedNode( node->left, insId, father );
    }
    if( node->right!=NULL ){
        findParentOfInsertedNode( node->right, insId, father );
    }
}

void insertNodetoMaxHeap(HeapNodePtr *root, HeapNodePtr new_node){
    HeapNodePtr parent;
    if( new_node->id==1 ){  // put in root
        (*root) = new_node;
    }
    else{
        findParentOfInsertedNode( (*root), new_node->id, &parent );
        if( (new_node->id)%2==1 ){
            parent->right = new_node;
        }
        else{
            parent->left = new_node;
        }
    }
}

void compareFatherWithChild(HeapNodePtr *father, HeapNodePtr *child){

    // printf("Compare father with virus %s and total occurences %d with child with virus %s and total occurences %d.\n", (*father)->occurence, (*father)->total, (*child)->occurence, (*child)->total);
    if( (*father)->total< (*child)->total ){
        int tmpInt;
        char *tmpStr;

        tmpInt = (*father)->total;
        (*father)->total = (*child)->total;
        (*child)->total = tmpInt;

        tmpStr = (*father)->occurence;
        (*father)->occurence = (*child)->occurence;
        (*child)->occurence = tmpStr;
    }
}

void reheapify(HeapNodePtr *node){

    if( (*node)->left!=NULL ){
        reheapify( &((*node)->left) );
    }
    if( (*node)->right!=NULL ){
        reheapify( &((*node)->right) );
    }

    if( (*node)->right!=NULL ){
        if( (*node)->left!=NULL ){
            if( ((*node)->left)->total > ((*node)->right)->total ){
                // compare current with left child
                compareFatherWithChild( node, &((*node)->left) );
            }
            else{
                // compare current with right child
                compareFatherWithChild( node, &((*node)->right) );
            }
        }
        else{
            // compare current with right child
            compareFatherWithChild( node, &((*node)->right) );
        }
    }
    else{
        if( (*node)->left!=NULL ){
            // compare current with left child
            compareFatherWithChild( node, &((*node)->left) );
        }
    }
}

void printKlargestItems(MaxHeapPtr tree, int k){
    // printf("I am going to print the %d largest items of Heap:\n", k);
    // printMaxHeapTree(tree);
    // printf("\n\n\n");
    int began = k;
    while(k>0 && tree->root!=NULL){
        if( strcmp(tree->root->occurence, "$$$$$$$$$$$")!=0 ){
            printf("%dth\tmost common occurence is %s\t with %d incidents.\n", began-k+1, tree->root->occurence, tree->root->total);
        }
        tree->root->occurence = "$$$$$$$$$$$";
        tree->root->total = 0;
        reheapify( &(tree->root) );
        k--;
    }
}

bool addMaxHeapNode(MaxHeapPtr tree, char *item, int *id){

    if( searchAllexisting( &(tree->root), item )==true ){
        // printf("Found Same\n");
        reheapify( &(tree->root) );    // reheapify
    }
    else{
        HeapNodePtr node = malloc(sizeof(HeapNode));
        if(node==NULL){
            printf("Couldn't allocate Heap Node.\n");
            return false;
        }
        node->occurence = item;
        node->total = 1;
        node->id = (*id);
        node->left = NULL;
        node->right = NULL;
        insertNodetoMaxHeap( &(tree->root), node );
        (*id)++;
    }
    return true;
}