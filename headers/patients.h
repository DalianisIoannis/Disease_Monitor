#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
    char* recordId;
    char* name;
    char* surname;
    char* virus;
    char* country;


} pRecord;

typedef pRecord *patientRecord;

patientRecord initRecord(char*);

void printRecord();

void deleteRecord(patientRecord*);