CC = gcc
CFLAGS = -Wall -Wextra -std=c11
LDFLAGS = -lm

SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin
TEST_DIR = test

SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRCS))
EXEC = $(BIN_DIR)/sbms

TEST_SRCS = $(wildcard $(TEST_DIR)/*.c)
TEST_OBJS = $(patsubst $(TEST_DIR)/%.c,$(OBJ_DIR)/%.o,$(TEST_SRCS))
TEST_EXECS = $(patsubst $(TEST_DIR)/%.c,$(BIN_DIR)/%,$(TEST_SRCS))

.PHONY: all clean test

all: $(EXEC)

$(EXEC): $(OBJS) | $(BIN_DIR)
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: $(TEST_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -I$(SRC_DIR) -c $< -o $@

$(BIN_DIR)/%: $(OBJ_DIR)/%.o $(filter-out $(OBJ_DIR)/main.o,$(OBJS)) $(TEST_DIR)/unity.o | $(BIN_DIR)
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

$(BIN_DIR) $(OBJ_DIR):
	mkdir -p $@

test: $(TEST_EXECS)
	@for test in $(TEST_EXECS); do ./$$test; done

$(TEST_DIR)/unity.o: $(TEST_DIR)/unity.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

