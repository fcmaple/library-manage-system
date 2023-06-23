#include "ui.hpp"
#include "server.hpp"
#include "lms.hpp"
#include "util.hpp"
// #include "library.hpp"

// UI::UI(int fd,std::shared_ptr<LMS> shm,std::shared_ptr<LIBRARY> library):ID(-1){
//     dup2(fd,STDIN_FILENO);
//     dup2(fd,STDOUT_FILENO);
//     dup2(fd,STDERR_FILENO);
//     // this->sharedMemory = static_cast<LMS*>(shm);
//     sharedMemory = shm;
//     // this->libMemory = static_cast<LIBRARY*>(library);
//     libMemory = library;
//     // std::cout <<"con ui\n";
//     // LMS* shared_data = static_cast<LMS*>(shm);
//     // strcpy(shared_data->username[shared_data->userIdx],"teresa");
//     // std::cout << "Data in UI  shared memory: " << shared_data->username[shared_data->userIdx++] << " " << shared_data->userIdx << std::endl;  // Read data from the shared memory
// }
UI::UI(int fd,void* shm,void* library):ID(-1){
    dup2(fd,STDIN_FILENO);
    dup2(fd,STDOUT_FILENO);
    dup2(fd,STDERR_FILENO);
    this->sharedMemory = static_cast<LMS*>(shm);
    // sharedMemory = shm;
    this->libMemory = static_cast<LIBRARY*>(library);
    // libMemory = library;
    // std::cout <<"con ui\n";
    // LMS* shared_data = static_cast<LMS*>(shm);
    // strcpy(shared_data->username[shared_data->userIdx],"teresa");
    // std::cout << "Data in UI  shared memory: " << shared_data->username[shared_data->userIdx++] << " " << shared_data->userIdx << std::endl;  // Read data from the shared memory
}

int UI::registerUI(const char* username,const char* password){
    LMS* sharedData = this->sharedMemory;
    // std::cout << "register \n";
    sharedData->wait();
    for(int i=0;i<MAX_USER;i++){
        if(sharedData->getName(i)==std::string(username)){
            fprintf(stdout,"username is already existed !\n");
            sharedData->post();
            return -1;
        }
    }
    for(int i=0;i<MAX_USER;i++){
        // std::cout<< i << std::endl;
        // std::cout << sharedData->getName(i).size() << std::endl;
        if(sharedData->getName(i).size()==0){
            sharedData->insert(i,username,password);
            // sem_post(sharedData->semaphore);
            sharedData->post();
            return i;
        }
    }
    sharedData->post();

    return -1;
}
int UI::loginUI(const std::string& username,const std::string& password){
    for(int i=0;i<MAX_USER;i++){
        if(sharedMemory->checkLogin(i,username,password)>=0){
            this->ID = i;
            // std::cout << i<< std::endl;
            return i;
        }
    }
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
            fprintf(stdout,"books    : Display all book in Library.\n");
            fprintf(stdout,"mybooks  : Display all book in personal bookshelf.\n");
            fprintf(stdout,"exit     : Logout and exit the system.\n");
            break;
        }
        case CMD::LOGIN:{
            std::pair<std::string,std::string> info = getUsernameAndPassword();
            if(this->loginUI(info.first,info.second)<0){
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
            // std::cout << "bookname :"<<bookName << std::endl;
            if(!bookName.size()) break;
            int bookId = stringToint(bookName);
            // std::cout << "id : "<<bookId<<std::endl;
            int e_flag = checkE(cmd);
            // std::cout << "flag: " <<e_flag<<std::endl; 
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
                fprintf(stdout,"You need to login to remove the book in your bookself. !\n");
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
                fprintf(stdout,"You need to login to check the book in your bookself. !\n");
                break;
            }
            libMemory->checkState(this->ID);

            break;
        }
        case CMD::SEARCH:{
            std::string bookName = getBookName(cmd);
            if(!bookName.size()) break;
            libMemory->search(bookName.c_str());
            break;
        }
        case CMD::BOOKS:{
            // std::cout << "books\n";
            libMemory->display();
            break;
        }
        case CMD::READ:{
            if(ID<0) {
                fprintf(stdout,"You need to login to read the book in your bookself. !\n");
                break;
            }
            std::string bookName = getBookName(cmd);
            if(!bookName.size()) break;
            int bookId = stringToint(bookName);
            int e_flag = checkE(cmd);
            std::cout << "id : "<<bookId<<std::endl;
            if(bookId < 0)
                libMemory->read(this->ID,bookName.c_str(),e_flag);
            else
                libMemory->read(this->ID,bookId,e_flag);
            break;
        }
        default:
            break;
    }
    return 1;
}
void UI::welcome(){
    int res = system("figlet -w 200 Library-System");
    // printf("-------------------------------------\n");
    // printf("---   Library Management System   ---\n");
    // printf("-------------------------------------\n");
    // printf("Welcome to Library Management System !\n");
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

// 熱門書 （）
// 子類別： 實體書 電子書 有聲書 漫畫 CD 等等
// 電子書： 可直接觀看 （頁數 .. 等）(Harry potter)