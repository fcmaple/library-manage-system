#include "book.hpp"

EBOOK:: EBOOK(fs::directory_entry entry): BOOK(entry){
    bookLabel = 0;
}
EBOOK:: EBOOK():BOOK(bookType::ELECTRONIC)
{
    bookLabel = 0;
}
int EBOOK::back(){
    state = false;
    borrower = -1;
    bookLabel = 0;
    fprintf(stdout,"You return the e-Book \"%s\"\n",name);
    return state;
}

int EBOOK::read() {
    std::ifstream inputFile(path);
    if (!inputFile) {
        std::cerr << "Failed to open the file." << std::endl;
        return -1;
    }
    inputFile.seekg(0, std::ios::beg);
    std::streampos beginPosition = inputFile.tellg();
    inputFile.seekg(bookLabel, std::ios::beg);
    std::streampos currentPosition = inputFile.tellg();

    int t =3;
    std::string line;
    
    while(t--){
        currentPosition = inputFile.tellg();
        if(currentPosition<0){
            break;
        }
        std::getline(inputFile,line);
        std::cout << line << std::endl;
    }
    currentPosition = inputFile.tellg();
    if(currentPosition < 0){
        fprintf(stdout,"---------- END ----------\n");
        this->bookLabel = beginPosition;
    }
    else
        this->bookLabel = currentPosition - beginPosition;
    inputFile.close();
    return 1;
} 
