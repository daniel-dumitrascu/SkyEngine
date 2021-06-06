include ../../conanbuildinfo.mak

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
			-I$(CONAN_INCLUDE_DIRS_GLFW) \
			-I$(CONAN_INCLUDE_DIRS_GLEW) \
			-I$(CONAN_INCLUDE_DIRS_LIBPNG) \
			-I$(CONAN_INCLUDE_DIRS_TINYXML2)
LIBS_DIR := -L$(CONAN_LIB_DIRS_GLFW) \
			-L$(CONAN_LIB_DIRS_GLEW) \
			-L$(CONAN_LIB_DIRS_LIBPNG) \
			-L$(CONAN_LIB_DIRS_TINYXML2)
LIBS  	 := -l$(CONAN_LIBS_GLFW) \
			-l$(CONAN_LIBS_GLEW) \
			-l$(CONAN_LIBS_LIBPNG) \
			-l$(CONAN_LIBS_TINYXML2) \
			-lpthread \
			-lGL
 
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
	@LD_LIBRARY_PATH=$(APP_DIR)
	@export LD_LIBRARY_PATH

debug: CXXFLAGS += -DDEBUG -g
debug: all

release: CXXFLAGS += -O2
release: all

clean:
	-@rm -rvf $(OBJ_DIR)/*
	-@rm -rvf $(APP_DIR)/*