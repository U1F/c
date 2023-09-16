#OBJS specifies which files to compile as part of the project
OBJS = sdltest.c

#CC specifies which compiler we're using
CC = gcc

#COMPILER_FLAGS specifies the additional compilation options we're using
# Enable all warnings and treat them as errors with `-Wall -Wextra -Werror`
COMPILER_FLAGS = -Wall -Wextra -Werror

#LINKER_FLAGS specifies the libraries we're linking against
LINKER_FLAGS = $(shell pkg-config --cflags --libs sdl2 SDL2_image)

#OBJ_NAME specifies the name of our executable
OBJ_NAME = sdltest

#This is the target that compiles our executable
all : $(OBJS)
	$(CC) $(OBJS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)

