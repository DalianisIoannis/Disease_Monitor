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

void get_child_nodes(AVLNodePtr node, int *total){    // returns how many child nodes a node has but needs -1 in result
    if(node==NULL){
        return;
    }
    else{
        *total = *total + 1;
        get_child_nodes(node->left, total);
        get_child_nodes(node->right, total);

    }
    return;
}

int get_max_height_of_tree(AVLNodePtr node){

    if(node==NULL){
        return -1;
    }
    else{
        int cur = node->nodeHeight;
        int tmp = get_max_height_of_tree(node->left);
        if(tmp>cur){
            cur = tmp;
        }
        tmp = get_max_height_of_tree(node->right);
        if(tmp>cur){
            cur = tmp;
        }
        return cur;
    }
}

int ReturnNodeHeight(AVLNodePtr node){
    if(node!=NULL){
        return node->nodeHeight;
    }
    return 0;
}

void reduceNodeAndSubtreeHeight(AVLNodePtr node){
    if(node==NULL){
        return;
    }
    node->nodeHeight -= 1;
    reduceNodeAndSubtreeHeight(node->left);
    reduceNodeAndSubtreeHeight(node->right);
}

void increasNodeAndSubtreeHeight(AVLNodePtr node){
    if(node==NULL){
        return;
    }
    node->nodeHeight += 1;
    reduceNodeAndSubtreeHeight(node->left);
    reduceNodeAndSubtreeHeight(node->right);
}

// pairnoun ton mpampa kai einai deiktis gia patera
AVLNodePtr LL_Rotation(AVLNodePtr old_father){

    AVLNodePtr tmp      = (old_father)->right;
    (old_father)->right = tmp->left;
    tmp->left           = (old_father);

    increasNodeAndSubtreeHeight(tmp->left->left);
    if(tmp->left!=NULL){
        tmp->left->nodeHeight += 1;
    }
    reduceNodeAndSubtreeHeight(tmp->right);
    tmp->nodeHeight -= 1;

    return tmp;
}

AVLNodePtr RR_Rotation(AVLNodePtr old_father){
    
    AVLNodePtr tmp      = (old_father)->left;
    (old_father)->left  = tmp->right;
    tmp->right          = (old_father);

    increasNodeAndSubtreeHeight(tmp->right->right);
    if(tmp->right!=NULL){
        tmp->right->nodeHeight += 1;
    }
    reduceNodeAndSubtreeHeight(tmp->left);
    tmp->nodeHeight -= 1;

    return tmp;
}

AVLNodePtr LR_Rotation(AVLNodePtr old_father){

    AVLNodePtr tmp      = (old_father)->left;
    (old_father)->left  = tmp->right->right;
    AVLNodePtr tmp2     = tmp->right;
    tmp->right          = tmp->right->left;
    tmp2->left          = tmp;
    tmp2->right         = old_father;

    reduceNodeAndSubtreeHeight(tmp2->left->right);
    reduceNodeAndSubtreeHeight(tmp2->right->left);
    increasNodeAndSubtreeHeight(tmp2->right->right);
    if(tmp2->right!=NULL){
        tmp2->right->nodeHeight += 1;
    }
    tmp2->nodeHeight -= 2;

    return tmp2;
}

AVLNodePtr RL_Rotation(AVLNodePtr old_father){

    AVLNodePtr tmp      = (old_father)->right;
    (old_father)->right = tmp->left->left;
    AVLNodePtr tmp2     = tmp->left;
    tmp->left           = tmp->left->right;
    tmp2->right         = tmp;
    tmp2->left          = old_father;

    reduceNodeAndSubtreeHeight(tmp2->right->left);
    reduceNodeAndSubtreeHeight(tmp2->left->right);
    increasNodeAndSubtreeHeight(tmp2->left->left);
    if(tmp2->left!=NULL){
        tmp2->left->nodeHeight += 1;
    }
    tmp2->nodeHeight -= 2;

    return tmp2;
}

// AVLNodePtr doubleRotateRight(AVLNodePtr old_father, AVLNodePtr added){
//     AVLNodePtr tmp;
// }

int getBalanceFactor(AVLNodePtr node){

    if(node==NULL){
        return 0;
    }
    else{
        return ReturnNodeHeight(node->right) - ReturnNodeHeight(node->left);
    }
}

