#include "test_lms.hpp"
// The test fixture class
class MyTestFixture : public ::testing::Test {
protected:
    void SetUp() override {
        lib->init();
        // Set up any resources needed for the tests
    }

    void TearDown() override {
        // Clean up any resources used by the tests
    }

    // Declare any member variables needed for the tests
    int myVariable;
    int id = 1;
    std::shared_ptr<LIBRARY> lib = std::make_shared<LIBRARY>();
};

TEST_F(MyTestFixture, BaseTest) {
    // ...
    myVariable = 42;
    ASSERT_EQ(myVariable, 42);
}
// Test case using the fixture
TEST_F(MyTestFixture, DisplayTest) {
#if BLOCKSTDOUT
    ::testing::internal::CaptureStdout();
#endif
    // Inside this test, you can access the fixture's member variables and methods
    ASSERT_EQ(lib->display(),1);
#if BLOCKSTDOUT
    std::string output = ::testing::internal::GetCapturedStdout();
#endif

    // std::cout << output << std::endl;
}

TEST_F(MyTestFixture, SearchTest) {
#if BLOCKSTDOUT
    ::testing::internal::CaptureStdout();
#endif
    std::string testName = "";
    ASSERT_EQ(lib->search(testName.c_str()),0);
    testName = "workout";
    ASSERT_EQ(lib->search(testName.c_str()),1);
#if BLOCKSTDOUT
    std::string output = ::testing::internal::GetCapturedStdout();
#endif
}

TEST_F(MyTestFixture, CheckStateTest) {
#if BLOCKSTDOUT
    ::testing::internal::CaptureStdout();
#endif
    ASSERT_EQ(lib->checkState(id),1);
#if BLOCKSTDOUT
    std::string output = ::testing::internal::GetCapturedStdout();
#endif
}
TEST_F(MyTestFixture, BorrowTestByName) {
    // ...
#if BLOCKSTDOUT
    ::testing::internal::CaptureStdout();
#endif
    std::string testName = "aaa";
    ASSERT_EQ(lib->borrow(id,testName.c_str()),-1);
    testName = "WorkOut";
    ASSERT_EQ(lib->borrow(id,testName.c_str()),id);
    ASSERT_EQ(lib->borrow(id,testName.c_str()),-1);
#if BLOCKSTDOUT
    std::string output = ::testing::internal::GetCapturedStdout();
#endif
    
}
TEST_F(MyTestFixture, BorrowTestByID) {
#if BLOCKSTDOUT
    ::testing::internal::CaptureStdout();
#endif
    int bookId = lib->getNum();
    ASSERT_EQ(lib->borrow(id,bookId),id);
    ASSERT_EQ(lib->borrow(id,bookId),-1);
    
    bookId = lib->getNum()+1;
    ASSERT_EQ(lib->borrow(id,bookId),-1);

#if BLOCKSTDOUT
    std::string output = ::testing::internal::GetCapturedStdout();
#endif
}
TEST_F(MyTestFixture, BackTestByName) {
#if BLOCKSTDOUT
    ::testing::internal::CaptureStdout();
#endif
    std::string testName = "aaa";
    ASSERT_EQ(lib->back(id,testName.c_str()),-1);
    testName = "WorkOut";
    ASSERT_EQ(lib->borrow(id,testName.c_str()),id);
    ASSERT_EQ(lib->back(id,testName.c_str()),id);
    ASSERT_EQ(lib->back(id,testName.c_str()),-1);
#if BLOCKSTDOUT
    std::string output = ::testing::internal::GetCapturedStdout();
#endif
}
TEST_F(MyTestFixture, BackTestByID) {
#if BLOCKSTDOUT
    ::testing::internal::CaptureStdout();
#endif

    int bookId = lib->getNum();
    ASSERT_EQ(lib->borrow(id,bookId),id);
    ASSERT_EQ(lib->back(id,bookId),id);
    ASSERT_EQ(lib->back(id,bookId),-1);
    
    bookId = lib->getNum()+1;
    ASSERT_EQ(lib->back(id,bookId),-1);
#if BLOCKSTDOUT
    std::string output = ::testing::internal::GetCapturedStdout();
#endif
}
// TEST_F(MyTestFixture, AnotherTest) {
    // ...
