#ifndef LIBRARY_H
#define LIBRARY_H

#define MAX_BOOKS 100


#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "book.h"
#include "server.h"
class LIBRARY{
public:
    LIBRARY();
    void init();
    int borrow(int ,const char*);
    int back(int,const char*);
private:
    BOOK books[MAX_BOOKS];
};
#endif