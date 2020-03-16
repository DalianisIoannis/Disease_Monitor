#include "../headers/disMonitor.h"
#include "../headers/HashTable.h"
#include "../headers/AVL.h"
#include "../headers/MaxHeap.h"

HashTable initHashTable(int bucket_size, int entries){
    HashTable HT = malloc(sizeof(HTable));
    if(HT==NULL){ return NULL; }

    HT->bucket_size = bucket_size;
    HT->entries = entries;

    int array_size = HT->bucket_size/sizeof(void*);

    if(array_size%2==1){
        array_size--;
    }
    if(array_size==0){
        printf("Bucket_Size should be at least 16 bytes to store 2 void pointers.\n");
        free(HT);
        return NULL;
    }

    HT->bucket_array = malloc( (HT->entries)*sizeof(Bucket) );
    if(HT->bucket_array==NULL){ free(HT); return NULL; }

    for(int i=0; i<HT->entries; i++){
        (HT->bucket_array)[i].next = NULL;
        (HT->bucket_array)[i].totalValues = array_size;
        
        (HT->bucket_array)[i].arr = malloc( array_size*sizeof(void*) );

        for(int j=0; j<(HT->bucket_array)[i].totalValues; j++){
            ((HT->bucket_array)[i]).arr[j] = NULL;
        }
    }
    return HT;
}

void emptyBucket(hashBucket *HtB, int do_i_delete_next){
    if( (*HtB)!=NULL ){
        // printf("Emptying\n");
        for(int i=1; i<(*HtB)->totalValues; i+=2){
            (*HtB)->arr[i-1] = NULL;
            if( (*HtB)->arr[i]!=NULL ){
                emptyAVLTree( (*HtB)->arr[i] );
                (*HtB)->arr[i] = NULL;
            }
        }
        free( (*HtB)->arr );
        emptyBucket( &(*HtB)->next, 1 );
        if(do_i_delete_next==1){
            free( (*HtB) );
        }
    }
}

void deleteHT(HashTable HT){
    for(int i=0; i<HT->entries; i++){
        // printf("\nEmpty bucket %d\n", i);
        Bucket *h = &((HT->bucket_array)[i]) ;
        emptyBucket( (&h) , 0 );
    }
    free(HT->bucket_array);
    free(HT);
}

void printBucket(hashBucket HtB){
    if(HtB!=NULL){
        printf("\n\n\nBucket saves %d value pairs when sizeof(*void) is %ld.\n", HtB->totalValues, sizeof(void*));
        for(int i=0; i<HtB->totalValues; i++){
            if(HtB->arr[i]==NULL && i%2==0){
                printf("\n\tPosition %d has value %p.\n", i, HtB->arr[i]);
            }
            else if(i%2==0){
                printf("\n\tPosition %d has value %s.\n", i, (char*)HtB->arr[i]);
            }
            else if(HtB->arr[i]!=NULL){
                printf("\tAVL tree of bucket\n");
                printAVLTree(HtB->arr[i]);
                printf("\n");
            }
        }
        if(HtB->next!=NULL){
            printf("Next bucket:\n");
        }
        printBucket(HtB->next);
    }
}

void printHashTable(HashTable HT){
    printf("\nHash Table has %d entries and %d bucket_size.\n", HT->entries, HT->bucket_size);
    for(int i=0; i<HT->entries; i++){
        printBucket(&(HT->bucket_array)[i]);
    }
}

hashBucket addNewBucket(patientRecord pR, int ind, int totalValues){
    if(ind==0){
        printf("\nMAKE NEW BUCKET for %s\n\n", pR->diseaseID);
    }
    else{
        printf("\nMAKE NEW BUCKET for %s\n\n", pR->country);
    }
    hashBucket b = malloc(sizeof(Bucket));
    if(b==NULL){
        printf("Problem in new bucket allocation.\n");
        return NULL;
    }
    b->totalValues = totalValues;
    b->next = NULL;

    b->arr = malloc( totalValues*sizeof(void*) );

    for(int j=0; j<b->totalValues; j++){
        b->arr[j] = NULL;
    }

    return b;
}

