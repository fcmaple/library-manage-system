#include "library.hpp"
namespace fs = std::filesystem; 

LIBRARY::LIBRARY(){
    init();
}
LIBRARY::~LIBRARY(){
    sem_close(semaphore);
    sem_unlink("/libSemaphore");
    // std::cout<<"lib de\n";
}
void LIBRARY::init(){
    std::string dirPath = "./data";
    ebookNum = 0;
    pbookNum = 0;
    try {
        for (const fs::directory_entry& entry : fs::directory_iterator(dirPath)) {
            if (entry.is_regular_file()) {
                // std::cout << entry.path() << std::endl;
                std::string bookName = entry.path().filename();
                if(bookName[0] == 'e'){
                    ebooks[ebookNum++].set(entry);
                }
                else
                    pbooks[pbookNum++].set(entry);
            }
            // std::cout << ebookNum << " " << pbookNum << std::endl;
        }
    } catch (const fs::filesystem_error& ex) {
        std::cerr << "Error: " << ex.what() << std::endl;
    }
    semaphore = sem_open("/libSemaphore", O_CREAT | O_RDWR, 0666, 1);
    // fprintf(stdout,"LIBRARY init ,book num: %d !\n",bookNum);
}
void LIBRARY::close(){
    sem_close(semaphore);
    sem_unlink("/libSemaphore");
}
int LIBRARY::wait(){
    sem_wait(semaphore);
    return 1;
}
int LIBRARY::post(){
    sem_post(semaphore);
    return 1;
}
int LIBRARY::search(const char* bookName){
    std::string book_str(bookName);
    // book_str = stringToLower(book_str);
    for(int i=0;i<ebookNum;i++){
        std::string bn = ebooks[i].getName();
        // std:: cout <<book_str<< " "<< stringToLower(bn) <<std::endl;
        if(book_str!=stringToLower(bn)) continue;
        fprintf(stdout,"\nBook: %s\n",bookName);
        fprintf(stdout,"Borrowing status: ");
        if(ebooks[i].getBorrower()<0) fprintf(stdout,"Avaliable\n");
        else fprintf(stdout,"Borrowed\n");
        fprintf(stdout,"Description: \n");
        ebooks[i].showDescription();
        return 1;
    }
    for(int i=0;i<pbookNum;i++){
        std::string bn = pbooks[i].getName();
        // std:: cout <<book_str<< " "<< stringToLower(bn) <<std::endl;
        if(book_str!=stringToLower(bn)) continue;
        fprintf(stdout,"\nBook: %s\n",bookName);
        fprintf(stdout,"Borrowing status: ");
        if(pbooks[i].getBorrower()<0) fprintf(stdout,"Avaliable\n");
        else fprintf(stdout,"Borrowed\n");
        fprintf(stdout,"Description: \n");
        pbooks[i].showDescription();
        return 1;
    }
    fprintf(stdout,"The book is not existed in Library !\n");
    return 0;
}
int LIBRARY::checkState(int id){
    // int count = 0;
    fprintf(stdout,"Your bookshelf !\n");
    for(int i=0;i<ebookNum;i++){
        int borrower = ebooks[i].getBorrower();
        if(borrower == id){
            fprintf(stdout,"%s\n",ebooks[i].getName().c_str());
            // fprintf(stdout,"the borrower is %d\n",borrower);
            return borrower;
        }
    }
    for(int i=0;i<pbookNum;i++){
        int borrower = pbooks[i].getBorrower();
        if(borrower == id){
            fprintf(stdout,"%s\n",pbooks[i].getName().c_str());
            // fprintf(stdout,"the borrower is %d\n",borrower);
            return borrower;
        }
    }
    // fprintf(stdout,"The book is not existed in Library !\n");
    return 1;
}
int LIBRARY::borrow(int id,const char* bookName,int e_flag){
    if(e_flag){
        for(int i=0;i<ebookNum;i++){
            int state = ebooks[i].match(bookName);
            if(state>0){
                ebooks[i].borrow(id);
                printf("state !! %d\n",id);
                return id;
            }else if(state==0){
                fprintf(stdout,"The book is already borrowed !\n");
                return -1;
            }
        }
    }else{
        for(int i=0;i<pbookNum;i++){
            int state = pbooks[i].match(bookName);
            if(state>0){
                pbooks[i].borrow(id);
                printf("state !! %d\n",id);
                return id;
            }else if(state==0){
                fprintf(stdout,"The book is already borrowed !\n");
                return -1;
            }
        }
    }
    fprintf(stdout,"The book is not existed in Library !\n");
    return -1;
}
int LIBRARY::borrow(int id,const int book_id,int e_flag){
    if(e_flag){
        if(book_id > ebookNum){
            fprintf(stdout,"The book ID is not existed in Library !\n");
            return -1;
        }
        int state = ebooks[book_id-1].getBorrower();
        if(state<0){
            ebooks[book_id-1].borrow(id);
            return id;
        }else {
            fprintf(stdout,"The book is already borrowed !\n");
            return -1;
        }
    }else{
        if(book_id > pbookNum){
            fprintf(stdout,"The book ID is not existed in Library !\n");
            return -1;
        }
        int state = pbooks[book_id-1].getBorrower();
        if(state<0){
            pbooks[book_id-1].borrow(id);
            return id;
        }else {
            fprintf(stdout,"The book is already borrowed !\n");
            return -1;
        }
    }   
}
int LIBRARY::back(int id,const char* bookName, int e_flag){
    if(e_flag){
        for(int i=0;i<ebookNum;i++){
            int state = ebooks[i].matchBack(id,bookName);
            if(state>0){
                ebooks[i].back();
                return id;
            }else if(state == 0){
                fprintf(stdout,"The borrower is not you !\n");
                return -1;
            }
        }
    }else{
        for(int i=0;i<pbookNum;i++){
            int state = pbooks[i].matchBack(id,bookName);
            if(state>0){
                pbooks[i].back();
                return id;
            }else if(state == 0){
                fprintf(stdout,"The borrower is not you !\n");
                return -1;
            }
        }
    }

    fprintf(stdout,"The book is not existed in Library !\n");
    return -1;
}
int LIBRARY::back(int id,const int bookId,int e_flag){
    if(e_flag){
        if(bookId > ebookNum){
            fprintf(stdout,"The book ID is not existed in Library !\n");
            return -1;
        }    
        int borrower = ebooks[bookId-1].getBorrower();
        if(borrower == id){
            ebooks[bookId-1].back();
            return id;
        }else if(borrower < 0){
            fprintf(stdout,"The book is available in the Library !\n");
            return -1;
        }else{
            fprintf(stdout,"The borrower is not you !\n");
            return -1;
        }
    }else{
        if(bookId > pbookNum){
            fprintf(stdout,"The book ID is not existed in Library !\n");
            return -1;
        }    
        int borrower = pbooks[bookId-1].getBorrower();
        if(borrower == id){
            pbooks[bookId-1].back();
            return id;
        }else if(borrower < 0){
            fprintf(stdout,"The book is available in the Library !\n");
            return -1;
        }else{
            fprintf(stdout,"The borrower is not you !\n");
            return -1;
        }
    }

    return -1;
}
int LIBRARY::display(){
    // std::cout <<"in\n";
    // std::cout << ebookNum << " " << pbookNum<<std::endl;
    for(int i=0;i<ebookNum;i++){
        // std::cout << i<<std::endl;
        // std::cout<<ebooks[ebookNum-1].getName()<<std::endl;
        std::string bn = ebooks[i].getName();
        int state = ebooks[i].getBorrower();
        // std::cout << bn<< std::endl;
        fprintf(stdout,"%3d. Name: %s \n",i+1,bn.c_str());
        if(state<0) fprintf(stdout,"     State: Avaliable\n");
        else fprintf(stdout,"     State: Borrowed\n");
    }
    for(int i=0;i<pbookNum;i++){
        std::string bn = pbooks[i].getName();
        int state = pbooks[i].getBorrower();
        fprintf(stdout,"%3d. Name: %s \n",i+1,bn.c_str());
        if(state<0) fprintf(stdout,"     State: Avaliable\n");
        else fprintf(stdout,"     State: Borrowed\n");
    }
    return 1;
}

int LIBRARY::getNum(int e_flag) const{
    if(e_flag)  return this->ebookNum;
    return this->pbookNum;
}