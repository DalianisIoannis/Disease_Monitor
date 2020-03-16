#include "../headers/MaxHeap.h"

MaxHeapPtr initMaxHeap(){
    MaxHeapPtr tree = malloc(sizeof(MaxHeap));
    if(tree==NULL){
        return NULL;
    }
    tree->root = NULL;
    tree->heapHeight = 0;
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
        space += 10;    // 16
        for(i=10; i<space; i++){
            printf(" ");
        }
        printf("NULL");
        return;
    }
    space += 10;    // 16
    printMaxHeapNode(node->right, space);
    printf("\n");
    for(i=10; i<space; i++){
        printf(" ");
    }
    printf("%s, %d\n", node->occurence, node->total);

    printMaxHeapNode(node->left, space);
}

void printMaxHeapTree(MaxHeapPtr tree){
    printMaxHeapNode(tree->root, 0);
}

// adds bigger 
bool searchAllexisting(HeapNodePtr *father, char *item){
    if( (*father)==NULL ){
        return false;
    }
    else{
        printf("Compare %s with %s\n", (*father)->occurence, item);
        if( strcmp( (*father)->occurence, item )==0 ){
            (*father)->total++;
            return true;
        }
        // return 
        bool tmp = searchAllexisting( &(*father)->left, item );
        if(tmp==true){
            return true;
        }
        return searchAllexisting( &(*father)->right, item );
    }
    return false;
}

// HeapNodePtr returnLeftMostNonEmpty(HeapNodePtr root){
//     HeapNodePtr tmp = root;
//     while(tmp->left!=NULL){
//         tmp = tmp->left;
//     }
//     return tmp;
// }

// HeapNodePtr returnFirstEmpty(HeapNodePtr node){//, int height){//}, int *i_have_reached){
//     if(node==NULL){
//         return node;
//     }
//     return returnFirstEmpty(node->left);//, height);
//     return returnFirstEmpty(node->right);//, height);
// }

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

bool addMaxHeapNode(MaxHeapPtr tree, char *item, HeapNodePtr *last, int *id){


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