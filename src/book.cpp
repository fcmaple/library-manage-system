#include "book.h"

BOOK::BOOK(){
}
void BOOK::set(const char* bookName){
    memset(name,'\0',sizeof(name));
    strcpy(name,bookName);
    state = false;
    borrower = -1;
    // printf("Book Name: %s State: %d \n",name,state);
}
int BOOK::match(const char* bookName) const{
    // printf("%s %s\n",name,bookName);
    if(strlen(name) == strlen(bookName) && !strcmp(name,bookName) ){
        if(!state)  return 1;
        else return 0;
    }
    return -1;
}
int BOOK::borrow(int id){
    state = true;
    borrower = id;
    return state;
}
int BOOK::back(){
    state = false;
    return state;
}