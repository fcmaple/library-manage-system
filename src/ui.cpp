#include "ui.h"
#include "server.h"
#include "lms.h"
#include "util.h"
UI::UI(int fd,void* shm,void* library):ID(-1){
    dup2(fd,STDIN_FILENO);
    dup2(fd,STDOUT_FILENO);
    dup2(fd,STDERR_FILENO);
    this->sharedMemory = static_cast<LMS*>(shm);
    this->libMemory = static_cast<LIBRARY*>(library);
    // LMS* shared_data = static_cast<LMS*>(shm);
    // strcpy(shared_data->username[shared_data->userIdx],"teresa");
    // std::cout << "Data in UI  shared memory: " << shared_data->username[shared_data->userIdx++] << " " << shared_data->userIdx << std::endl;  // Read data from the shared memory
}
int UI::registerUI(const char* username,const char* password){
    LMS* sharedData = this->sharedMemory;
    for(int i=0;i<MAX_USER;i++){
        if(strlen(sharedData->username[i])==0){
            this->ID = i;
            strcpy(sharedData->username[i],username);
            strcpy(sharedData->password[i],password);
            printf("Register success ! your username : %s, password : %s\n",sharedData->username[i],sharedData->password[i]);
            return 1;
        }
    }
    return -1;
}
int UI::loginUI(const char* username,const char* password) const {
    for(int i=0;i<MAX_USER;i++){
        if(strlen(username)==strlen(sharedMemory->username[i]) && !strcmp(sharedMemory->username[i],username) &&\
            strlen(password)==strlen(sharedMemory->password[i]) && !strcmp(sharedMemory->password[i],password)){
                fprintf(stdout,"Welcome Back, %s !\n",username);
                return i;
        }
    }
    fprintf(stdout,"User is not exited\n");
    return 0;
}
CMD UI::translate(std::string& command){
    std::string cmd = stringToLower(command);
    if(cmd == "exit"){
        return CMD::EXIT;
    }else if(cmd == "register"){
        return CMD::REGISTER;
    }else if(cmd == "menu"){
        return CMD::MENU;
    }else if(cmd == "login"){
        return CMD::LOGIN;
    }else if(cmd.substr(0,3) == "add"){
        return CMD::ADD;
    }else if(cmd.substr(0,6) == "remove"){
        return CMD::REMOVE;
    }else if(cmd.size()==0){
        return CMD::NOTHING;
    }else{
        fprintf(stderr,"Invalid Command\n");
        return CMD::INVALID;
    }
}
const std::pair<std::string,std::string> UI::getUsernameAndPassword(){
    std::string name,pwd;
    std::cout << "Please input your name : " ;
    std::getline(std::cin,name);
    std::cout << "Please input your password : " ;
    std::getline(std::cin,pwd);
    return {name,pwd};
}
int UI::parse(std::string& cmd){
    CMD command = translate(cmd);
    switch (command)
    {
        case CMD::EXIT:{
            return 0;
        }
        case CMD::REGISTER:{
            std::pair<std::string,std::string> info = getUsernameAndPassword();
            if(this->registerUI(info.first.c_str(),info.second.c_str())<0){
                fprintf(stderr,"Register Error!\n");
                return -1;
            }
            break;
        }
        case CMD::MENU:{
            fprintf(stdout,"login    : To log in to your personal account.\n");
            fprintf(stdout,"register : To register a new account for the Library Management System (LMS).\n");
            fprintf(stdout,"add      : Add a book to your personal borrow bookshelf.\n");
            fprintf(stdout,"rm       : Remove a book from your personal borrow bookshelf.\n");
            fprintf(stdout,"search   : Search the specified book.\n");
            fprintf(stdout,"exit     : Logout and exit the system.\n");
            break;
        }
        case CMD::LOGIN:{
            std::pair<std::string,std::string> info = getUsernameAndPassword();
            if(this->loginUI(info.first.c_str(),info.second.c_str())<0){
                fprintf(stderr,"Login Error !\n");
            }
            break;
        }
        case CMD::ADD:{
            if(ID<0) {
                fprintf(stdout,"You need to login to add the book in your bookself. !\n");
                break;
            }
            std::string bookName = getBookName(cmd);
            if(!bookName.size()) break;
            libMemory->borrow(this->ID,bookName.c_str());
        }
        case CMD::REMOVE:{
            if(ID<0) {
                fprintf(stdout,"You need to login to remove the book in your bookself. !\n");
                break;
            }
            std::string bookName = getBookName(cmd);
            if(!bookName.size()) break;
            libMemory->back(this->ID,bookName.c_str());
        }
        default:
            break;
    }
    return 1;
}
void UI::welcome(){
    printf("-------------------------------------\n");
    printf("---   Library Management System   ---\n");
    printf("-------------------------------------\n");
    printf("Welcome to Library Management System !\n");
    printf("Input \"menu\", the terminal will display all the functions and descriptions of the system !\n");
}
int UI::run(){
    welcome();
    while(1){
        std::string cmd;
        std::cout << "LMS> " ;
        std::getline(std::cin,cmd);
        if(!parse(cmd))
            break;
    }
    std::cout << "exit !\n";
    return 1;
}