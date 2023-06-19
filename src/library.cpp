#include "library.h"

namespace fs = std::filesystem; 

LIBRARY::LIBRARY(){
    init();
}

void LIBRARY::init(){
    std::string dirPath = "./data";
    bookNum = 0;
    try {
        for (const fs::directory_entry& entry : fs::directory_iterator(dirPath)) {
            if (entry.is_regular_file()) {
                std::cout << entry.path() << std::endl;
                books[bookNum++].set(entry);
            }
        }
    } catch (const fs::filesystem_error& ex) {
        std::cerr << "Error: " << ex.what() << std::endl;
    }
    fprintf(stdout,"LIBRARY init ,book num: %d !\n",bookNum);
}
int LIBRARY::search(const char* bookName){
    std::string book_str(bookName);
    // book_str = stringToLower(book_str);
    for(int i=0;i<bookNum;i++){
        std::string bn = books[i].getName();
        // std:: cout <<book_str<< " "<< stringToLower(bn) <<std::endl;
        if(book_str!=stringToLower(bn)) continue;
        fprintf(stdout,"\nBook: %s\n",bookName);
        fprintf(stdout,"Borrowing status: ");
        if(books[i].getBorrower()<0) fprintf(stdout,"Avaliable\n");
        else fprintf(stdout,"Borrowed\n");
        fprintf(stdout,"Description: \n");
        books[i].showDescription();
        return 1;
    }
    fprintf(stdout,"The book is not existed in Library !\n");
    return 0;
}
int LIBRARY::checkState(int id){
    // int count = 0;
    fprintf(stdout,"Your bookshelf !\n");
    for(int i=0;i<bookNum;i++){
        int borrower = books[i].getBorrower();
        if(borrower == id){
            fprintf(stdout,"%s\n",books[i].getName().c_str());
            // fprintf(stdout,"the borrower is %d\n",borrower);
            return borrower;
        }
    }
    // fprintf(stdout,"The book is not existed in Library !\n");
    return 1;
}
int LIBRARY::borrow(int id,const char* bookName){
    for(int i=0;i<bookNum;i++){
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
int LIBRARY::borrow(int id,const int book_id){
    if(book_id > bookNum){
        fprintf(stdout,"The book ID is not existed in Library !\n");
        return -1;
    }
    int state = books[book_id-1].getBorrower();
    if(state<0){
        books[book_id-1].borrow(id);
        return id;
    }else {
        fprintf(stdout,"The book is already borrowed !\n");
        return -1;
    }
    
}
int LIBRARY::back(int id,const char* bookName){
    for(int i=0;i<bookNum;i++){
        int state = books[i].matchBack(id,bookName);
        if(state>0){
            books[i].back();
            return id;
        }else if(state == 0){
            fprintf(stdout,"The borrower is not you !\n");
            return -1;
        }
    }
    fprintf(stdout,"The book is not existed in Library !\n");
    return -1;
}
int LIBRARY::back(int id,const int bookId){
    if(bookId > bookNum){
        fprintf(stdout,"The book ID is not existed in Library !\n");
        return -1;
    }    
    int borrower = books[bookId-1].getBorrower();
    if(borrower == id){
        books[bookId-1].back();
        return id;
    }else if(borrower < 0){
        fprintf(stdout,"The book is available in the Library !\n");
        return -1;
    }else{
        fprintf(stdout,"The borrower is not you !\n");
        return -1;
    }
    return -1;
}
int LIBRARY::display(){
    for(int i=0;i<bookNum;i++){
        std::string bn = books[i].getName();
        int state = books[i].getBorrower();
        fprintf(stdout,"%3d. Name: %s \n",i+1,bn.c_str());
        if(state<0) fprintf(stdout,"     State: Avaliable\n");
        else fprintf(stdout,"     State: Borrowed\n");
    }
    return 1;
}