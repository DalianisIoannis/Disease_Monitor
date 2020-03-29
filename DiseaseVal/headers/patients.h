#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
    char* recordId;
    char* patientFirstName;
    char* patientLastName;
    char* diseaseID;
    char* country;
    char* entryDate;
    char* exitDate;
} pRecord;

typedef pRecord *patientRecord;


patientRecord initRecord(char*);
void printRecord(patientRecord);
void deleteRecord(patientRecord*);
void changePatientExitDate(patientRecord*, char*);