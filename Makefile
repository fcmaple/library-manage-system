.PONY=clean,run

CXX= g++

SRC_DIR = src
BIN_DIR = bin
OBJ_DIR = obj
#source files

SRCS = $(wildcard $(SRC_DIR)/*.cpp)
OBJS = $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRCS))

CC = gcc
CXXFLAGS = -std=c++17 -Wall -g
LDFLAGS =
PROG=lms
all: $(BIN_DIR)/$(PROG)

$(shell mkdir -p $(OBJ_DIR))
$(shell mkdir -p $(BIN_DIR))

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) -c $(CXXFLAGS) $< -o $@

$(BIN_DIR)/$(PROG): $(OBJS)
	$(CXX) -o $@ $^ $(CXXFLAGS)
run:
    ifdef PORT
		@echo "Running with argument: $(PORT)"
		$(BIN_DIR)/$(PROG) $(PORT)
    else
		@echo "Usage. make run PORT=[PORT]"
    endif

clean:
	rm -rf $(OBJ_DIR)/*.o $(BIN_DIR)/$(PROG)




