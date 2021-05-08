CXX      := g++
CXXFLAGS := -DLINUX_PLATFORM \
			-DGLEW_STATIC \
			-DGRAPHICS_OPENGL_LATEST \
			-DDEBUG_SECTION \
			-fPIC -Wall -g 
LDFLAGS  := -shared
BUILD    := ./build
OBJ_DIR  := $(BUILD)/objects
APP_DIR  := $(BUILD)/apps
TARGET   := libNemesisEngine.so
INCLUDE  := -I./sources/core \
			-I./../libs/glfw/include/ \
			-I./../libs/glew/include/ \
			-I./../libs/libpng16/ \
			-I./../libs/libpng16/include/libpng16 
LIBS_DIR := -L./../libs/glfw/lib/linux/ \
			-L./../libs/glew/lib/linux/ \
			-L./../libs/libpng16/
LIBS  	 := -lglfw3 \
			-lGLEW \
			-lGL \
			-lpng
 
SRC_PATH = ./sources
SRC_TO_FILTER_OUT = ./sources/core/tinyxml2/contrib/html5-printer.cpp \
					./sources/core/platform/windows/InputDataType.h \
					./sources/core/platform/windows/WindowsPlatform.h \
					./sources/core/platform/windows/WindowsPlatform.cpp \
					./sources/core/video/opengl_2.0_es/OpenGLESRenderer.cpp
SRC := $(filter-out $(SRC_TO_FILTER_OUT), $(shell find $(SRC_PATH) -name '*.cpp'))
OBJECTS  := $(SRC:%.cpp=$(OBJ_DIR)/%.o)

all: build $(APP_DIR)/$(TARGET)

$(OBJ_DIR)/%.o: %.cpp
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c $< -o $@

$(APP_DIR)/$(TARGET): $(OBJECTS)
	@mkdir -p $(@D)
	$(CXX)  $(CXXFLAGS) $(LIBS_DIR) -Wl,-whole-archive $(LIBS) -Wl,-no-whole-archive $(LDFLAGS) -o $(APP_DIR)/$(TARGET) $^ 

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