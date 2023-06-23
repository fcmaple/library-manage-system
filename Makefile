SRC_DIR = src
BIN_DIR = bin
OBJ_DIR = obj
TEST_DIR = tests


SRCS = $(wildcard $(SRC_DIR)/*.cpp)
TEST_SRCS = $(wildcard $(TEST_DIR)/*.cpp)

OBJS = $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRCS))
TEST_OBJS = $(patsubst $(TEST_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(TEST_SRCS))

INC := -I$(SRC_DIR)

CC = gcc
CXX= g++
CXXFLAGS = -std=c++17 -Wall -g -O3
LDFLAGS =
PROG=LMS
TEST_PROG= testLMS
TESTFLAGS = -lgtest -lgtest_main -pthread

.PHONY = all clean test run

all: $(BIN_DIR)/$(PROG)

$(shell mkdir -p $(OBJ_DIR))
$(shell mkdir -p $(BIN_DIR))

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) -c $(CXXFLAGS) $(INC) $< -o $@

$(BIN_DIR)/$(PROG): $(OBJS)
	$(CXX) -o $@ $^ $(CXXFLAGS)

run:
    ifdef PORT
		@echo "Running with argument: $(PORT)"
		$(BIN_DIR)/$(PROG) $(PORT)
    else
		@echo "Usage. make run PORT=[PORT]"
    endif

test: $(BIN_DIR)/$(TEST_PROG)
	$(BIN_DIR)/$(TEST_PROG)

$(BIN_DIR)/$(TEST_PROG): $(TEST_OBJS) $(filter-out $(OBJ_DIR)/main.o, $(OBJS))
	$(CXX) $(CXXFLAGS) $(INC) -o $@ $^ -lgtest -lgtest_main -pthread

$(OBJ_DIR)/%.o: $(TEST_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) $(INC) -c -o $@ $<

clean:
	rm -rf $(OBJ_DIR)/*.o $(BIN_DIR)/$(PROG) $(BIN_DIR)/$(TEST_PROG) /dev/shm/sem.lmsSem /dev/shm/sem.libSem




