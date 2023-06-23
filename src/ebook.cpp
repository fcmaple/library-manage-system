#include "book.hpp"

EBOOK:: EBOOK(fs::directory_entry entry): BOOK(entry){
    bookLabel = 0;
}
EBOOK:: EBOOK():BOOK(bookType::ELECTRONIC)
{
    // printf("ebook\n");
    bookLabel = 0;
}
int EBOOK::read(const std::string& name) {
    // printf("ebook read !\n");
    // std::cout << name << std::endl;

    std::ifstream inputFile(name);
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