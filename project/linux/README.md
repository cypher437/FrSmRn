# Dependencies

## Ubuntu
apt install libsdl2-ttf-dev libsdl2-mixer-dev libsdl2-image-dev libsdl2-dev

## OSX
How to run repository on MAC OSX:

The default compiler on OSX is Clang rather than vanilla GCC (as on Linux),
therefore some compile and makefile commands will by default not work on OSX.

1. In /project/ create compile.sh:

```
#!/bin/bash

gcc  `sdl2-config --cflags` -Wall -Wempty-body -Werror -Wstrict-prototypes -Werror=uninitialized -Warray-bounds -g -I./src -c -o build/block.o src/block.c
gcc  `sdl2-config --cflags` -Wall -Wempty-body -Werror -Wstrict-prototypes -Werror=uninitialized -Warray-bounds -g -I./src -c -o build/camera.o src/camera.c
gcc  `sdl2-config --cflags` -Wall -Wempty-body -Werror -Wstrict-prototypes -Werror=uninitialized -Warray-bounds -g -I./src -c -o build/draw.o src/draw.c
gcc  `sdl2-config --cflags` -Wall -Wempty-body -Werror -Wstrict-prototypes -Werror=uninitialized -Warray-bounds -g -I./src -c -o build/entities.o src/entities.c
gcc  `sdl2-config --cflags` -Wall -Wempty-body -Werror -Wstrict-prototypes -Werror=uninitialized -Warray-bounds -g -I./src -c -o build/init.o src/init.c
gcc  `sdl2-config --cflags` -Wall -Wempty-body -Werror -Wstrict-prototypes -Werror=uninitialized -Warray-bounds -g -I./src -c -o build/input.o src/input.c
gcc  `sdl2-config --cflags` -Wall -Wempty-body -Werror -Wstrict-prototypes -Werror=uninitialized -Warray-bounds -g -I./src -c -o build/io.o src/io.c
gcc  `sdl2-config --cflags` -Wall -Wempty-body -Werror -Wstrict-prototypes -Werror=uninitialized -Warray-bounds -g -I./src -c -o build/main.o src/main.c
gcc  `sdl2-config --cflags` -Wall -Wempty-body -Werror -Wstrict-prototypes -Werror=uninitialized -Warray-bounds -g -I./src -c -o build/map.o src/map.c
gcc  `sdl2-config --cflags` -Wall -Wempty-body -Werror -Wstrict-prototypes -Werror=uninitialized -Warray-bounds -g -I./src -c -o build/pizza.o src/pizza.c
gcc  `sdl2-config --cflags` -Wall -Wempty-body -Werror -Wstrict-prototypes -Werror=uninitialized -Warray-bounds -g -I./src -c -o build/player.o src/player.c
gcc  `sdl2-config --cflags` -Wall -Wempty-body -Werror -Wstrict-prototypes -Werror=uninitialized -Warray-bounds -g -I./src -c -o build/platform.o src/platform.c
gcc  `sdl2-config --cflags` -Wall -Wempty-body -Werror -Wstrict-prototypes -Werror=uninitialized -Warray-bounds -g -I./src -c -o build/sound.o src/sound.c
gcc  `sdl2-config --cflags` -Wall -Wempty-body -Werror -Wstrict-prototypes -Werror=uninitialized -Warray-bounds -g -I./src -c -o build/stage.o src/stage.c
gcc  `sdl2-config --cflags` -Wall -Wempty-body -Werror -Wstrict-prototypes -Werror=uninitialized -Warray-bounds -g -I./src -c -o build/textures.o src/textures.c
gcc  `sdl2-config --cflags` -Wall -Wempty-body -Werror -Wstrict-prototypes -Werror=uninitialized -Warray-bounds -g -I./src -c -o build/text.o src/text.c
gcc  `sdl2-config --cflags` -Wall -Wempty-body -Werror -Wstrict-prototypes -Werror=uninitialized -Warray-bounds -g -I./src -c -o build/util.o src/util.c
gcc -o pp06 build/block.o build/camera.o build/draw.o build/entities.o build/init.o build/input.o build/io.o build/main.o build/map.o build/pizza.o build/player.o build/platform.o build/sound.o build/stage.o build/textures.o build/text.o build/util.o `sdl2-config --libs` -lSDL2_mixer -lSDL2_image -lm
```

Make sure that the "-lefence" flags have been removed from any compiler commands you use.
Make the file executable:

chmod +x compile.sh

2. Install Homebrew and SDL2 packages

Homebrew is a convenient and widely supported package manager for OSX that allows for
easy installation of many tools and packages commonly used on Linux.

https://docs.brew.sh/Installation

Use homebrew to install sdl2:

brew install sdl2

brew install sdl2_image

brew install sdl2_mixer

3. Replace abs function with fabs:

Under project/src/ edit the following lines in "platform.c":

LINE 50: if (abs(self->x - self->sx) < PLATFORM_SPEED && abs(self->y - self->sy) < PLATFORM_SPEED)

CHANGE TO: if (fabs(self->x - self->ex) < PLATFORM_SPEED && fabs(self->y - self->ey) < PLATFORM_SPEED)

LINE 58: if (abs(self->x - self->ex) < PLATFORM_SPEED && abs(self->y - self->ey) < PLATFORM_SPEED)

CHANGE TO: if (fabs(self->x - self->ex) < PLATFORM_SPEED && fabs(self->y - self->ey) < PLATFORM_SPEED)

4. Create build directory, compile and run game

in /project/:

mkdir build

./compile.sh

./pp06
