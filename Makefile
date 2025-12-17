CC = gcc
CXX = g++

BUILD_DIR = build
EXEC_DIR = $(BUILD_DIR)/bin

KITTY_CFLAGS = -Wall -Wextra -std=c11

VTE_CXXFLAGS = -Wall -Wextra -std=c++17 -DVTE_GTK=4 `pkg-config --cflags xkbcommon`
VTE_LDFLAGS = `pkg-config --libs xkbcommon`

KITTY_TESTER = $(EXEC_DIR)/kitty_tester
VTE_TESTER = $(EXEC_DIR)/vte_tester

.PHONY: all clean

all: $(BUILD_DIR) $(EXEC_DIR) $(KITTY_TESTER) $(VTE_TESTER)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)
	mkdir -p $(BUILD_DIR)/kitty
	mkdir -p $(BUILD_DIR)/vte

$(EXEC_DIR):
	mkdir -p $(EXEC_DIR)

kitty_test/kitty_encoder_body.inc: source/key_encoding.c kitty_test/extract_kitty.py
	@echo "=> Generating kitty encoder body..."
	@python3 kitty_test/extract_kitty.py source/key_encoding.c

$(BUILD_DIR)/kitty/kitty_tester.o: kitty_test/kitty_tester.c kitty_test/kitty_mocks.h kitty_test/kitty_encoder_body.inc
	@echo "=> Compiling kitty tester object..."
	$(CC) $(KITTY_CFLAGS) -c kitty_test/kitty_tester.c -o $@

$(KITTY_TESTER): $(BUILD_DIR)/kitty/kitty_tester.o
	@echo "=> Linking kitty tester..."
	$(CC) $^ -o $@
	@echo "-> Built $(KITTY_TESTER)"

vte_test/vte_key_press_body.inc: source/vte.cc vte_test/extract_code.py
	@echo "=> Generating VTE key press body..."
	@python3 vte_test/extract_code.py source/vte.cc

$(BUILD_DIR)/vte/main.o: vte_test/main.cc vte_test/vte_key_tester.h
	@echo "=> Compiling VTE tester main object..."
	$(CXX) $(VTE_CXXFLAGS) -c vte_test/main.cc -o $@

$(BUILD_DIR)/vte/vte_key_tester.o: vte_test/vte_key_tester.cc vte_test/vte_key_tester.h vte_test/kittykeys.h vte_test/vte_key_press_body.inc
	@echo "=> Compiling VTE tester logic object..."
	$(CXX) $(VTE_CXXFLAGS) -c vte_test/vte_key_tester.cc -o $@

$(VTE_TESTER): $(BUILD_DIR)/vte/main.o $(BUILD_DIR)/vte/vte_key_tester.o
	@echo "=> Linking VTE tester..."
	$(CXX) $^ -o $@ $(VTE_LDFLAGS)
	@echo "-> Built $(VTE_TESTER)"


clean:
	@echo "=> Cleaning build files..."
	rm -rf $(BUILD_DIR)
	rm -f vte_test/vte_key_press_body.inc kitty_test/kitty_encoder_body.inc