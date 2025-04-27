CC := gcc
CFLAGS := -Wall -Wextra
AR := ar rcs

SRC_DIR := src
SRC := $(SRC_DIR)/jyggalog.c
OBJ := jyggalog.o
TARGET := libjl.a

$(TARGET): $(OBJ)
	$(AR) $@ $^

$(OBJ): $(SRC)
	$(CC) -c -o $@ $^ $(CFLAGS)

test: test.c
	$(CC) test.c -o test -L./ -ljl

.PHONY: clean

clean:
	rm -f $(OBJ) $(TARGET)
