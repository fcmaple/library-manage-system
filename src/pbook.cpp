#include "book.hpp"
PBOOK::PBOOK(fs::directory_entry entry) :BOOK(entry,bookType::PHISICAL){
}
PBOOK::PBOOK():BOOK(bookType::PHISICAL){
}
int PBOOK::read() {
    printf("Sorry! \"%s\" is not a e-book, so you can't read online !\n",name);
    return 1;
} 