#include <iostream>

std::string stringToLower(std::string& str){
    for(char& ch:str){
        if(!isalpha(ch)) continue;
        ch = std::tolower(ch);
    }
    return str;
}
std::string getBookName(std::string& str){
    for(int i=0;i<(int)str.size();i++){
        if(str[i]==' ' && i<=(int)str.size()-1){
            return str.substr(i+1);
        }
    }
    fprintf(stdout,"Can't get the book name!\n");
    return "";
}