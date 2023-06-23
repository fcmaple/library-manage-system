#ifndef BOOK_H
#define BOOK_H

#define MAX_NAME 100

#include <stdio.h>
#include <string.h>

#include <iostream>
#include <string>
#include <filesystem>
#include <fstream>

#include "util.hpp"
namespace fs = std::filesystem;
enum bookType{
    ELECTRONIC,PHISICAL
};

class BOOK{
public:
    BOOK(fs::directory_entry);
    BOOK(fs::directory_entry,bookType);
    BOOK();
    BOOK(bookType);
    // void set(const char*);
    void set(fs::directory_entry);
    int match(const char*) const;
    int matchBack(int,const char*) const;
    int borrow(int);
    virtual int back();
    int getBorrower() const;
    bookType getType() const;
    std::string getName() const;
    std::string getPath() const;
    int showDescription() const;
    virtual int read();
protected:
    char name[MAX_NAME];
    char path[MAX_NAME];
    bool state;
    int borrower;
    bookType type;
    
};
class EBOOK:public BOOK
{
private:
    /* data */
    int bookLabel;
public:
    EBOOK(fs::directory_entry);
    EBOOK();
    virtual int back() override;
    virtual int read()  override;
};
class PBOOK:public BOOK
{
private:
    /* data */
public:
    PBOOK(fs::directory_entry);
    PBOOK();
    virtual int read()  override;

};



#endif