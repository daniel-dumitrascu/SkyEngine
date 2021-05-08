CXX      := g++
CXXFLAGS := -DLINUX_PLATFORM \
			-DDEBUG_SECTION \
			-fPIC -Wall -g 
BUILD    := ./build
OBJ_DIR  := $(BUILD)/objects
APP_DIR  := $(BUILD)/apps
TARGET   := game
INCLUDE  := -I./../engine/sources/core/
LIBS_DIR := -L./../engine/build/apps/	
LIBS  	 := -lNemesisEngine \
			-lz
 
SRC_PATH = ./sources
SRC_TO_FILTER_OUT = ./sources/test/main.cpp
SRC := $(filter-out $(SRC_TO_FILTER_OUT), $(shell find $(SRC_PATH) -name '*.cpp'))
OBJECTS  := $(SRC:%.cpp=$(OBJ_DIR)/%.o)

all: build $(APP_DIR)/$(TARGET)

$(OBJ_DIR)/%.o: %.cpp
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c $< -o $@

$(APP_DIR)/$(TARGET): $(OBJECTS)
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $^ $(LIBS_DIR) $(LIBS) -o $(APP_DIR)/$(TARGET)  

.PHONY: all build clean debug release

build:
	@mkdir -p $(APP_DIR)
	@mkdir -p $(OBJ_DIR)

debug: CXXFLAGS += -DDEBUG -g
debug: all

release: CXXFLAGS += -O2
release: all

clean:
	-@rm -rvf $(OBJ_DIR)/*
	-@rm -rvf $(APP_DIR)/*