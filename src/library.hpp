#ifndef LIBRARY_H
#define LIBRARY_H

#define MAX_BOOKS 100


#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <iostream>
#include <filesystem>

#include "book.hpp"
#include "server.hpp"
#include "util.hpp"
class LIBRARY{
public:
    LIBRARY();
    void init();
    int borrow(int ,const char*);
    int borrow(int ,const int );
    int back(int,const char*);
    int back(int,const int);
    int checkState(int);
    int search(const char*);
    int display();
    int getNum() const;
private:
    BOOK books[MAX_BOOKS];
    int bookNum;

};
#endif