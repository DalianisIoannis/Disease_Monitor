#include "../headers/patients.h"

patientRecord initRecord(char* line){

    // printf("File INSIDE line is %s", line); // last line without \n
    
    char *token;
    patientRecord p = malloc(sizeof(pRecord));
    if(p==NULL){
        return NULL;
    }

    token = strtok(line," \t");
    p->recordId = strdup(token);
    if(p->recordId==NULL){
        return NULL;
    }

    token   = strtok(NULL, " \t\n");
    p->patientFirstName = strdup(token);
    if(p->patientFirstName==NULL){
        return NULL;
    }

    token   = strtok(NULL, " \t\n");
    p->patientLastName = strdup(token);
    if(p->patientLastName==NULL){
        return NULL;
    }

    token   = strtok(NULL, " \t\n");
    p->diseaseID = strdup(token);
    if(p->diseaseID==NULL){
        return NULL;
    }

    token   = strtok(NULL, " \t\n");
    p->country = strdup(token);
    if(p->country==NULL){
        return NULL;
    }

    token   = strtok(NULL, " \t\n");
    p->entryDate = strdup(token);
    if(p->entryDate==NULL){
        return NULL;
    }

    token   = strtok(NULL, " \t\n");
    p->exitDate = strdup(token);
    if(p->exitDate==NULL){
        return NULL;
    }

    // printf("\tRecord with Id \t%s\n", p->recordId);
    // printf("\tRecord with patientFirstName \t%s\n", p->patientFirstName);
    // printf("\tRecord with patientLastName \t%s\n", p->patientLastName);
    // printf("\tRecord with diseaseID \t%s\n", p->diseaseID);
    // printf("\tRecord with country \t%s\n", p->country);
    // printf("\tRecord with entryDate \t%s\n", p->entryDate);
    // printf("\tRecord with exitDate \t%s\n", p->exitDate);

    return p;
}

void printRecord(patientRecord p){

    printf("Patient with recordId \t%s:\n", p->recordId);
    printf("\tpatientFirstName \t%s\n", p->patientFirstName);
    printf("\tpatientLastName \t%s\n", p->patientLastName);
    printf("\tdiseaseID \t%s\n", p->diseaseID);
    printf("\tcountry \t%s\n", p->country);
    printf("\tentryDate \t%s\n", p->entryDate);
    printf("\texitDate \t%s\n", p->exitDate);

}

void deleteRecord(patientRecord* p){

    printf("\tDelete patient with RecordId %s\n", (*p)->recordId);

    free( (*p)->recordId );
    free( (*p)->patientFirstName );
    free( (*p)->patientLastName );
    free( (*p)->diseaseID );
    free( (*p)->country );
    free( (*p)->entryDate );
    free( (*p)->exitDate );

    free( *p );
}