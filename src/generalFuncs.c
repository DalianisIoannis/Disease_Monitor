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

    if(strcmp(d2,"-")==0){
        return -2;
    }
    if(strcmp(d1,"-")==0){
        return -1;
    }
    else{   // none is -
        char *token, *temp;
        int day1, day2, month1, month2, year1, year2;
        
        temp = strdup(d1);
        if(temp==NULL){
            fprintf(stderr, "Couldn't allocate temp string. Abort...\n");
            exit(1);
        }

        token = strtok(temp,"-");
        day1 = atoi(token);

        token = strtok(NULL,"-");
        month1 = atoi(token);

        token = strtok(NULL,"-\n \t");
        year1 = atoi(token);

        free(temp);
        temp = strdup(d2);
        if(temp==NULL){
            fprintf(stderr, "Couldn't allocate temp string. Abort...\n");
            exit(1);
        }

        token = strtok(temp,"-");
        day2 = atoi(token);
        
        token = strtok(NULL,"-");
        month2 = atoi(token);
        
        token = strtok(NULL,"-\n \t");
        year2 = atoi(token);

        free(temp);
        // printf("Computed Date1 as %d-%d-%d\n", day1, month1, year1);
        // printf("Computed Date2 as %d-%d-%d\n", day2, month2, year2);
        if(year2>year1){
            return 2;
        }
        else if(year2==year1){
            if(month2>month1){
                return 2;
            }
            else if(month2==month1){
                if(day2>day1){
                    return 2;
                }
                else if(day2==day1){
                    return 0;
                }
                else{
                    return 1;
                }
            }
            else{
                return 1;
            }
        }
        else{
            return 1;
        }
    }
}

char* takeString(FILE *fp, size_t size){
    char *str;
    int ch;
    size_t len = 0;
    str = realloc(NULL, sizeof(char)*size);
    if(!str) return str;
    while( EOF!=(ch=fgetc(fp)) && ch!='\n' ){
        str[len++] = ch;
        if(len==size){
            str = realloc(str, sizeof(char)*(size+=16));
            if(!str) return str;
        }
    }
    str[len++]='\0';
    return realloc(str, sizeof(char)*len);
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
                if(++dotCount>1){
                    return false;
                }
                break;
            case '-':
                if(++minusCount>1){
                    return false;
                }
                break;
            case '+':
                if(++plusCount>1){
                    return false;
                }
                break;
            default:
                if( c<'0' || c>'9'){
                    return false;
                }
        }
        str++;
    }
    return true;
}