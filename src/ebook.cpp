#include "book.hpp"

EBOOK:: EBOOK(fs::directory_entry entry): BOOK(entry){
}
EBOOK:: EBOOK():BOOK(bookType::ELECTRONIC)
{
    // printf("ebook\n");
}
int EBOOK::read() {
    printf("ebook read !\n");
    return 1;
} 