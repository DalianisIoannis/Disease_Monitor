#include "../headers/includer.h"

bool initMonitor(FILE **f, Linked_List *ll){    // ll is lList**

    *f = fopen("Assets/patientRecordsFile.txt","r");
    if((*f)==NULL){
        fprintf(stderr, "Couldn't open txt file. Abort...\n");
        return false;
    }

    *ll = initlinkedList();
    if((*ll)==NULL){
        return false;
    }

    return true;
}

void emptyMonitor(FILE **f, Linked_List *ll, char** line){

    emptyLinkedList(ll);
    free(*line);
    free(*ll);
    fclose(*f);
}

bool inputLLtoAVL(Linked_List Entries, AVLTreePtr AVL_Tree){

    listNode tmp = Entries->front;

    while(tmp!=NULL){
        if(!addAVLNode(AVL_Tree, tmp->item)){
            return false;
        }
        tmp = tmp->next;
    }

    return true;
}

void inputLLtoCountList(Linked_List Entries, cList cl, int date_coun){

    listNode tmp = Entries->front;
    while(tmp!=NULL){
        if(date_coun==0){   // disease
            if( !addcNode(&(cl->start), tmp->item->diseaseID, &(cl->count)) ){
                // printf("Disease \t%s\t\thas been found again.\n", tmp->item->diseaseID);
            }
        }
        else{               // country
            if( !addcNode(&(cl->start), tmp->item->country, &(cl->count)) ){
                // printf("Country \t%s\t\thas been found again.\n", tmp->item->country);
            }
        }
        tmp = tmp->next;
    }
}

int returnMaxInt(int a, int b){
    if(a>=b){ return a; }
    return b;
}

bool disMonitor(){
    FILE* file;
    size_t len = 0;
    __ssize_t read;
    char *line = NULL;
    Linked_List Entries;

    if(!initMonitor(&file, &Entries)){
        return false;
    }

    while( (read=getline(&line, &len, file))!=-1 ){
        
        patientRecord a = initRecord(line);
        if(a==NULL){
            fprintf(stderr, "Couldn't allocate patientRecord. Abort...\n");
            return false;
        }
        if( compareDates(a->entryDate, a->exitDate)==1 ){   //check if dates are ok
            printf("Patient with recordId %s has wrong dates. Rejected!\n", a->recordId);
            deleteRecord(&a);
            continue;
        }
        if(!addNode(&Entries, a)){
            fprintf(stderr, "Couldn't add Linked List node. Abort...\n");
            return false;
        }
    }

    printLinkedList(Entries);

    // AVL
    AVLTreePtr AVL_Tree;
    if( (AVL_Tree = initAVLTree())==NULL ){
            fprintf(stderr, "Couldn't allocate AVL Tree. Abort...\n");
            return false;
        }
    if(!inputLLtoAVL(Entries, AVL_Tree)){
        fprintf(stderr, "Couldn't fill AVL tree. Abort...\n");
        return false;
    }
    printAVLTree(AVL_Tree);
    emptyAVLTree(AVL_Tree);

    // count different viruses
    cList countList;
    countList = initcList();
    inputLLtoCountList(Entries, countList, 0);
    int diff_diseases = countList->count;
    printf("\nPrint countList with %d diseases.\n", diff_diseases);
    printcList(countList->start);
    deletecList(&countList);

    // count different countries
    countList = initcList();
    inputLLtoCountList(Entries, countList, 1);
    int diff_countries = countList->count;
    printf("\nPrint countList with %d countries.\n", diff_countries);
    printcList(countList->start);
    deletecList(&countList);

    emptyMonitor(&file, &Entries, &line);

    return true;
}

// return 
// 0    if dates are same
// 1    if first date is bigger(later than second date)
// 2    for the opposite
// -1   if first is -
// -2   if second is -
int compareDates(char *d1, char *d2){

    if(strcmp(d2,"-")==0){
        return -2;
    }
    if(strcmp(d1,"-")==0){
        return -1;
    }
    else{   // none is -
        char *token, *temp;
        int day1, day2, month1, month2, year1, year2;
        
        temp = strdup(d1);
        if(temp==NULL){
            fprintf(stderr, "Couldn't allocate temp string. Abort...\n");
            exit(1);
        }

        token = strtok(temp,"-");
        day1 = atoi(token);

        token = strtok(NULL,"-");
        month1 = atoi(token);

        token = strtok(NULL,"-\n \t");
        year1 = atoi(token);

        free(temp);
        temp = strdup(d2);
        if(temp==NULL){
            fprintf(stderr, "Couldn't allocate temp string. Abort...\n");
            exit(1);
        }

        token = strtok(temp,"-");
        day2 = atoi(token);
        
        token = strtok(NULL,"-");
        month2 = atoi(token);
        
        token = strtok(NULL,"-\n \t");
        year2 = atoi(token);

        free(temp);

        // printf("Computed Date1 as %d-%d-%d\n", day1, month1, year1);
        // printf("Computed Date2 as %d-%d-%d\n", day2, month2, year2);

        if(year2>year1){
            return 2;
        }
        else if(year2==year1){
            if(month2>month1){
                return 2;
            }
            else if(month2==month1){
                if(day2>day1){
                    return 2;
                }
                else if(day2==day1){
                    return 0;
                }
                else{
                    return 1;
                }
            }
            else{
                return 1;
            }
        }
        else{
            return 1;
        }
    }
}