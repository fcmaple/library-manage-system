#ifndef UI_H
#define UI_H

#include <string>
#include <iostream>
#include <memory>
#include "lms.h"
#include "library.h"
enum CMD{
	EXIT,REGISTER,MENU,LOGIN,ADD,REMOVE,NOTHING,MYBOOKS,BOOKS,SEARCH,INVALID,
};
class UI{
public:
    UI(int,void*,void*);
    void reset();
    void welcome();
    int run();
    int parse(std::string&);
    const std::pair<std::string,std::string> getUsernameAndPassword();
    int registerUI(const char*,const char*);
    int loginUI(const char*,const char*) const;
    CMD translate(std::string&);
private:
    LMS* sharedMemory;
    LIBRARY* libMemory;
    int ID;
};


#endif