void performRotations(AVLNodePtr *existent, AVLNodePtr *added){

    // printf("For existent %s check\n", (*existent)->item->entryDate);

    int balance = ReturnNodeHeight((*existent)->right) - ReturnNodeHeight((*existent)->left);
    int newcompare;
    int does_it_have_at_least_one_not_NULL_child=18;

    if( (*existent)->right==NULL ){ // check left subtree
        newcompare = 19;
    }
    else{
        newcompare = compareDates( (*existent)->right->item->entryDate,  (*added)->item->entryDate);
        if( (*existent)->right->right!=NULL || (*existent)->right->left!=NULL ){
            does_it_have_at_least_one_not_NULL_child = 1;
        }
        else{
            does_it_have_at_least_one_not_NULL_child = 0;
        }
    }

    if( balance>=2 && (newcompare==0 || newcompare==2) && does_it_have_at_least_one_not_NULL_child==1 ){
        printf("Gia tin %s me eisodo %s thelei LL\n", (*existent)->item->entryDate, (*added)->item->entryDate);
        (*existent) = LL_Rotation( (*existent) );
    }
    if( balance>=2 && newcompare==1 && does_it_have_at_least_one_not_NULL_child==1 ){
        printf("Gia tin %s me eisodo %s thelei RL\n", (*existent)->item->entryDate, (*added)->item->entryDate);
        (*existent) = RL_Rotation( (*existent) );
    }

    if( (*existent)->left==NULL ){  // check left subtree
        newcompare = 19;
    }
    else{
        newcompare = compareDates( (*existent)->left->item->entryDate,  (*added)->item->entryDate);
        if( (*existent)->left->right!=NULL || (*existent)->left->left!=NULL ){
            does_it_have_at_least_one_not_NULL_child = 1;
        }
        else{
            does_it_have_at_least_one_not_NULL_child = 0;
        }
    }

    if( balance<=-2 && newcompare==1 && does_it_have_at_least_one_not_NULL_child==1 ){
        printf("Gia tin %s me eisodo %s thelei RR\n", (*existent)->item->entryDate, (*added)->item->entryDate);
        (*existent) = RR_Rotation( (*existent) );
    }
    if( balance<=-2 && (newcompare==0 || newcompare==2) && does_it_have_at_least_one_not_NULL_child==1 ){
        printf("Gia tin %s me eisodo %s thelei LR\n", (*existent)->item->entryDate, (*added)->item->entryDate);
        (*existent) = LR_Rotation( (*existent) );
    }

    // // // // // // // // // // // check for long subtree right
    // printf("EIMAI STO %s kai to right->nodeHeight einai %d kai to max aristera einai %d\n", (*existent)->item->entryDate, );
    if( (ReturnNodeHeight( (*existent)->right ) - get_max_height_of_tree( (*existent)->left )  <= -2) && ((*existent)->right!=NULL) ){

        printf("Double Rotate Right node %s\n", (*existent)->item->entryDate);
        // printf("To ReturnNodeHeight( (*existent)->right ) einai %d\n", ReturnNodeHeight( (*existent)->right ));
        // printf("To get_max_height_of_tree( (*existent)->left ) einai %d\n", get_max_height_of_tree( (*existent)->left ));
        // (*existent) = doubleRotateRight( (*existent), (*added) );
    }

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

bool compareAdd(AVLNodePtr *existent, AVLNodePtr *added){

    int comparer;
    if( (*existent)==NULL ){
        (*existent)         = (*added);
        (*existent)->right  = NULL;
        (*existent)->left   = NULL;
        // printf("ADDED\n");
    }
    else{

        comparer = compareDates( (*existent)->item->entryDate, (*added)->item->entryDate);
        
        (*added)->nodeHeight += 1;   // update height

        if(comparer==0 || comparer==2){ // goes to the right
            // printf("For existing %s and added %s we go right\n", (*existent)->item->entryDate, (*added)->item->entryDate);
            compareAdd( &(*existent)->right, added);
        }
        else if(comparer==1){   // goes to the left
            // printf("For existing %s and added %s we go left\n", (*existent)->item->entryDate, (*added)->item->entryDate);
            compareAdd( &(*existent)->left, &(*added));
        }
        else{   // -1 or -2
            printf("For existing %s and added %s we are in third\n", (*existent)->item->entryDate, (*added)->item->entryDate);
            free(*added);
            return false;
        }

        // (*added)->nodeHeight += 1;   // update height
        
        performRotations( &(*existent), &(*added) );
    }

    return true;
}

bool addAVLNode(AVLTreePtr tree, patientRecord pR){

    AVLNodePtr node = malloc(sizeof(AVLNode));
    if(node==NULL){ return false; }
    node->item = pR;
    node->nodeHeight = 1;

    if( !compareAdd( &(tree->root), &node ) ){
        fprintf(stderr, "Couldn't add node in AVL. Abort...\n");
        return false;
    }

    printf("Meta tin eisagogi \n");
    printAVLTree(tree);

    return true;
}

// according to printing technics found online
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