#include "../headers/disMonitor.h"

bool initMonitor(FILE **f, Linked_List *ll, char *filename, AVLTreePtr *DuplicateTree){
    *f = fopen(filename, "r");
    if( (*f)==NULL ){
        fprintf(stderr, "Couldn't open txt file. Abort...\n");
        return false;
    }

    *ll = initlinkedList();
    if((*ll)==NULL){
        return false;
    }
    
    *DuplicateTree = initAVLTree();
    if((*DuplicateTree)==NULL){
        return false;
    }

    return true;
}

void emptyMonitor(FILE **f, Linked_List *ll, char** line, HashTable *HT_disease, HashTable *HT_country, AVLTreePtr *DuplicateTree){
    deleteHT(*HT_disease);
    deleteHT(*HT_country);
    emptyAVLTree(*DuplicateTree);
    emptyLinkedList(ll);
    free(*line);
    free(*ll);
    fclose(*f);
}

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

void Querries(HashTable HT_disease, HashTable HT_country, Linked_List Entries, AVLTreePtr *DuplicateTree){
    char *inputString = NULL;
    char *tmp, *ind1, *ind2, *instruct, *ind3, *ind4, *ind5, *ind6, *ind7;

    printf("Select instruction.\n");

    inputString = takeString(stdin, 10);
    while( strlen(inputString)==0 ){
        printf("Select instruction.\n");
        free(inputString);
        inputString = NULL;
        inputString = takeString(stdin, 10);
    }

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
        ind5 = strtok(NULL," \n\t");
        ind6 = strtok(NULL," \n\t");
        ind7 = strtok(NULL," \n\t");
        
        if(strcmp(instruct, "globalDiseaseStats")==0){
            if(ind1!=NULL && ind2==NULL){
                printf("Both dates should be either NULL or not NULL.\n\n");
            }
            else{
                if(ind1!=NULL){
                    int compDat = compareDates(ind1, ind2);
                    if( compDat==0 || compDat==2 ){
                        globalDiseaseStats(HT_disease, ind1, ind2);
                    }
                    else{
                        printf("Give correct dates.\n\n");
                    }
                }
                else{
                    globalDiseaseStats(HT_disease, ind1, ind2);
                }
            }
        }
        else if( strcmp(instruct, "topk-Diseases" )==0){
            if(ind1==NULL || ind2==NULL){
                printf("Need to provide k and country.\n\n");
            }
            else if(ind3!=NULL && ind4==NULL){ 
                printf("Both dates should be either NULL or not NULL.\n\n");
            }
            else{
                if(ind3!=NULL){
                    int compDat = compareDates(ind3, ind4);
                    if( compDat==0 || compDat==2 ){
                        topk(HT_country, ind1, ind2, ind3, ind4, true);
                    }
                    else{
                        printf("Give correct dates.\n\n");
                    }
                }
                else{
                    topk(HT_country, ind1, ind2, ind3, ind4, true);
                }
            }
        }
        else if( strcmp(instruct, "topk-Countries")==0 ){
            if(ind1==NULL || ind2==NULL){
                printf("Need to provide k and disease.\n\n");
            }
            else if(ind3!=NULL && ind4==NULL){ 
                printf("Both dates should be either NULL or not NULL.\n\n");
            }
            else{
                if(ind3!=NULL){
                    int compDat = compareDates(ind3, ind4);
                    if( compDat==0 || compDat==2 ){
                        topk(HT_disease, ind1, ind2, ind3, ind4, false);
                    }
                    else{
                        printf("Give correct dates.\n\n");
                    }
                }
                else{
                    topk(HT_disease, ind1, ind2, ind3, ind4, false);
                }
            }
        }
        else if( strcmp(instruct, "diseaseFrequency")==0 ){ // diseaseFrequency virusName date1 date2 [country]
            // instruct diseaseFrequency
            // ind1     virusName has to be not NULL
            // ind2     date1 has to be not NULL
            // ind3     date2 has to be not NULL
            // ind4     country can be NULL
            if( ind1==NULL || ind2==NULL || ind3==NULL ){
                printf("Need to provide proper variables.\n\n");
            }
            else{
                int compDat = compareDates(ind2, ind3);
                if(compDat!=0 && compDat!=2){
                    printf("Give correct dates.\n\n");
                }
                else{
                    if( ind4==NULL ){ // didn't give country
                        diseaseFrequencyNoCountry(HT_disease, ind1, ind2, ind3);
                    }
                    else{
                        diseaseFrequencyCountry(HT_country, ind1, ind4, ind2, ind3);
                    }
                }
            }
        }
        else if( strcmp(instruct, "insertPatientRecord")==0 ){
            // instruct is insertPatientRecord
            // ind1 is recordID
            // ind2 is patientFirstName
            // ind3 is patientLastName
            // ind4 is diseaseID
            // ind5 is country
            // ind6 is entryDate
            // ind7 is exitDate can be NULL
            if(ind6==NULL){
                printf("A new patient entry needs at least 6 characteristics.\n\n");
            }
            else{
                 char *line;
                if( ind7!=NULL ){
                    line = malloc( (strlen(ind1)+strlen(ind2)+strlen(ind3)+strlen(ind4)+strlen(ind5)+strlen(ind6)+strlen(ind7)+7)*sizeof(char) );
                }
                else{
                    line = malloc( (strlen(ind1)+strlen(ind2)+strlen(ind3)+strlen(ind4)+strlen(ind5)+strlen(ind6)+8)*sizeof(char) );
                }
                if(line==NULL){
                    printf("Couldn't allocate line.\n");
                    return;
                }
                strcpy(line, ind1);
                strcat(line, " ");
                strcat(line, ind2);
                strcat(line, " ");
                strcat(line, ind3);
                strcat(line, " ");
                strcat(line, ind4);
                strcat(line, " ");
                strcat(line, ind5);
                strcat(line, " ");
                strcat(line, ind6);
                strcat(line, " ");
                if( ind7==NULL ){
                    strcat(line, "-");
                }
                else{
                    strcat(line, ind7);
                }

                patientRecord a = initRecord(line);
                free(line);
                if(a==NULL){
                    fprintf(stderr, "Couldn't allocate patientRecord. Abort...\n");
                    return;
                }
                if( compareDates(a->entryDate, a->exitDate)==1 ){   //check if dates are ok
                    printf("Patient with recordId %s has wrong dates. Rejected!\n\n", a->recordId);
                    deleteRecord(&a);
                }
                else{
                    if( addAVLNode(*DuplicateTree, a, a->recordId)==false ){
                        printf("Such recordId already exists!\n\n");
                        deleteRecord(&a);
                    }
                    else{
                        if(!addNode(&Entries, a)){
                            printf("Such recordId already exists in List!\n");
                        }
                        else{
                            if(!addHT(HT_country, a, 1)){
                                printf("Error!\n");
                                return;
                            }
                            if(!addHT(HT_disease, a, 0)){
                                printf("Error!\n");
                                return;
                            }
                            printf("New record added.\n\n");
                        }
                    }
                }
            }
        }
        else if(strcmp(instruct, "recordPatientExit")==0){
            if(ind1==NULL || ind2==NULL){
                printf("Need to provide recordId and exitDate.\n\n");
            }
            else{
                if( UpdateExitDate( &((*DuplicateTree)->root), ind1, ind2 ) ){
                    printf("\nPatient exitDate changed!\n\n");
                }
            }
        }
        else if( strcmp(instruct, "numCurrentPatients")==0 ){
            numCurrentPatients(HT_disease, ind1);
        }
        else{
            printf("\nNo such instruction exists.\n\n");
        }
        free(tmp);
        free(inputString);
        printf("Select instruction.\n");
        inputString = takeString(stdin, 10);
        while( strlen(inputString)==0 ){
            printf("Select instruction.\n");
            free(inputString);
            inputString = NULL;
            inputString = takeString(stdin, 10);
        }
    }
    free(inputString);
    return;
}

