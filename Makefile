CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -I./include -I./test
LDFLAGS = -lm

SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin
TEST_DIR = test
INCLUDE_DIR = include

SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRCS))
EXEC = $(BIN_DIR)/sbms

TEST_SRCS = $(wildcard $(TEST_DIR)/*.c)
TEST_OBJS = $(patsubst $(TEST_DIR)/%.c,$(OBJ_DIR)/%.o,$(TEST_SRCS))
TEST_EXECS = $(patsubst $(TEST_DIR)/%.c,$(BIN_DIR)/%,$(TEST_SRCS))

UNITY_SRC = $(TEST_DIR)/unity.c
UNITY_OBJ = $(OBJ_DIR)/unity.o

.PHONY: all clean test

all: $(EXEC)

$(EXEC): $(OBJS) | $(BIN_DIR)
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: $(TEST_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(UNITY_OBJ): $(UNITY_SRC) | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(BIN_DIR)/%: $(OBJ_DIR)/%.o $(filter-out $(OBJ_DIR)/main.o,$(OBJS)) $(UNITY_OBJ) | $(BIN_DIR)
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

$(BIN_DIR) $(OBJ_DIR):
	mkdir -p $@

test: $(filter-out $(BIN_DIR)/unity, $(TEST_EXECS))
	@for test in $(TEST_EXECS); do ./$$test; done

clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

