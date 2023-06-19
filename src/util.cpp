#include <iostream>

std::string stringToLower(std::string& str){
    for(char& ch:str){
        if(!isalpha(ch)) continue;
        ch = std::tolower(ch);
    }
    return str;
}
std::string getBookName(std::string& str){
    int n = str.size();
    for(int i=0;i<n;i++){
        if(str[i]==' ' && i<=(int)str.size()-1){
            return str.substr(i+1);
        }
    }
    fprintf(stdout,"Can't get the book name!\n");
    return "";
}
std::string removeEnd(const std::string& str){
    int n = str.size();
    for(int i=0;i<n;i++){
        if(str[i]=='.') return str.substr(0,i);
    }
    return str;
}
int stringToint(const std::string& str){
    int n = str.size();
    for(int i=0;i<n;i++){
        if(!std::isdigit(str[i]))
            return -1;
    }
    return std::atoi(str.c_str());
}