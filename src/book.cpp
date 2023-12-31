#include "book.hpp"

BOOK::BOOK(fs::directory_entry entry){
    set(entry);
}
BOOK::BOOK(fs::directory_entry entry,bookType t){
    set(entry);
    type = t;
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
    strcpy(name,bn.c_str());
    strcpy(path,entry.path().c_str());
    state = false;
    borrower = -1;

}
int BOOK::match(const char* bookName) const{
    if(strlen(name) == strlen(bookName)){
        for(int i=0;i<(int)strlen(name);i++){
            if(name[i]!=bookName[i] && bookName[i]-'a'+'A' != name[i]) return -1;
        }
        if(!state)  return 1;
        else return 0;
    }
    return -1;
}
int BOOK::matchBack(int id, const char* bookName) const{
    if(strlen(name) == strlen(bookName) ){
        for(int i=0;i<(int)strlen(name);i++){
            if(name[i]!=bookName[i] && bookName[i]-'a'+'A' != name[i]) return -1;
        }
        if(id==borrower) return 1;
        else return 0;
    }
    return -1;
}
int BOOK::borrow(int id){
    state = true;
    borrower = id;
    fprintf(stdout,"You borrow the Book \"%s\"\n",name);
    return state;
}
int BOOK::getBorrower() const{
    return borrower;
}
std::string BOOK::getName() const{
    return std::string(name);
}
std::string BOOK::getPath() const{
    return std::string(path);
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
    std::getline(file,line);
    std::cout << line << std::endl;
    
    file.close();
    return 1;
}
int BOOK::read(){
    std::cout << "book !\n";
    return 1;
}