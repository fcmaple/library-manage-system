#include "lms.h"
void LMS::reset(){
    for(int i=0;i<MAX_USER;i++){
        memset(username[i],'\0',sizeof(username[i]));
        memset(password[i],'\0',sizeof(password[i]));
    }
    fprintf(stdout,"LMS Reset !\n");
}