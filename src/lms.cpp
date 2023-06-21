#include "lms.hpp"
LMS::LMS(){
    reset();
    // std::cout <<"lms con\n";
}
void LMS::reset(){
    for(int i=0;i<MAX_USER;i++){
        memset(username[i],'\0',sizeof(username[i]));
        memset(password[i],'\0',sizeof(password[i]));
    }
    semaphore = sem_open("/lmsSem", O_CREAT | O_RDWR, 0666, 1);
}
LMS::~LMS(){
    // std::cout <<"lms de\n";
    sem_close(semaphore);
    sem_unlink("/lmsSem");
}
std::string LMS::getName(const int id) const{

    return std::string(username[id]);
}
std::string LMS::getPassword(const int id) const{
    return std::string(username[id]);
}
int LMS::wait(){
    sem_wait(semaphore);
    return 1;
}
int LMS::post(){
    sem_post(semaphore);
    return 1;
}
int LMS::insert(int id,const std::string& userName,const std::string& passWord){
    try
    {
        strcpy(this->username[id],userName.c_str());
        strcpy(this->password[id],passWord.c_str());
        printf("Register success ! your username : %s, password : %s\n",username[id],password[id]);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    
    return 1;
}
int LMS::checkLogin(int id,const std::string& userName,const std::string& passWord){
    
    try
    {
        if(strlen(username[id])==strlen(userName.c_str()) && !strcmp(username[id],userName.c_str()) &&\
            strlen(password[id])==strlen(passWord.c_str()) && !strcmp(password[id],passWord.c_str())){
                fprintf(stdout,"Welcome Back, %s!\n",username[id]);
                return id;
        }
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    return -1;   
}
