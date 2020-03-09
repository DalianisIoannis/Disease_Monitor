#include "../headers/patients.h"

patientRecord initRecord(char* line){

    char *token;

    patientRecord p = malloc(sizeof(pRecord));

    printf("File INSIDE line is %s", line); // last line without \n

    token = strtok(line," ");

    p->recordId = malloc( (strlen(token)+1)*sizeof(char) );
    strcpy(p->recordId, token);
    printf("\tRecord with Id %s\n", p->recordId);

    return p;
}

void printRecord(){

    return;
}

void deleteRecord(patientRecord* p){

    printf("\tSvino to (*ll)->front->item->id %s\n", (*p)->recordId);

    free( (*p)->recordId );

    free( *p );

}