void addBucket(hashBucket HtB, patientRecord pR, int ind){
    bool have_i_entered_in_this_bucket = 0;
    for(int i=0; i<HtB->totalValues; i+=2){
        if(HtB->arr[i]==NULL){
            if(ind==0){
                HtB->arr[i] = pR->diseaseID;
            }
            else{
                HtB->arr[i] = pR->country;
            }
            AVLTreePtr tree = initAVLTree(); 
            HtB->arr[i+1] = tree;
            addAVLNode(HtB->arr[i+1], pR);
            have_i_entered_in_this_bucket = 1;
            break;
        }
        else{
            if( ind==0 && strcmp(HtB->arr[i], pR->diseaseID)==0 ){
                addAVLNode(HtB->arr[i+1], pR);
                have_i_entered_in_this_bucket = 1;
                break;
            }
            if( ind==1 && strcmp(HtB->arr[i], pR->country)==0 ){
                addAVLNode(HtB->arr[i+1], pR);
                have_i_entered_in_this_bucket = 1;
                break;
            }
        }
    }
    // need next bucket
    if(have_i_entered_in_this_bucket==0 && HtB->next!=NULL){
        addBucket(HtB->next, pR, ind);
        have_i_entered_in_this_bucket = 1;
    }
    if(have_i_entered_in_this_bucket==0){
        HtB->next = addNewBucket(pR, ind, HtB->totalValues);
        addBucket(HtB->next, pR, ind);
    }
}

// ind is 0 for disease and 1 for country
bool addHT(HashTable HT, patientRecord pR, int ind){
    if(ind==0){
        printf("Adding %s.\n", pR->diseaseID);
    }
    else{
        printf("Adding %s.\n", pR->country);
    }
    int hashValue;
    if(ind==0){
        hashValue = hashFunction(pR->diseaseID, HT->entries);
    }
    else{
        hashValue = hashFunction(pR->country, HT->entries);
    }
    // printf("Returned hash Value %d.\n", hashValue);
    addBucket( &(HT->bucket_array)[hashValue], pR, ind );
    return true;
}

int hashFunction(char *s, int divider){
    char *tmp = s;
    int ascci_value = 0;
    while(*tmp){
        ascci_value += (int)(*tmp);
        tmp++;
    }
    return ascci_value%divider;
}

void printNumOfDis(hashBucket b, char *d1, char *d2){
    if(b!=NULL){
        for(int i=0; i<b->totalValues; i+=2){
            if(b->arr[i]!=NULL){

                int total = 0;
                AVLTreePtr tt = b->arr[i+1];

                printAVLTree(tt);
                get_child_nodes( tt->root, &total, d1, d2 );

                printf("\n\n\nDisease %s has %d occurences.\n", (char*)b->arr[i], total);
            }
        }
        printNumOfDis(b->next, d1, d2);
    }
}

void globalDiseaseStats(HashTable HT, char *d1, char *d2){
    printf("\n");
    if(d1!=NULL){
        printf("Find occurences of all viruses from %s untill %s.\n", d1, d2);
    }
    else{
        printf("Find occurences of all viruses.\n");
    }
    for(int i=0; i<HT->entries; i++){
        printNumOfDis( &(HT->bucket_array)[i], d1, d2 );
    }
}

