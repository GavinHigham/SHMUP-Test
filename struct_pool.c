#include "struct_pool.h"
//C stuff.
#include <stdio.h>
#include <stdlib.h>
//Allegro stuff.
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>

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

void swap_array_item(void *pool[], int a, int b)
{
	//Ugh why are these void pointers they should be struct pointers.
	void *temp = pool[a];
	pool[a] = pool[b];
	pool[b] = temp;
}

void kill_item(SPP sp, int index) {
	swap_array_item((void **)sp->pool, index, sp->liveIndex - 1);
	sp->liveIndex--;
}

void special_kill_item(SPP sp, PROJP pp) {
	swap_array_item((void **)sp->pool, pp->index, sp->liveIndex - 1);
	sp->liveIndex--;
}

void * new_pool_item(SPP sp)
{
	void *new_tmp = sp->pool[sp->liveIndex];
	sp->liveIndex++;
	return new_tmp;
}

void update_pool(SPP sp, void (*struct_update)(SPP, int)) {
	int i;
	for (i = 0; i < sp->liveIndex; i++) {
		struct_update(sp, i);
	}
}

SPP init_smartItemPool(int count, void *(init_struct)())
{
	SPP sp = (SPP)malloc(sizeof(SMARTPOOL));
	int pool_size = sizeof(void *)*count;
	sp->pool = (void **)malloc(pool_size);
	init_struct_pool((void **)sp->pool, count, init_struct);
	sp->liveIndex = 0;
	sp->poolsize = count;
	return sp;
}

void free_smartItemPool(SPP sp) {
	free_struct_pool((void **)sp->pool, sp->poolsize);
	free(sp);
}