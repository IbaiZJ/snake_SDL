all:
	gcc -o bin/snake src/*.c -I/usr/include/SDL2 -L/usr/lib -lSDL2