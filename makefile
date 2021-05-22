CC = gcc
INC_DIR=./include
SRC_DIR=./src
BUILD_DIR=./build
EXE_DIR=./bin
TARGET=main.exe
CFLAGS += -lm -g
SRC=$(wildcard $(SRC_DIR)/*.c)
OBJ=$(patsubst %.c, $(BUILD_DIR)/%.o, $(notdir $(SRC)))


app:$(OBJ)
	@$(CC) $(CFLAGS)  $(OBJ)  -o $(EXE_DIR)/$(TARGET)

$(BUILD_DIR)/%.o:$(SRC_DIR)/%.c
	@$(CC) -g -fno-stack-protector -c $< -o $@

run:
	$(EXE_DIR)/$(TARGET)

.PHONY: clean

clean:
	rm -rf ./build/*.o ./bin/*.exe