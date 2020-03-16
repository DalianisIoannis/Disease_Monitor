#pragma once

#include "./patients.h"
#include "./disMonitor.h"
#include <stdbool.h>


// bucket is made of an array of pointers
// [0]->pointer to string [1]->pointer to AVL [2]->pointer to string ...
typedef struct Bucket{

    int totalValues;    // mporei to arr na einai mikrotero gia na einai sosta ta zevgaria
    void **arr;          // saves pairs of string, pointer
    struct Bucket *next;    // next if current gets Full
} Bucket;

typedef Bucket *hashBucket;

typedef struct HTable{
    int bucket_size;    // for all buckets
    int entries;        // hash indexes -> possible results of hashFunction
    hashBucket bucket_array;    // buckets of Table

} HTable;

typedef HTable *HashTable;

HashTable initHashTable(int, int);

void deleteHT(HashTable);

void printHashTable(HashTable);

void printBucket(hashBucket);

void emptyBucket(hashBucket*, int);

int hashFunction(char*, int);

bool addHT(HashTable, patientRecord, int);

void addBucket(hashBucket, patientRecord, int);

hashBucket addNewBucket(patientRecord, int, int);

void printNumOfDis(hashBucket, char*, char*);

void globalDiseaseStats(HashTable, char*, char*);

void countryOccurences(HashTable, char*, char*, char*, char*);

void topk_Diseases(HashTable, char*, char*, char*, char*);

void printSpecificBucket(hashBucket, char*);