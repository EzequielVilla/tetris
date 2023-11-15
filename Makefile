CXX = g++
CXXFLAGS = -std=c++11 -Wall

SRC_DIR = src
BUILD_DIR = build
BIN_DIR = bin

SRCS = $(wildcard $(SRC_DIR)/*.cpp)
OBJS = $(patsubst $(SRC_DIR)/%.cpp, $(BUILD_DIR)/%.o, $(SRCS))
TARGET = $(BIN_DIR)/tetris

all: $(TARGET)

$(TARGET): $(OBJS)
	@mkdir -p $(BIN_DIR) 
	$(CXX) $(CXXFLAGS) -o $@ $^

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(BUILD_DIR)  
	$(CXX) $(CXXFLAGS) -c -o $@ $<

clean:
	rm -rf $(BUILD_DIR)/* $(TARGET)