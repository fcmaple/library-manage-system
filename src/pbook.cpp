#include "book.hpp"
PBOOK::PBOOK(fs::directory_entry entry) :BOOK(entry,bookType::PHISICAL){
}
PBOOK::PBOOK():BOOK(bookType::PHISICAL){
}
int PBOOK::read(const std::string& str) {
    printf("pbook read !\n");
    return 1;
} 