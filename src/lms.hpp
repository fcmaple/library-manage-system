#ifndef LMS_HPP
#define LMS_HPP

#define MAX_USER 50
#include <semaphore.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
#include <iostream>
#include <string>
#include <map>
#include <algorithm>
#include <utility> 
#include <cstring>     // For string operations

class LMS{
public:
    LMS();
    ~LMS();
    std::string getName(const int) const;
    std::string getPassword(const int) const;
    int wait();
    int post();
    int insert(int,const std::string&,const std::string &);
    int checkLogin(int,const std::string&,const std::string &);
    // int login(int,const std::string&,const std::string &);
    void reset();

private:
    char username[MAX_USER][20];
    char password[MAX_USER][20];
    unsigned int userIdx;
    sem_t* semaphore;
};
#endif