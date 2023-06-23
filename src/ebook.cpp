#include "book.hpp"

EBOOK:: EBOOK(fs::directory_entry entry): BOOK(entry){
    bookLabel = 0;
}
EBOOK:: EBOOK():BOOK(bookType::ELECTRONIC)
{
    // printf("ebook\n");
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
    // printf("ebook read !\n");
    std::ifstream inputFile(path);
    if (!inputFile) {
        std::cerr << "Failed to open the file." << std::endl;
        return -1;
    }
    inputFile.seekg(0, std::ios::beg);
    std::streampos beginPosition = inputFile.tellg();
    inputFile.seekg(bookLabel, std::ios::beg);

    int t =3;
    std::string line;
    
    while(t--){
        std::getline(inputFile,line);
        std::cout << line << std::endl;
    }
    std::streampos currentPosition = inputFile.tellg();
    this->bookLabel = currentPosition - beginPosition;
    inputFile.close();
    return 1;
} 
