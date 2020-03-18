#include "../headers/AVL.h"

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

        node->item  = NULL; 
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

    left_son->right     = old_father;
    old_father->left    = grandson;
    old_father->nodeHeight  = returnMaxInt( ReturnNodeHeight(old_father->left), ReturnNodeHeight(old_father->right) )   + 1;
    left_son->nodeHeight    = returnMaxInt( ReturnNodeHeight(left_son->left),  ReturnNodeHeight(left_son->right) )      + 1;

    return left_son;
}

AVLNodePtr rotateNodeLeft(AVLNodePtr old_father){
    AVLNodePtr  right_son = old_father->right,
                grandson = old_father->right->left;

    right_son->left     = old_father;
    old_father->right   = grandson;
    old_father->nodeHeight  = returnMaxInt( ReturnNodeHeight(old_father->left), ReturnNodeHeight(old_father->right) )   + 1;
    right_son->nodeHeight   = returnMaxInt( ReturnNodeHeight(right_son->left), ReturnNodeHeight(right_son->right) )     + 1;

    return right_son;
}

int getUnhealed(AVLNodePtr node){
    int returner = 0;
    if(node==NULL){
        return 0;
    }
    else{
        returner += getUnhealed(node->left);
        returner += getUnhealed(node->right);
        if( strcmp(node->item->exitDate, "-")==0 ){
            returner++;
        }
        return returner;
    }
}

void get_child_nodes(AVLNodePtr node, int *total, char *d1, char *d2, char *comparer){    // returns node + childs of node
    // for diseaseFrequency
    // if comparer is NULL then i am in HT_disease
    // else i am in HT_country and comparer is virus name
    if(node==NULL){
        return;
    }
    else{
        if(comparer==NULL){
            if(d1==NULL){
                *total = *total + 1;
            }
            else{
                int compare1 = compareDates(d1, node->item->entryDate),
                    compare2 = compareDates(d2, node->item->entryDate);
                if( (compare1==0 || compare1==2) && (compare2==0 || compare2==1) ){
                    *total = *total + 1;
                }
            }
            get_child_nodes(node->left, total, d1, d2, comparer);
            get_child_nodes(node->right, total, d1, d2, comparer);
        }
        else{
            if(d1==NULL && strcmp(node->item->diseaseID, comparer)==0){
                *total = *total + 1;
            }
            else{
                int compare1 = compareDates(d1, node->item->entryDate),
                    compare2 = compareDates(d2, node->item->entryDate);
                if( (compare1==0 || compare1==2) && (compare2==0 || compare2==1) && strcmp(node->item->diseaseID, comparer)==0){
                    *total = *total + 1;
                }
            }
            get_child_nodes(node->left, total, d1, d2, comparer);
            get_child_nodes(node->right, total, d1, d2, comparer);
        }
    }
    return;
}

int ReturnNodeHeight(AVLNodePtr node){
    if(node!=NULL){
        return node->nodeHeight;
    }
    return 0;
}


int getBalanceFactor(AVLNodePtr node){
    if(node==NULL){
        return 0;
    }
    else{
        return ReturnNodeHeight(node->right) - ReturnNodeHeight(node->left);
    }
}

bool compareAdd(AVLNodePtr *existent, AVLNodePtr *added){
    int comparer;
    if( (*existent)==NULL ){
        (*existent)         = (*added);
        (*existent)->right  = NULL;
        (*existent)->left   = NULL;
    }
    else{

        comparer = compareDates( (*existent)->item->entryDate, (*added)->item->entryDate);
        
        if(comparer==0 || comparer==2){ // goes to the right
            compareAdd( &(*existent)->right, added);
        }
        else if(comparer==1){   // goes to the left
            compareAdd( &(*existent)->left, &(*added));
        }
        else{   // -1 or -2
            printf("For existing %s and added %s we have an error.\n", (*existent)->item->entryDate, (*added)->item->entryDate);
            free(*added);
            return false;
        }

        (*existent)->nodeHeight = 1 + returnMaxInt( ReturnNodeHeight((*existent)->left), ReturnNodeHeight((*existent)->right) );

        performRotations(existent, added);
    }
    return true;
}

void RR_rotation(AVLNodePtr* node){
    (*node) = rotateNodeRight((*node));
}

void LL_rotation(AVLNodePtr* node){
    (*node) = rotateNodeLeft((*node));
}

void RL_Rotation(AVLNodePtr* node){
    (*node)->right = rotateNodeRight((*node)->right);
    (*node) = rotateNodeLeft(*node);
}

void LR_Rotation(AVLNodePtr* node){
    (*node)->left = rotateNodeLeft((*node)->left);
    (*node) = rotateNodeRight(*node);
}

void performRotations(AVLNodePtr* existent, AVLNodePtr* added){
    int balance = getBalanceFactor((*existent));
    int strcomp;
    
    if((*existent)->right!=NULL){
        strcomp = compareDates( (*added)->item->entryDate, (*existent)->right->item->entryDate );
        
        if( balance>=2 && (strcomp==0 || strcomp==1)){
            LL_rotation(&(*existent));
        }
        if( balance>=2 && (strcomp==2)){
            RL_Rotation(&(*existent));
        }
    }
    if((*existent)->left!=NULL){
        strcomp = compareDates( (*added)->item->entryDate, (*existent)->left->item->entryDate );

        if( balance<=-2 && (strcomp==2) ){
            RR_rotation(&(*existent));
        }
        if( balance<=-2 && (strcomp==0 || strcomp==1) ){
            LR_Rotation(&(*existent));
        }
    }
}

bool addAVLNode(AVLTreePtr tree, patientRecord pR){
    AVLNodePtr node = malloc(sizeof(AVLNode));
    if(node==NULL){ return false; }
    node->item          = pR;
    node->nodeHeight    = 1;

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

    recPrintAVLNode(node->left, space);
}

void printAVLTree(AVLTreePtr tree){
    recPrintAVLNode(tree->root, 0);
}