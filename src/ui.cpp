#include "ui.hpp"
#include "server.hpp"
#include "lms.hpp"
#include "util.hpp"

UI::UI(int fd,void* shm,void* library):ID(-1){
    dup2(fd,STDIN_FILENO);
    dup2(fd,STDOUT_FILENO);
    dup2(fd,STDERR_FILENO);
    this->sharedMemory = static_cast<LMS*>(shm);
    this->libMemory = static_cast<LIBRARY*>(library);
}

int UI::registerUI(const char* username,const char* password){
    LMS* sharedData = this->sharedMemory;
    for(int i=0;i<MAX_USER;i++){
        if(sharedData->getName(i)==std::string(username)){
            fprintf(stdout,"username is already existed !\n");
            return -1;
        }
    }
    for(int i=0;i<MAX_USER;i++){
        if(sharedData->getName(i).size()==0){
            sharedData->insert(i,username,password);
            return i;
        }
    }

    return -1;
}
int UI::loginUI(const std::string& username,const std::string& password){
    for(int i=0;i<MAX_USER;i++){
        if(sharedMemory->checkLogin(i,username,password)>=0){
            this->ID = i;
            return i;
        }
    }
    // sharedMemory->post();
    fprintf(stdout,"User is not exited\n");
    return -1;
}
CMD UI::translate(std::string& command){
    std::string cmd = stringToLower(command);
    if(cmd.substr(0,4) == "exit"){
        return CMD::EXIT;
    }else if(cmd.substr(0,8) == "register"){
        return CMD::REGISTER;
    }else if(cmd.substr(0,4) == "menu"){
        return CMD::MENU;
    }else if(cmd.substr(0,5) == "login"){
        return CMD::LOGIN;
    }else if(cmd.substr(0,3) == "add"){
        return CMD::ADD;
    }else if(cmd.substr(0,2) == "rm"){
        return CMD::REMOVE;
    }else if(cmd.size()==0){
        if(readingBook.size()) return CMD::READING;
        return CMD::NOTHING;
    }else if(cmd.substr(0,7) == "mybooks"){
        return CMD::MYBOOKS;
    }else if(cmd.substr(0,5) == "books"){
        return CMD::BOOKS;
    }else if(cmd.substr(0,6) == "search"){
        return CMD::SEARCH;
    }else if(cmd.substr(0,4) == "read"){
        return CMD::READ;
    }else{
        fprintf(stdout,"Invalid Command\n");
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
            sharedMemory->wait();
            if(this->registerUI(info.first.c_str(),info.second.c_str())<0){
                fprintf(stderr,"Register Error!\n");
                return -1;
            }
            sharedMemory->post();
            break;
        }
        case CMD::MENU:{
            fprintf(stdout,"login    : To log in to your personal account. Usage: login\n");
            fprintf(stdout,"register : To register a new account for the Library Management System (LMS). Usage: register\n");
            fprintf(stdout,"add      : Add a book to your personal borrow bookshelf. Usage: add [book name/book id] [e/p]\n");
            fprintf(stdout,"rm       : Remove a book from your personal borrow bookshelf. Usage: rm [book name/book id] [e/p]\n");
            fprintf(stdout,"search   : Search the specified book. Usage: search [book name]\n");
            fprintf(stdout,"read     : Read the book in personal bookself. Usage: read [book name/book id] [e/p]\n");
            fprintf(stdout,"books    : Display all book in Library. Usage: books\n");
            fprintf(stdout,"mybooks  : Display all book in personal bookshelf. Usage: mybooks\n");
            fprintf(stdout,"exit     : Logout and exit the system. Usage: exit\n");
            break;
        }
        case CMD::LOGIN:{
            std::pair<std::string,std::string> info = getUsernameAndPassword();
            sharedMemory->wait();
            if(this->loginUI(info.first,info.second)<0){
                fprintf(stderr,"Login Error !\n");
            }
            sharedMemory->post();
            break;
        }
        case CMD::ADD:{
            if(ID<0) {
                fprintf(stdout,"You need to login to add the book in your bookself.\n");
                break;
            }
            std::string bookName = getBookName(cmd);
            if(!bookName.size()) break;
            int bookId = stringToint(bookName);
            int e_flag = checkE(cmd);
            libMemory->wait();
            if(bookId<0){
                libMemory->borrow(this->ID,bookName.c_str(),e_flag);
            }else
                libMemory->borrow(this->ID,bookId,e_flag);
            libMemory->post();
            break;
        }
        case CMD::REMOVE:{
            if(ID<0) {
                fprintf(stdout,"You need to login to remove the book in your bookself.\n");
                break;
            }
            std::string bookName = getBookName(cmd);
            if(!bookName.size()) break;
            int bookId = stringToint(bookName);
            int e_flag = checkE(cmd);
            libMemory->wait();
            if(bookId<0)
                libMemory->back(this->ID,bookName.c_str(),e_flag);
            else
                libMemory->back(this->ID,bookId,e_flag);
            libMemory->post();
            break;
        }
        case CMD::MYBOOKS:{
            if(ID<0) {
                fprintf(stdout,"You need to login to check the book in your bookself.\n");
                break;
            }
            libMemory->wait();
            libMemory->checkState(this->ID);
            libMemory->post();

            break;
        }
        case CMD::SEARCH:{
            std::string bookName = getBookName(cmd);
            if(!bookName.size()) break;
            libMemory->wait();
            libMemory->search(bookName.c_str());
            libMemory->post();
            break;
        }
        case CMD::BOOKS:{
            libMemory->display();
            break;
        }
        case CMD::READ:{
            if(ID<0) {
                fprintf(stdout,"You need to login to read the book in your bookself.\n");
                break;
            }
            std::string bookName = getBookName(cmd);
            if(!bookName.size()) break;
            int bookId = stringToint(bookName);
            int e_flag = checkE(cmd);
            libMemory->wait();
            if(bookId < 0){
                libMemory->read(this->ID,bookName.c_str(),e_flag);
            }else
                libMemory->read(this->ID,bookId,e_flag);
            readingBook = bookName;
            libMemory->post();
            break;
        }
        case CMD::READING:{
            if(ID<0) {
                fprintf(stdout,"You need to login to read the book in your bookself.\n");
                break;
            }
            std::string bookName = readingBook;
            int bookId = stringToint(bookName);
            libMemory->wait();
            if(bookId < 0){
                libMemory->read(this->ID,bookName.c_str(),1);
            }else
                libMemory->read(this->ID,bookId,1);
            libMemory->post();
            break;
        }
        default:
            break;
    }
    if(command!=CMD::READING && command!=CMD::READ){
        readingBook = "";
    }
    return 1;
}
void UI::welcome(){
    int res = system("figlet -w 200 Library-System");
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
    return 1;
}
