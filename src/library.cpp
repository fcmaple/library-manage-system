#include "library.h"

LIBRARY::LIBRARY(){
    init();
}

void LIBRARY::init(){
    for(int i=0;i<MAX_BOOKS;i++){
        std::string str = std::to_string(i);
        books[i].set(str.c_str());
    }
    fprintf(stdout,"LIBRARY init !\n");
}
int LIBRARY::borrow(int id,const char* bookName){
    for(int i=0;i<MAX_BOOKS;i++){
        int state = books[i].match(bookName);
        if(state>0){
            books[i].borrow(id);
            return id;
        }else if(state==0){
            fprintf(stdout,"The book is already borrowed !\n");
            return -1;
        }
    }
    fprintf(stdout,"The book is not existed in Library !\n");
    return -1;
}
int LIBRARY::back(int id,const char* bookName){
    for(int i=0;i<MAX_BOOKS;i++){
        if(books[i].match(bookName)){
            books[i].back();
            return id;
        }
    }
    return -1;
}