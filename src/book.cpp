#include "book.hpp"

BOOK::BOOK(fs::directory_entry entry){
    set(entry);
}
BOOK::BOOK(fs::directory_entry entry,bookType t){
    set(entry);
    type = t;
    // std:: cout << "book con t\n";
}
BOOK::BOOK(){
    state = false;
    borrower = -1;
    strcpy(name,"None");
    strcpy(path,"None");
}
BOOK::BOOK(bookType t){
    state = false;
    borrower = -1;
    strcpy(name,"None");
    strcpy(path,"None");
    type = t;
}
void BOOK::set(fs::directory_entry entry){
    memset(name,'\0',sizeof(name));
    std::string bn = removeEnd(entry.path().filename());
    // strcpy(name,entry.path().filename().c_str());
    strcpy(name,bn.c_str());
    strcpy(path,entry.path().c_str());
    state = false;
    borrower = -1;
    // type = bookType::PHISICAL;
    // printf("Book Name: %s State: %d \n",name,state);

}
int BOOK::match(const char* bookName) const{
    if(strlen(name) == strlen(bookName) && !strcmp(name,bookName) ){
        if(!state)  return 1;
        else return 0;
    }
    return -1;
}
int BOOK::matchBack(int id, const char* bookName) const{
    if(strlen(name) == strlen(bookName) && !strcmp(name,bookName) ){
        if(id==borrower) return 1;
        else return 0;
        // std::cout << id << " " << borrower <<std::endl;
        return borrower;
    }
    return -1;
}
int BOOK::borrow(int id){
    state = true;
    borrower = id;
    // printf("ID: %d book %s borrower %d.\n",id,name,borrower);
    fprintf(stdout,"You borrow the Book \"%s\"\n",name);
    return state;
}
int BOOK::getBorrower() const{
    return borrower;
}
std::string BOOK::getName(){
    // std::cout <<name<<std::endl;
    return std::string(name);
}
int BOOK::back(){
    state = false;
    borrower = -1;
    fprintf(stdout,"You return the Book \"%s\"\n",name);
    return state;
}

int BOOK::showDescription() const{
    std::ifstream file(std::string(this->path));
    if (!file.is_open()) {
        std::cerr << "Failed to open file." << std::endl;
        return 1;
    }
    std::string line;
    while(std::getline(file,line)){
        std::cout << line << std::endl;
    }
    file.close();
    return 1;
}