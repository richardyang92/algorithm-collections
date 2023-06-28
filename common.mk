CC = clang

SRC = $(wildcard *.c)
TARGET = $(addprefix $(TARGET_DIR), $(BIN))

all:
	$(CC) -g -o $(TARGET) $(SRC)