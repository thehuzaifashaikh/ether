PROJECT := ether
SRC_DIR := src
OBJ_DIR := obj
BIN_DIR := bin
INCLUDE_DIR := include
LIB_DIR := lib
SRC_FILES := $(wildcard $(SRC_DIR)/*.c)
OBJ_FILES := $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRC_FILES))
LDFLAGS := /usr/lib/x86_64-linux-gnu/libglfw.so -lGL -lX11 -lpthread
CFLAGS := -Wall -Wextra -Wshadow -pedantic -std=c99 -m64 -g -O0 -I $(INCLUDE_DIR)

ifeq ($(OS), Windows_NT)
	PROJECT := $(PROJECT).exe
endif

run: $(BIN_DIR)/$(PROJECT)
	./$(BIN_DIR)/$(PROJECT)

$(BIN_DIR)/$(PROJECT): $(OBJ_FILES)
	gcc -o $@ $^ $(LDFLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	gcc $(CFLAGS) -c -o $@ $<

clean:
ifeq ($(OS), Windows_NT)
	del $(BIN_DIR)\$(PROJECT)
	del $(OBJ_FILES)
else
	rm -f $(BIN_DIR)/$(PROJECT)
	rm -f $(OBJ_FILES)
endif
