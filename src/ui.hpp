#ifndef UI_HPP
#define UI_HPP

#include <string>
#include <iostream>
#include <memory>
#include <stdlib.h>
#include "lms.hpp"
#include "library.hpp"

enum CMD{
	EXIT,REGISTER,MENU,LOGIN,ADD,REMOVE,NOTHING,MYBOOKS,BOOKS,SEARCH,INVALID,
};
class UI{
public:
    UI(int,std::shared_ptr<LMS>,std::shared_ptr<LIBRARY>);
    // UI(int,std::shared_ptr<LMS>,void*);
    void reset();
    void welcome();
    int run();
    int parse(std::string&);
    const std::pair<std::string,std::string> getUsernameAndPassword();
    int registerUI(const char*,const char*);
    int loginUI(const std::string&,const std::string&);
    CMD translate(std::string&);
private:
    std::shared_ptr<LMS> sharedMemory;
    std::shared_ptr<LIBRARY> libMemory;
    int ID;
};


#endif