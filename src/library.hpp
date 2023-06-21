#ifndef LIBRARY_HPP
#define LIBRARY_HPP

#define MAX_BOOKS 100


#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <iostream>
#include <filesystem>
#include <semaphore.h>
#include <unistd.h>    // For POSIX constants and types
#include <fcntl.h>  
#include "book.hpp"
// #include "server.hpp"
#include "util.hpp"
class LIBRARY{
public:
    LIBRARY();
    ~LIBRARY();
    void init();
    int borrow(int ,const char*,int);
    int borrow(int ,const int ,int);
    int back(int,const char*,int);
    int back(int,const int,int);
    int checkState(int);
    int search(const char*);
    int display();
    int getNum(int) const;
    void close();
    int wait();
    int post();
private:
    EBOOK ebooks[MAX_BOOKS];
    PBOOK pbooks[MAX_BOOKS];
    int ebookNum;
    int pbookNum;
    sem_t* semaphore;

};
#endif