#include "../headers/includer.h"

void initMonitor(FILE **f, Linked_List *ll){    // ll is lList**

    *f = fopen("Assets/patientRecordsFile.txt","r");
    *ll = initlinkedList();

}

void emptyMonitor(FILE **f, Linked_List *ll, char** line){

    free(*line);
    free(*ll);
    fclose(*f);

}

void disMonitor(){
    FILE* file;
    size_t len = 0;
    __ssize_t read;
    char *line = NULL;
    Linked_List Entries;

    initMonitor(&file, &Entries);

    if(file==NULL){
        fprintf(stderr, "Couldn't open txt file. Abort...\n");
        return;
    }

    while( (read=getline(&line, &len, file))!=-1 ){
        printf("\nFile line is %s", line);
        
        patientRecord a = initRecord(line);

        addNode(&Entries, &a);
        
    }

    emptyLinkedList(&Entries);

    emptyMonitor(&file, &Entries, &line);

}