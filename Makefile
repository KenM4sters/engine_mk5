APP_NAME = app
BUILD_DIR = bin
C_FILES = ./src/*.c
MATH_FILES = ./src/engine/math/*.c
ENGINE_FILES = ./src/engine/*.c

APP_INCLUDES:= -I./deps/include/GLFW -framework Cocoa -framework OpenGL -framework IOkit
APP_INCLUDES_4= -I./deps/include/*.h
APP_LINKERS:= -L./deps/lib -lglfw3

build:
	clang $(C_FILES) $(ENGINE_FILES) $(MATH_FILES) -o $(BUILD_DIR)/$(APP_NAME) $(APP_INCLUDES_4) $(APP_INCLUDES) $(APP_LINKERS)

clean:
			rm -rf bin/app
