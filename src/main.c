#include "../headers/disMonitor.h"
#include <stdio.h>

int main(int argc, char** argv){
    printf("\n\n");

    // int diseaseHashtableNumOfEntries,
    //     countryHashtableNumOfEntries,
    //     bucketSize;
    
    if( !disMonitor() ){
        fprintf(stderr, "Disease Monitor didn't work successfully!\n");
        exit(1);
    }
    
    
    printf("\n\n");
    return 0;
}