CC=cc
CFLAGS=  -c -Wall -Wextra -std=c99 -I/usr/local/include
LIBS= -L/usr/local/lib -lallegro -lallegro_main -lallegro_image -lallegro_dialog -lallegro_primitives
SOURCES:=$(shell echo *.c)
OBJECTS:=$(patsubst %.c,%.o,${SOURCES})
TARGETS:=$(patsubst %.c,%,${SOURCES})

all: main

main: main.o collision.o definitions.o game_draw.o game_entities.o game_pools.o logic_tick.o proj.o struct_pool.o trig.o
	$(CC) $(LIBS) main.o collision.o definitions.o game_draw.o game_entities.o game_pools.o logic_tick.o proj.o struct_pool.o trig.o -o main

main.o: main.c additional_main
	$(CC) $(CFLAGS) main.c

#If we change C sources that main imports, recompile.
additional_main: init.c key_handling.c tex_load.c

collision.o: collision.c
	$(CC) $(CFLAGS) collision.c

definitions.o: definitions.c
	$(CC) $(CFLAGS) definitions.c

game_draw.o: game_draw.c
	$(CC) $(CFLAGS) game_draw.c

game_entities.o: game_entities.c
	$(CC) $(CFLAGS) game_entities.c

game_pools.o: game_pools.c
	$(CC) $(CFLAGS) game_pools.c

logic_tick.o: logic_tick.c
	$(CC) $(CFLAGS) logic_tick.c

proj.o: proj.c
	$(CC) $(CFLAGS) proj.c

struct_pool.o: struct_pool.c
	$(CC) $(CFLAGS) struct_pool.c

trig.o: trig.c
	$(CC) $(CFLAGS) trig.c

clean:
	rm -f -R $(OBJECTS) $(TARGETS) *.dSYM