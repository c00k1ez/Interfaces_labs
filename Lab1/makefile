SRC_DIR := ./src
OBJ_DIR := ./obj

SRC_FILES := $(wildcard $(SRC_DIR)/*.cpp)
OBJ_FILES := $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRC_FILES))

all: main

main: $(OBJ_FILES)
	g++ $(OBJ_DIR)/change_input.o $(OBJ_DIR)/utils.o -o change_input
	g++ $(OBJ_DIR)/check_input.o $(OBJ_DIR)/utils.o -o check_input
	g++ $(OBJ_DIR)/make_input.o $(OBJ_DIR)/utils.o -o make_input

clean:
	rm -rf $(OBJ_DIR) change_input check_input make_input

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	if [ ! -d $(OBJ_DIR) ]; then mkdir $(OBJ_DIR); fi
	g++ -std=c++11 -c -o $@ $<