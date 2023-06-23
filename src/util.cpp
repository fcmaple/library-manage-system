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
            return str.substr(start+1,end-start);
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
    // std::cout << "string : "<<str<<" size "<<str.size()<<std::endl;
    std::string tmp;
    for(int i=0;i<n;i++){
        if(str[i]=='\n' || str[i]=='\r') continue;
        if(str[i]<'0' && str[i]>'9'){
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
        // if(str.substr(i,3)==" e_") return 1;
        if(i+2<n && str.substr(i,3)==" e_") return 1;
        if(count==2 && str[i]=='e') return 1;
        if(str[i]==' ') count ++;
    }
    return 0;
}