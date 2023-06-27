CC = gcc

SRC = $(wildcard *.c)
TARGET = $(addprefix $(TARGET_DIR), $(BIN))

all:
	CC -o $(TARGET) $(SRC)