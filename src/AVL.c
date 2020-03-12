#include "../headers/AVL.h"
#include "../headers/disMonitor.h"

AVLTreePtr initAVLTree(){

    AVLTreePtr tree = malloc(sizeof(AVLTree));
    if(tree==NULL){
        return NULL;
    }

    tree->root = NULL;

    return tree;

}

// Postorder deletion of all tree Nodes
void emptyAVLnodes(AVLNodePtr node){

    if(node==NULL){
        return;
    }
    else{
        emptyAVLnodes(node->left);
        emptyAVLnodes(node->right);

        node->left = NULL;
        node->right = NULL;
        free(node);

    }
    return;
}

void emptyAVLTree(AVLTreePtr tree){

    emptyAVLnodes(tree->root);

    free(tree);

}

bool compareAdd(AVLNodePtr *existent, AVLNodePtr *added){

    if( (*existent)==NULL ){
        (*existent) = (*added);
        (*existent)->right = NULL;
        (*existent)->left = NULL;
        printf("ADDED\n");
    }
    else{

        int comparer = compareDates( (*existent)->item->entryDate, (*added)->item->entryDate);

        if(comparer==0 || comparer==2){
            // goes to the right
            printf("For existing %s and added %s we go right\n", (*existent)->item->entryDate, (*added)->item->entryDate);
            compareAdd( &(*existent)->right, &(*added));

        }
        else if(comparer==1){
            // goes to the left
            printf("For existing %s and added %s we go left\n", (*existent)->item->entryDate, (*added)->item->entryDate);
            compareAdd( &(*existent)->left, &(*added));

        }
        else{
            // -1 or -2
            printf("For existing %s and added %s we are in third\n", (*existent)->item->entryDate, (*added)->item->entryDate);
            free(*added);
            return false;
        }
    }

    return true;
}

bool addAVLNode(AVLTreePtr tree, patientRecord pR){

    AVLNodePtr node = malloc(sizeof(AVLNode));
    if(node==NULL){ return false; }
    node->item = pR;

    if( !compareAdd( &(tree->root), &node ) ){
        fprintf(stderr, "Couldn't add node in AVL. Abort...\n");
        return false;
    }

    return true;
}

// according to printing technics found online
void recPrintAVLNode(AVLNodePtr node, int space){

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
    recPrintAVLNode(node->right, space);

    printf("\n");
    for(i=10; i<space; i++){
        printf(" ");
    }
    
    printf("%s\n", node->item->entryDate);
    // printf("%s\n", node->item->recordId);

    recPrintAVLNode(node->left, space);
}

void printAVLTree(AVLTreePtr tree){

    recPrintAVLNode(tree->root, 0);

}