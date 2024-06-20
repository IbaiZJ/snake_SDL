C_FILES = src/*.c
BIN = bin/snake

INCLUDES = -I/usr/include/SDL2
INCLUDES_L = -L/usr/lib
FLAGS = -lSDL2


all:
	gcc -o $(BIN) $(C_FILES) $(INCLUDES) $(INCLUDES_L) $(FLAGS)