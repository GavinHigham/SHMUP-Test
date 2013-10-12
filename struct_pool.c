#pragma once

//C stuff.
#include <stdio.h>
#include <stdlib.h>
#ifdef _WIN32
	#include <time.h>
#else
	#include <sys/time.h>
#endif
//Allegro stuff.
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
//My stuff.
#include "definitions.h"
#include "struct_pool.c"
#include "proj.c"
#include "init.c"
#include "tex_load.c"
#include "logic_tick.c"
#include "key_handling.c"
#include "game_draw.c"

//This is my implementation for what I call a "struct pool", a way to initialize
//and store a bunch of reused structs to avoid allocating memory when stuff is running.

void init_struct_pool(void *pool[], int count, void *(init_struct)(void)) {
	int i;
	for (i = 0; i < count; i++) {
		pool[i] = init_struct();
	}
}

void free_struct_pool(void *pool[], int count)
{
	int i;
	for (i = 0; i < count; i++) free(pool[i]);
}

//This one swaps two pointers in an array.
void swap_array_item(void *pool[], int a, int b)
{
	//Ugh why are these void pointers they should be struct pointers.
	void *temp = pool[a];
	pool[a] = pool[b];
	pool[b] = temp;
}

//Kills a live struct and returns it to the pool.
void kill_item(SPP sp, int index) {
	swap_array_item((void **)sp->pool, index, sp->liveIndex - 1);
	sp->liveIndex--;
}

//Same as above, but takes a specially-prepared PROJP.
void special_kill_item(SPP sp, PROJP pp) {
	swap_array_item((void **)sp->pool, pp->index, sp->liveIndex - 1);
	sp->liveIndex--;
}

//Revives a struct from the smartpool and gives it to you.
void * new_pool_item(SPP sp)
{
	void *new = sp->pool[sp->liveIndex];
	sp->liveIndex++;
	return new;
}

//Updates all items in a pool. Takes a function pointer, which is the action to
//be performed on each struct. The update function specified should cast a
//struct pointer given to it by this function as the appropriate struct pointer
//type.
void update_pool(SPP sp, void (*struct_update)(SPP, int)) {
	int i;
	for (i = 0; i < sp->liveIndex; i++) {
		struct_update(sp, i);
	}
}

//The function pointer is to a function which initializes the kind of struct
//that you wish to fill the pool with.
SPP init_smartItemPool(int count, void *(init_struct)())
{
	SPP sp = malloc(sizeof(SMARTPOOL));
	sp->pool = malloc(sizeof(void *)*count);
	init_struct_pool((void **)sp->pool, count, init_struct);
	sp->liveIndex = 0;
	sp->poolsize = count;
	return sp;
}

void free_smartItemPool(SPP sp) {
	free_struct_pool((void **)sp->pool, sp->poolsize);
	free(sp);
}