# OBJS specifies which files to compile as part of the project
OBJS = sdltest.c

# OBJ_NAME specifies the name of our executable
OBJ_NAME = sdltest

# This is the target that compiles our executable
all : $(OBJS)
	$(CC) $(OBJS) -w $(shell pkg-config --cflags --libs sdl2) -o $(OBJ_NAME)
