CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -I./src

INCLUDES = -I/opt/homebrew/include
LIB_PATHS = -L/opt/homebrew/lib

TEST_LDFLAGS = $(LIB_PATHS) -lcunit

SRC_DIR = src
TEST_DIR = tests
BUILD_DIR = build

APP_SOURCES = $(wildcard $(SRC_DIR)/*.cpp)
TEST_SOURCES = $(wildcard $(TEST_DIR)/*.cpp)

APP_TARGET = $(BUILD_DIR)/guitar_app
TEST_TARGET = $(BUILD_DIR)/test_runner

all: $(BUILD_DIR) $(APP_TARGET)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(APP_TARGET): $(APP_SOURCES) | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) $^ -o $@

test: $(BUILD_DIR) $(TEST_TARGET)
	./$(TEST_TARGET)

$(TEST_TARGET): $(TEST_SOURCES) src/song.cpp src/chord.cpp src/tracker.cpp src/metronome.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) $(INCLUDES) $^ -o $@ $(TEST_LDFLAGS)

clean:
	rm -rf $(BUILD_DIR)
	rm -f guitar_app test_runner

.PHONY: all test clean