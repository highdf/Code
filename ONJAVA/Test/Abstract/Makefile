.PHONY:all run

CC=javac
RUN=java

SRC_DIR=src
BIN_DIR=bin

src_file=$(wildcard $(SRC_DIR)/*.java)

MAIN_CLASS=Main
MAIN_FILE=Main.java

all:$(src_file) $(MAIN_FILE)
	$(CC) -d $(BIN_DIR) $^

run:
	$(RUN) -cp $(BIN_DIR) $(MAIN_CLASS)
