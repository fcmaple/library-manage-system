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
    int start = -1;
    int end = -1;
    for(int i=0;i<n;i++){
        if(str[i]==' ' && start<0){
            start = i;
        }else if(str[i]==' '&&start>=0){
            end = i;
        }
        if(start>=0 && end >=0){
            return str.substr(start+1,end-start-1);
        }
    }
    if(start>=0) return str.substr(start+1);
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
    std::string tmp;
    for(int i=0;i<n;i++){
        if(str[i]=='\n' || str[i]=='\r' || str[i]=='\t') continue;
        if(!std::isdigit(str[i])){
            return -1;
        }
        tmp += str[i];
    }
    return std::atoi(tmp.c_str());
}
int checkE(const std::string& str){
    int n = str.size();
    int count = 0;
    for(int i=0;i<n;i++){
        if(i+2<n && str.substr(i,3)==" e_") return 1;
        if(count==2 && str[i]=='e') return 1;
        if(str[i]==' ') count ++;
    }
    return 0;
}