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

void emptyAVLnodes(AVLNodePtr node){    // Postorder deletion of all tree Nodes

    if(node==NULL){ return; }
    else{
        emptyAVLnodes(node->left);
        emptyAVLnodes(node->right);

        node->left  = NULL;
        node->right = NULL;
        free(node);
    }
    return;
}

void emptyAVLTree(AVLTreePtr tree){

    emptyAVLnodes(tree->root);
    free(tree);
}

int ReturnNodeHeight(AVLNodePtr node){
    if(node!=NULL){
        return node->nodeHeight;
    }
    return 0;
}

void recPrintAVLNode(AVLNodePtr node, int space){

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
    recPrintAVLNode(node->right, space);

    printf("\n");
    for(i=10; i<space; i++){
        printf(" ");
    }
    
    printf("%s H %d\n", node->item->entryDate, node->nodeHeight);
    // printf("%s\n", node->item->entryDate);
    // printf("%s max %d\n", node->item->entryDate, get_max_height_of_tree(node));

    recPrintAVLNode(node->left, space);
}

void printAVLTree(AVLTreePtr tree){

    recPrintAVLNode(tree->root, 0);
}

int getBalanceFactor(AVLNodePtr node){

    if(node==NULL){
        return 0;
    }
    else{
        return ReturnNodeHeight(node->right) - ReturnNodeHeight(node->left);
    }
}

AVLNodePtr rotateNodeRight(AVLNodePtr old_father){

    AVLNodePtr  left_son = old_father->left,
                grandson = old_father->left->right;

    left_son->right = old_father;
    old_father->left = grandson;

    // heights
    old_father->nodeHeight  = returnMaxInt( ReturnNodeHeight(old_father->left), ReturnNodeHeight(old_father->right) ) + 1;
    left_son->nodeHeight    = returnMaxInt( ReturnNodeHeight(left_son->left),  ReturnNodeHeight(left_son->right) ) + 1;

    return left_son;
}

AVLNodePtr rotateNodeLeft(AVLNodePtr old_father){

    AVLNodePtr  right_son = old_father->right,
                grandson = old_father->right->left;

    right_son->left = old_father;
    old_father->right = grandson;

    // heights
    old_father->nodeHeight  = returnMaxInt( ReturnNodeHeight(old_father->left), ReturnNodeHeight(old_father->right) ) + 1;
    right_son->nodeHeight   = returnMaxInt( ReturnNodeHeight(right_son->left), ReturnNodeHeight(right_son->right) ) + 1;

    return right_son;

}

bool compareAddNEW(AVLNodePtr *existent, AVLNodePtr *added){

    int comparer;
    if( (*existent)==NULL ){
        (*existent)         = (*added);
        (*existent)->right  = NULL;
        (*existent)->left   = NULL;
        // printf("ADDED\n");
    }
    else{

        comparer = compareDates( (*existent)->item->entryDate, (*added)->item->entryDate);
        
        // (*added)->nodeHeight += 1;   // update height

        if(comparer==0 || comparer==2){ // goes to the right
            // printf("For existing %s and added %s we go right\n", (*existent)->item->entryDate, (*added)->item->entryDate);
            compareAddNEW( &(*existent)->right, added);
        }
        else if(comparer==1){   // goes to the left
            // printf("For existing %s and added %s we go left\n", (*existent)->item->entryDate, (*added)->item->entryDate);
            compareAddNEW( &(*existent)->left, &(*added));
        }
        else{   // -1 or -2
            printf("For existing %s and added %s we are in third\n", (*existent)->item->entryDate, (*added)->item->entryDate);
            free(*added);
            return false;
        }

        (*existent)->nodeHeight = 1 + returnMaxInt( ReturnNodeHeight((*existent)->left), ReturnNodeHeight((*existent)->right) );

        // int balance;
    }

    return true;
}

// int returnMaxInt(int a, int b);
bool addAVLNode(AVLTreePtr tree, patientRecord pR){

    AVLNodePtr node = malloc(sizeof(AVLNode));
    if(node==NULL){ return false; }
    node->item = pR;
    node->nodeHeight = 1;

    if( !compareAddNEW( &(tree->root), &node ) ){
        fprintf(stderr, "Couldn't add node in AVL. Abort...\n");
        return false;
    }




    // printf("Meta tin eisagogi \n");
    // printAVLTree(tree);

    return true;
}