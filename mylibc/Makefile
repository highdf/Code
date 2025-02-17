.PHONY: all 

SRC_DIR=src
LIB_DIR=libs
TEST_DIR=test
TEST_FILE_NAME=test_string.c

SRC_FILES=$(wildcard $(SRC_DIR)/*)
TEST_PATH=$(TEST_DIR)/$(TEST_FILE_NAME)

all:$(SRC_FILES) $(TEST_PATH)
	gcc $^ -o out
