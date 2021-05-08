CXX      := g++
CXXFLAGS := -DGLEW_STATIC \
			-DLINUX_PLATFORM \
			-DGRAPHICS_OPENGL_LATEST \
			-fPIC -Wall -g 
BUILD    := ./build
OBJ_DIR  := $(BUILD)/objects
APP_DIR  := $(BUILD)/apps
TARGET   := sample
INCLUDE  := -I./../libs/glfw/include/ \
			-I./../libs/glew/include/		
LIBS_DIR := -L./../libs/glfw/lib/linux/ \
			-L./../libs/glew/lib/linux/
LIBS  	 := -lglfw3 \
			-lGLEW \
			-lpthread \
			-lGL \
			-lX11 \
			-lXi \
			-lXrandr \
			-lXxf86vm \
			-lXinerama \
			-lXcursor \
			-lrt \
			-lm \
			-ldl
			
 
SRC_PATH = .
SRC := $(shell find $(SRC_PATH) -name '*.cpp')
OBJECTS  := $(SRC:%.cpp=$(OBJ_DIR)/%.o)

all: build $(APP_DIR)/$(TARGET)

$(OBJ_DIR)/%.o: %.cpp
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c $< -o $@ $(LDFLAGS)

$(APP_DIR)/$(TARGET): $(OBJECTS)
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(LIBS_DIR) -Wl,-whole-archive $(LIBS) -Wl,-no-whole-archive -o $(APP_DIR)/$(TARGET) $^ $(LDFLAGS)

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