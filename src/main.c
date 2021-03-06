#include "../headers/disMonitor.h"
#include "../headers/generalFuncs.h"

int main(int argc, char** argv){
    
    // ./diseaseMonitor -p patientRecordsFile –h1 diseaseHashtableNumOfEntries –h2 countryHashtableNumOfEntries –b bucketSize
    // argv[0] ./diseaseMonitor
    // argv[1] -p
    // argv[2] patientRecordsFile
    // argv[3] –h1
    // argv[4] diseaseHashtableNumOfEntries
    // argv[5] –h2
    // argv[6] countryHashtableNumOfEntries
    // argv[7] –b
    // argv[8] bucketSize
    if(argv[8]==NULL){
        fprintf(stderr, "Command must be in form: ./diseaseMonitor -p patientRecordsFile –h1 diseaseHashtableNumOfEntries –h2 countryHashtableNumOfEntries –b bucketSize!\n");
        exit(1);
    }
    if( access( argv[2], F_OK ) == -1 ){
        fprintf(stderr, "File %s doesn't exist. Abort...\n", argv[2]);
        exit(1);
    }
    if( isNumber(argv[4])==false || isNumber(argv[6])==false || isNumber(argv[8])==false ){
        fprintf(stderr, "diseaseHashtableNumOfEntries, countryHashtableNumOfEntries and bucketSize must be numbers. Abort...\n");
        exit(1);
    }

    if( !disMonitor(argv[2], atoi(argv[4]), atoi(argv[6]), atoi(argv[8])) ){
        fprintf(stderr, "Disease Monitor didn't work successfully!\n");
        exit(1);
    }

    return 0;
}