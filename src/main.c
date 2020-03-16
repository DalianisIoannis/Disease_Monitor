#include "../headers/disMonitor.h"
#include <stdio.h>

int main(int argc, char** argv){
    printf("\n\n");

    int diseaseHashtableNumOfEntries = 5,
        countryHashtableNumOfEntries = 5,
        // bucketSize = 100;
        bucketSize = 32;
        // bucketSize = 31;
        // bucketSize = 16;
        // bucketSize = 15;
        // bucketSize = 26;
    
    if( !disMonitor(diseaseHashtableNumOfEntries, countryHashtableNumOfEntries, bucketSize) ){
        fprintf(stderr, "Disease Monitor didn't work successfully!\n");
        exit(1);
    }
    
    printf("\n\n");
    return 0;
}