// }
// ...
class MyTestBook : public ::testing::Test {
protected:
    void SetUp() override {
        std::string dirPath = "./data";
        try {
            for (const fs::directory_entry& entry : fs::directory_iterator(dirPath)) {
                if (entry.is_regular_file()) {
                    book->set(entry);
                    bookName = removeEnd(entry.path().filename());
                    bookPath = entry.path();
                    break;
                }
            }
        } catch (const fs::filesystem_error& ex) {
            std::cerr << "Error: " << ex.what() << std::endl;
        }
        // Set up any resources needed for the tests
    }

    void TearDown() override {
        // Clean up any resources used by the tests
    }
    int bookNum;
    int myVariable;
    int id = 1;
    std::string bookName;
    std::string bookPath;
    std::shared_ptr<BOOK> book = std::make_shared<BOOK>();
};

TEST_F(MyTestBook, MatchTest) {
#if BLOCKSTDOUT
    ::testing::internal::CaptureStdout();
#endif
    std::string testName = "aaa";
    ASSERT_EQ(book->match(testName.c_str()),-1);
    testName = bookName;
    ASSERT_EQ(book->match(testName.c_str()),1);
#if BLOCKSTDOUT
    std::string output = ::testing::internal::GetCapturedStdout();
#endif
}
TEST_F(MyTestBook, MatchBackTest) {
#if BLOCKSTDOUT
    ::testing::internal::CaptureStdout();
#endif
    std::string testName = "aaa";
    ASSERT_EQ(book->matchBack(id,testName.c_str()),-1);
    testName = bookName;
    ASSERT_EQ(book->matchBack(id,testName.c_str()),0);
    ASSERT_EQ(book->borrow(id),1);
    ASSERT_EQ(book->matchBack(id,testName.c_str()),1);
#if BLOCKSTDOUT
    std::string output = ::testing::internal::GetCapturedStdout();
#endif
}
TEST_F(MyTestBook, BorrowTest) {
#if BLOCKSTDOUT
    ::testing::internal::CaptureStdout();
#endif
    ASSERT_EQ(book->borrow(id),1);
#if BLOCKSTDOUT
    std::string output = ::testing::internal::GetCapturedStdout();
#endif
}
TEST_F(MyTestBook, GetBorrowerTest) {
#if BLOCKSTDOUT
    ::testing::internal::CaptureStdout();
#endif
    ASSERT_EQ(book->borrow(id),1);
    ASSERT_EQ(book->getBorrower(),id);
#if BLOCKSTDOUT
    std::string output = ::testing::internal::GetCapturedStdout();
#endif
}
TEST_F(MyTestBook, GetNameTest) {
#if BLOCKSTDOUT
    ::testing::internal::CaptureStdout();
#endif
    ASSERT_EQ(book->getName(),bookName);
#if BLOCKSTDOUT
    std::string output = ::testing::internal::GetCapturedStdout();
#endif
}
TEST_F(MyTestBook, BackTest) {
#if BLOCKSTDOUT
    ::testing::internal::CaptureStdout();
#endif
    ASSERT_EQ(book->back(),0);
#if BLOCKSTDOUT
    std::string output = ::testing::internal::GetCapturedStdout();
#endif
}
TEST_F(MyTestBook, DisplayTest) {
#if BLOCKSTDOUT
    ::testing::internal::CaptureStdout();
#endif
    ASSERT_EQ(book->showDescription(),1);
#if BLOCKSTDOUT
    std::string output = ::testing::internal::GetCapturedStdout();
#endif
}
// TEST_F(MyTestBook, BackTest) {
// #if BLOCKSTDOUT
//     ::testing::internal::CaptureStdout();
// #endif
// #if BLOCKSTDOUT
//     std::string output = ::testing::internal::GetCapturedStdout();
// #endif
// }
int main(int argc, char* argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}