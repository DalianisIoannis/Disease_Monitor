#include "../headers/generalFuncs.h"

int returnMaxInt(int a, int b){
    if(a>=b){ return a; }
    return b;
}

// return 
// 0    if dates are same
// 1    if first date is bigger(later than second date)
// 2    for the opposite
// -1   if first is -
// -2   if second is -
int compareDates(char *d1, char *d2){

    if(strcmp(d2,"-")==0){ return -2; }
    if(strcmp(d1,"-")==0){ return -1; }
    char *token, *temp;
    int day1, day2, month1, month2, year1, year2;
    
    temp = strdup(d1);
    if(temp==NULL){
        fprintf(stderr, "Couldn't allocate temp string. Abort...\n");
        exit(1);
    }

    token = strtok(temp,"-");
    if( isNumber(token)==false ){
        fprintf(stderr, "Date given wrong. Abort...\n");
        exit(1);
    }
    day1 = atoi(token);

    token = strtok(NULL,"-");
    if( isNumber(token)==false ){
        fprintf(stderr, "Date given wrong. Abort...\n");
        exit(1);
    }
    month1 = atoi(token);

    token = strtok(NULL,"-\n \t");
    if( isNumber(token)==false ){
        fprintf(stderr, "Date given wrong. Abort...\n");
        exit(1);
    }
    year1 = atoi(token);

    free(temp);
    temp = strdup(d2);
    if(temp==NULL){
        fprintf(stderr, "Couldn't allocate temp string. Abort...\n");
        exit(1);
    }

    token = strtok(temp,"-");
    if( isNumber(token)==false ){
        fprintf(stderr, "Date given wrong. Abort...\n");
        exit(1);
    }
    day2 = atoi(token);
    
    token = strtok(NULL,"-");
    if( isNumber(token)==false ){
        fprintf(stderr, "Date given wrong. Abort...\n");
        exit(1);
    }
    month2 = atoi(token);
    
    token = strtok(NULL,"-\n \t");
    if( isNumber(token)==false ){
        fprintf(stderr, "Date given wrong. Abort...\n");
        exit(1);
    }
    year2 = atoi(token);

    free(temp);

    if(year2>year1){
        return 2;
    }
    else if(year2==year1){
        if(month2>month1){
            return 2;
        }
        else if(month2==month1){
            if(day2>day1){ return 2; }
            else if(day2==day1){ return 0; }
            else{ return 1; }
        }
        else{ return 1; }
    }
    else{ return 1; }
}

bool isNumber(const char *str){
    if( str==NULL || *str=='\0' ){
        return false;
    }
    int minusCount  = 0,
        plusCount   = 0,
        dotCount    = 0;

    while(*str){
        char c = *str;
        switch(c){
            case '.':
                if(++dotCount>1){ return false; }
                break;
            case '-':
                if(++minusCount>1){ return false; }
                break;
            case '+':
                if(++plusCount>1){ return false; }
                break;
            default:
                if( c<'0' || c>'9'){ return false; }
        }
        str++;
    }
    return true;
}

// 0    if are same
// 1    if first  is bigger
// 2    for the opposite
// int comp_String_as_Int(char *s1, char *s2){
//     if( atoi(s1)>atoi(s2) ){
//         return 1;
//     }
//     else if(atoi(s1)==atoi(s2)){
//         return 0;
//     }
//     else{
//         return 2;
//     }
// }