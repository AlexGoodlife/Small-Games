OBJS = main.c src/commands.c src/combat.c src/entity.c src/location.c src/npc.c src/player.c src/quests.c

CC = gcc

INCLUDE_PATHS = -Iinclude

COMPILER_FLAGS = -Wall 

LINKER_FLAGS = -lmingw32

OBJ_NAME = rpg

all : $(OBJS)
	$(CC) $(OBJS) $(INCLUDE_PATHS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)