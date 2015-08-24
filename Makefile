CC=clang
CFLAGS=  -c -Wall -Wextra -std=c99 -I/usr/local/include
LDFLAGS= -L/usr/local/lib
LDLIBS= -lallegro -lallegro_main -lallegro_image -lallegro_dialog -lallegro_primitives
OBJECTS = main.o collision.o definitions.o game_draw.o game_entities.o game_pools.o logic_tick.o proj.o struct_pool.o tex_load.o trig.o
EXE = main

all: main

main: $(OBJECTS)
	$(CC) $(LDFLAGS) $(LDLIBS) $(OBJECTS) -o $(EXE)

clean:
	rm -f -R $(OBJECTS) $(EXE) *.dSYM
