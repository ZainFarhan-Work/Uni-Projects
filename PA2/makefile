CC = gcc
CFLAGS = -Wall -Wextra -g -std=c11

INCLUDE = -I./include

PYTHON := python3
SCRIPT := test/test_valgrind.py

SRC_DIR = src
TEST_DIR = test
BIN_DIR = bin

SRC_KEY = $(SRC_DIR)/key.c
SRC_KEYCHAIN = $(SRC_DIR)/keychain.c
SRC_LOCATOR = $(SRC_DIR)/locator.c
SRC_NAVIGATOR = $(SRC_DIR)/navigator.c

TEST_KEY = $(TEST_DIR)/test_key.c
TEST_KEYCHAIN = $(TEST_DIR)/test_keychain.c
TEST_LOCATOR = $(TEST_DIR)/test_locator.c
TEST_NAVIGATOR = $(TEST_DIR)/test_navigator.c

BIN_KEY = $(BIN_DIR)/test_key
BIN_KEYCHAIN = $(BIN_DIR)/test_keychain
BIN_LOCATOR = $(BIN_DIR)/test_map
BIN_NAVIGATOR = $(BIN_DIR)/test_navigator

VALGRIND = valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes

all: $(BIN_KEY) $(BIN_KEYCHAIN) $(BIN_LOCATOR) $(BIN_NAVIGATOR)

$(BIN_KEY): $(SRC_KEY) $(TEST_KEY)
	$(CC) $(CFLAGS) $(TEST_KEY) -o $(BIN_KEY)

$(BIN_KEYCHAIN): $(SRC_KEY) $(SRC_KEYCHAIN) $(TEST_KEYCHAIN)
	$(CC) $(CFLAGS) $(INCLUDE) $(SRC_KEY) $(TEST_KEYCHAIN) -o $(BIN_KEYCHAIN)

$(BIN_LOCATOR): $(SRC_LOCATOR) $(TEST_LOCATOR)
	$(CC) $(CFLAGS) $(TEST_LOCATOR) -o $(BIN_LOCATOR)

$(BIN_NAVIGATOR): $(SRC_KEY) $(SRC_KEYCHAIN) $(SRC_LOCATOR) $(SRC_NAVIGATOR) $(TEST_NAVIGATOR)
	$(CC) $(CFLAGS) $(INCLUDE) $(SRC_KEY) $(SRC_KEYCHAIN) $(SRC_LOCATOR) $(TEST_NAVIGATOR) -o $(BIN_NAVIGATOR)

run_key: $(BIN_KEY)
	@$(VALGRIND) ./$(BIN_KEY) 2> $(BIN_DIR)/valgrind_key.txt
	@$(PYTHON) $(SCRIPT) bin/valgrind_key.txt 1

run_keychain: $(BIN_KEYCHAIN)
	@$(VALGRIND) ./$(BIN_KEYCHAIN) 2> $(BIN_DIR)/valgrind_keychain.txt
	@$(PYTHON) $(SCRIPT) bin/valgrind_keychain.txt 3

run_locator: $(BIN_LOCATOR)
	@$(VALGRIND) ./$(BIN_LOCATOR) 2> $(BIN_DIR)/valgrind_map.txt
	@$(PYTHON) $(SCRIPT) bin/valgrind_map.txt 1

run_navigator: $(BIN_NAVIGATOR)
	@$(VALGRIND) ./$(BIN_NAVIGATOR) 2> $(BIN_DIR)/valgrind_cont.txt
	@$(PYTHON) $(SCRIPT) bin/valgrind_cont.txt 3

clean:
	rm -f $(BIN_DIR)/*

.PHONY: all clean run_key run_keychain run_locator run_navigator