// recursively adds AVLnode values to Heap 
void addAVLnodeValuetoMaxHeap(AVLNodePtr node, MaxHeapPtr Heap, int *id, char *d3, char *d4, bool is_country){
    if(node==NULL){
        return;
    }
    else{
        addAVLnodeValuetoMaxHeap(node->left, Heap, id, d3, d4, is_country);
        addAVLnodeValuetoMaxHeap(node->right, Heap, id, d3, d4, is_country);
        if(d3!=NULL){
            int compd3 = compareDates(d3, node->item->entryDate);    // has to be 0 or 1
            int compd4 = compareDates(d4, node->item->entryDate);    // has to be 0 or 1
            if( (compd3==0 || compd3==1) && (compd4==0 || compd4==1) ){
                // printf("\nGoing to add %s.\n", node->item->diseaseID);
                // printf("So far Heap:\n");
                // printMaxHeapTree(Heap);
                // printf("\n");
                if(is_country==true){
                    addMaxHeapNode(Heap, node->item->diseaseID, id);
                }
                else{
                    addMaxHeapNode(Heap, node->item->country, id);
                }
            }
        }
        else{
            // printf("\nGoing to add %s.\n", node->item->diseaseID);
            // printf("So far Heap:\n");
            // printMaxHeapTree(Heap);
            // printf("\n");
            // addMaxHeapNode(Heap, node->item->diseaseID, id);
            if(is_country==true){
                addMaxHeapNode(Heap, node->item->diseaseID, id);
            }
            else{
                addMaxHeapNode(Heap, node->item->country, id);
            }
        }
    }
}

void accesSpecificBucket(hashBucket HtB, char *countr_or_disease, int k, char *d3, char *d4, bool is_country){
    if(HtB!=NULL){
        for(int i=0; i<HtB->totalValues; i+=2){
            if(HtB->arr[i]!=NULL){
                if(strcmp(HtB->arr[i], countr_or_disease)==0){
                    // Found specific country or disease
                    MaxHeapPtr MaxHeapTree = initMaxHeap();
                    if(MaxHeapTree==NULL){
                        printf("Couldn't allocate Max Heap.\n");
                        return;
                    }
                    printf("\n\tPosition %d has value %s.\n", i, (char*)HtB->arr[i]);
                    AVLTreePtr tmpAVL = HtB->arr[i+1];
                    AVLNodePtr AVLroot = tmpAVL->root;

                    int idcount = 1;
                    addAVLnodeValuetoMaxHeap(AVLroot, MaxHeapTree, &idcount, d3, d4, is_country);
                    
                    printf("\tAVL tree of bucket\n");
                    printAVLTree(tmpAVL);
                    printf("\n");
                    
                    printKlargestItems(MaxHeapTree, k);
                    
                    emptyMaxHeap(MaxHeapTree);
                    return;
                }
            }
        }
        if(HtB->next!=NULL){
            printf("Next bucket:\n");
        }
        accesSpecificBucket(HtB->next, countr_or_disease, k, d3, d4, is_country);
    }
}

void countryOccurences(HashTable HT, char *k, char *countr, char *d3, char *d4){
    int hV = hashFunction(countr, HT->entries);
    printf("Looking for country %s with hash Value %d.\n", countr, hV);
    accesSpecificBucket(&(HT->bucket_array)[hV], countr, atoi(k), d3, d4, true);
}

void diseaseOccurences(HashTable HT, char *k, char *dis, char *d3, char *d4){
    int hV = hashFunction(dis, HT->entries);
    printf("Looking for disease %s with hash Value %d.\n", dis, hV);
    accesSpecificBucket(&(HT->bucket_array)[hV], dis, atoi(k), d3, d4, false);
}

// if is_country==true find k more for particular country
// else find for particular disease k more countries
void topk(HashTable HT, char *d1, char *d2, char *d3, char *d4, bool is_country){
    printf("\n");
    if( is_country==true ){
        if(d3!=NULL){
            printf("Find occurences of all viruses in country %s from %s untill %s.\n", d2, d3, d4);
        }
        else{
            printf("Find occurences of all viruses in country %s.\n", d2);
        }
        countryOccurences(HT, d1, d2, d3, d4);
    }
    else{
        if(d3!=NULL){
            printf("Find occurences of all countries with disease %s from %s untill %s.\n", d2, d3, d4);
        }
        else{
            printf("Find occurences of all countries with disease %s.\n", d2);
        }
        diseaseOccurences(HT, d1, d2, d3, d4);
    }
}