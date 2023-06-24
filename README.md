# Library-Manage-System
Create a command-line-based library management system using C++. The system should allow users to manage a library's collection of books. Users should be able to add, remove, and search for books, as well as perform other library-related functions.
## How to use
### Server
```shell=
make && make run [Port]
```
### Client
```shell=
nc [server IP]:[Port]
```
Notic: The default server IP is `localhost`, if you want to set the server IP to public, modify the macro `PUBLIC` in `server.hpp`

## Specification
### Register
The user need to register to be a member when the user connect to library-management-system.
```shell=
Usage: register
```  
### Login
```shell=
Usage: login
```
### Borrow
When the user want to borrow a e-book/p-book.
You can use command `books` to see all book id.
`e` means the book type is e-book, `p` means the book type is p-book.
```shell=
Usage: add [book name/book id] [e/p]
```
### Return
When the user want to borrow a e-book/p-book.
```shell=
Usage: rm [book name/book id] [e/p]
```
### Read
When the user want to read a e-book.
You can input "" to keep reading after command `read`.
```shell=
Usage: read [book name/book id] [e/p]
```
### Search
When the user want to check the state of specified book.
```shell=
Usage: search [book name]
```
### Display personal bookself / all books
When the user want to see all book in the library-management-system.
```shell=
Usage: books
```
When the user just want to check how many books in the personal bookshelf.
```shell=
Usage: mybooks
```

## Implementation detail
### Server

On the server side, I establish a socket server. When an external connection is made, I create a new process using `fork()` to handle that external connection. The `stdin`, `stdout`, and `stderr` of that process can be redirected to the corresponding socket file descriptor.

To handle data that needs to be shared among multiple processes, such as library books and account/password management, I create shared memory. This allows different processes to access and modify the shared data. To deal with synchronization issues when accessing the shared data,I use `semaphores`.

### Client

On the client side, I have written a UI class specifically designed to handle client requests and generate responses based on those requests.