bool disMonitor(char *filename, int diseaseHashtableNumOfEntries, int countryHashtableNumOfEntries, int bucketSize){
    FILE*       file;
    size_t      len     = 0;
    __ssize_t   read;
    char        *line   = NULL;
    Linked_List Entries;
    HashTable   HT_disease, HT_country;
    AVLTreePtr  DuplicateTree;

    if( !initMonitor(&file, &Entries, filename, &DuplicateTree) ){
        return false;
    }
    printf("Loading. Please Wait...\n");
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
        if( addAVLNode(DuplicateTree, a, a->recordId)==false ){ // check and add in duplicator tree
            fprintf(stderr, "Patient with recordId %d already exists. Rejected!\n", atoi(a->recordId));
            deleteRecord(&a);
            free(line);
            emptyAVLTree(DuplicateTree);
            emptyLinkedList(&Entries);
            free(Entries);
            fclose(file);
            return false;
        }
        else{
            if(!addNode(&Entries, a)){
                fprintf(stderr, "Couldn't add Linked List node. Abort...\n");
                return false;
            }
        }
    }

    printf("\n");   // Hash Table with disease
    if( (HT_disease = initHashTable(bucketSize, diseaseHashtableNumOfEntries))==NULL ){
        fprintf(stderr, "Couldn't allocate Hash Table. Abort...\n");
        return false;
    }
    inputLLtoHT(Entries, HT_disease, 0);    // 0 for disease
    
    // printf("Hash Table of Diseases is:\n"); printHashTable(HT_disease);

    printf("\n");   // Hash Table with country
    if( (HT_country = initHashTable(bucketSize, countryHashtableNumOfEntries))==NULL ){
        fprintf(stderr, "Couldn't allocate Hash Table. Abort...\n");
        return false;
    }
    inputLLtoHT(Entries, HT_country, 1);    // 1 for country

    // printf("Hash Table of Countries is:\n"); printHashTable(HT_country);

    Querries(HT_disease, HT_country, Entries, &DuplicateTree);

    // printf("Check after querries.\n");
    // printLinkedList(Entries);
    // printHashTable(HT_disease);
    // printHashTable(HT_country);
    // printAVLTree(DuplicateTree);

    emptyMonitor(&file, &Entries, &line, &HT_disease, &HT_country, &DuplicateTree);

    return true;
}