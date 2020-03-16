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

// bool inputLLtoAVL(Linked_List Entries, AVLTreePtr AVL_Tree){
//     listNode tmp = Entries->front;
//     while(tmp!=NULL){
//         if(!addAVLNode(AVL_Tree, tmp->item)){
//             return false;
//         }
//         tmp = tmp->next;
//     }
//     return true;
// }

bool inputLLtoHT(Linked_List Entries, HashTable HT_in, int ind){
    listNode tmp = Entries->front;
    while(tmp!=NULL){
        if(!addHT(HT_in, tmp->item, ind)){
            return false;
        }
        tmp = tmp->next;
    }
    return true;
}

int returnMaxInt(int a, int b){
    if(a>=b){ return a; }
    return b;
}

char* takeString(FILE *fp, size_t size){
    char *str;
    int ch;
    size_t len = 0;
    str = realloc(NULL, sizeof(char)*size);
    if(!str) return str;
    while( EOF!=(ch=fgetc(fp)) && ch!='\n' ){
        str[len++] = ch;
        if(len==size){
            str = realloc(str, sizeof(char)*(size+=16));
            if(!str) return str;
        }
    }
    str[len++]='\0';
    return realloc(str, sizeof(char)*len);
}

void Querries(HashTable HT_disease, HashTable HT_country){

    char *inputString = NULL;
    char *tmp, *ind1, *ind2, *instruct, *ind3, *ind4;

    printf("Select instruction.\n");
    inputString = takeString(stdin, 10);
    while(strcmp(inputString, "exit")!=0){
        tmp = strdup(inputString);
        if(tmp==NULL){
            printf("String failure.\n");
            return;
        }
        instruct = strtok(tmp," \n\t");
        ind1 = strtok(NULL," \n\t");
        ind2 = strtok(NULL," \n\t");
        ind3 = strtok(NULL," \n\t");
        ind4 = strtok(NULL," \n\t");
        printf("Instruction %s %s %s %s %s.\n", instruct, ind1, ind2, ind3, ind4);

        if(strcmp(instruct, "globalDiseaseStats")==0){
            if(ind1!=NULL && ind2==NULL){ 
                printf("Both dates should be either NULL or not NULL.\n");
            }
            else{
                globalDiseaseStats(HT_disease, ind1, ind2);
            }
        }
        else if( strcmp(instruct, "topk-Diseases" )==0){
            if(ind1==NULL || ind2==NULL){
                printf("Need to provide k and country.\n");
            }
            else if(ind3!=NULL && ind4==NULL){ 
                printf("Both dates should be either NULL or not NULL.\n");
            }
            else{
                topk(HT_country, ind1, ind2, ind3, ind4, true);
            }
        }
        else if( strcmp(instruct, "topk-Countries")==0 ){
            if(ind1==NULL || ind2==NULL){
                printf("Need to provide k and disease.\n");
            }
            else if(ind3!=NULL && ind4==NULL){ 
                printf("Both dates should be either NULL or not NULL.\n");
            }
            else{
                topk(HT_disease, ind1, ind2, ind3, ind4, false);
            }
        }
        else{
            printf("Not such instruction exists.\n");
        }
        free(tmp);
        free(inputString);
        printf("Select instruction.\n");
        inputString = takeString(stdin, 10);
    }
    free(inputString);
    return;
}

bool disMonitor(int diseaseHashtableNumOfEntries, int countryHashtableNumOfEntries, int bucketSize){
    FILE* file;
    size_t len = 0;
    __ssize_t read;
    char *line = NULL;
    Linked_List Entries;    // stores all correct the records

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

    // printLinkedList(Entries);

    // AVL
    // AVLTreePtr AVL_Tree;
    // if( (AVL_Tree = initAVLTree())==NULL ){
    //     fprintf(stderr, "Couldn't allocate AVL Tree. Abort...\n");
    //     return false;
    // }
    // if(!inputLLtoAVL(Entries, AVL_Tree)){
    //     fprintf(stderr, "Couldn't fill AVL tree. Abort...\n");
    //     return false;
    // }
    // printAVLTree(AVL_Tree);
    // emptyAVLTree(AVL_Tree);

    // Hash Table with disease
    printf("\n");
    HashTable HT_disease;
    if( (HT_disease = initHashTable(bucketSize, diseaseHashtableNumOfEntries))==NULL ){
        fprintf(stderr, "Couldn't allocate Hash Table. Abort...\n");
        emptyMonitor(&file, &Entries, &line);
        return false;
    }
    inputLLtoHT(Entries, HT_disease, 0);    // 0 for disease
    printHashTable(HT_disease);
    //

    // Hash Table with country
    printf("\n");
    HashTable HT_country;
    if( (HT_country = initHashTable(bucketSize, countryHashtableNumOfEntries))==NULL ){
        fprintf(stderr, "Couldn't allocate Hash Table. Abort...\n");
        emptyMonitor(&file, &Entries, &line);
        return false;
    }
    inputLLtoHT(Entries, HT_country, 1);    // 0 for disease
    printHashTable(HT_country);

    // querries
    Querries(HT_disease, HT_country);


    deleteHT(HT_disease);
    deleteHT(HT_country);
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