#ifndef BOOK_H
#define BOOK_H

#define MAX_NAME 100

#include <stdio.h>
#include <string.h>

#include <iostream>
#include <string>
#include <filesystem>
#include <fstream>

#include "util.h"
namespace fs = std::filesystem;
enum bookType{
    ELECTRONIC,PHISICAL
};

class BOOK{
public:
    BOOK();
    // void set(const char*);
    void set(fs::directory_entry);
    int match(const char*) const;
    int matchBack(int,const char*) const;
    int borrow(int);
    int back();
    int getBorrower() const;
    std::string getName();
    int showDescription() const;
private:
    char name[MAX_NAME];
    char path[MAX_NAME];
    bool state;
    int borrower;
    bookType type;
    
};

#endif