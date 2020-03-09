#include "../headers/includer.h"

int main(void){
    printf("Start\n");

    patientRecord* a = malloc(sizeof(patientRecord));
    
    disMonitor();
    
    free(a);

    printf("End\n");
    return 0;
}