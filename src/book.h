#ifndef BOOK_H
#define BOOK_H

#define MAX_NAME 100

#include <stdio.h>
#include <string.h>
class BOOK{
public:
    BOOK();
    void set(const char*);
    int match(const char*) const;
    int borrow(int);
    int back();
private:
    char name[MAX_NAME];
    bool state;
    int borrower;
};


#endif