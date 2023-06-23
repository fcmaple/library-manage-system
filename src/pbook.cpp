#include "book.hpp"
PBOOK::PBOOK(fs::directory_entry entry) :BOOK(entry,bookType::PHISICAL){
}
PBOOK::PBOOK():BOOK(bookType::PHISICAL){
}
int PBOOK::read() {
    printf("pbook read !\n");
    return 1;
} 