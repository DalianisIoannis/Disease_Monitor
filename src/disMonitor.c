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
        
        // printf("\nFile line is %s", line);
        
        patientRecord a = initRecord(line);
        if(a==NULL){
            fprintf(stderr, "Couldn't allocate patientRecord. Abort...\n");
            return false;
        }
        //check if dates are ok
        if(!compareDates(a->entryDate, a->exitDate)){
            printf("Patient with recordId %s has wrong dates. Rejected!\n", a->recordId);
            deleteRecord(&a);
            continue;
        }

        // addNode(&Entries, &a);
        if(!addNode(&Entries, a)){
            fprintf(stderr, "Couldn't add Linked List node. Abort...\n");
            return false;
        }

    }

    printLinkedList(Entries);

    // emptyLinkedList(&Entries);
    emptyMonitor(&file, &Entries, &line);

    return true;
}

bool compareDates(char *d1, char *d2){

    printf("D1 is %s\n", d1);
    printf("D2 is %s\n", d2);

    if(strcmp(d2,"-")==0){
        return true;
        // printf("No Exit Date!\n");
    }
    else{
        char *token;
        int day1, day2, week1, week2, year1, year2;
        
        token = strtok(d1,"-");
        day1 = atoi(token);

        token = strtok(NULL,"-");
        week1 = atoi(token);

        token = strtok(NULL,"-\n \t");
        year1 = atoi(token);

        token = strtok(d2,"-");
        day2 = atoi(token);
        
        token = strtok(NULL,"-");
        week2 = atoi(token);
        
        token = strtok(NULL,"-\n \t");
        year2 = atoi(token);

        printf("Computed Date1 as %d-%d-%d\n", day1, week1, year1);
        printf("Computed Date2 as %d-%d-%d\n", day2, week2, year2);

        if(year2<year1){
            return false;
        }
        else if(year2==year1){
            if(week2<week1){
                return false;
            }
            else if(week2==week1){
                if(day2<day1){
                    return false;
                }
            }
        }
    }


    printf("\n");
    return true;

}