#ifndef LMS_HPP
#define LMS_HPP

#define MAX_USER 50

#include <iostream>
#include <string>
#include <map>
#include <algorithm>
#include <utility> 
#include <cstring>     // For string operations

struct LMS {
    char username[MAX_USER][20];
    char password[MAX_USER][20];
    unsigned int userIdx;
    void reset();
};
#endif