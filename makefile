CXX := g++
CXXFLAGS := -g -Wall

TARGET := parser

BUILD_DIR := ./build
SRC_DIR := ./src

SRCS := $(shell find $(SRC_DIRS) -name '*.cpp')
OBJS := $(SRCS:$(SRC_DIR)/%.cpp=$(BUILD_DIR)/%.o)

$(TARGET) : $(OBJS)
	$(CXX) -o $@ $(OBJS)

$(BUILD_DIR)/%.o : $(SRC_DIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

.PHONY : clean

clean :
	@rm -rf $(BUILD_DIR) $(TARGET)

