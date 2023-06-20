#ifndef UI_HPP
#define UI_HPP

#include <string>
#include <iostream>
#include <memory>
#include "lms.hpp"
#include "library.hpp"
enum CMD{
	EXIT,REGISTER,MENU,LOGIN,ADD,REMOVE,NOTHING,MYBOOKS,BOOKS,SEARCH,INVALID,
};
class UI{
public:
    UI(int,void*,void*);
    // UI(int,std::shared_ptr<LMS>,std::shared_ptr<LIBRARY>);
    void reset();
    void welcome();
    int run();
    int parse(std::string&);
    const std::pair<std::string,std::string> getUsernameAndPassword();
    int registerUI(const char*,const char*);
    int loginUI(const std::string&,const std::string&);
    CMD translate(std::string&);
private:
    LMS* sharedMemory;
    LIBRARY* libMemory;
    int ID;
};


#endif