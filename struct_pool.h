#ifndef H_STRUCT_POOL
#define H_STRUCT_POOL
#include "definitions.h"

void init_struct_pool(void *pool[], int count, void *(init_struct)(void));

void free_struct_pool(void *pool[], int count);

//This one swaps two pointers in an array.
void swap_array_item(void *pool[], int a, int b);

//Kills a live struct and returns it to the pool.
void kill_item(SPP sp, int index);

//Same as above, but takes a specially-prepared PROJP.
void special_kill_item(SPP sp, PROJP pp);

//Revives a struct from the smartpool and gives it to you.
void * new_pool_item(SPP sp);

//Updates all items in a pool. Takes a function pointer, which is the action to
//be performed on each struct. The update function specified should cast a
//struct pointer given to it by this function as the appropriate struct pointer
//type.
void update_pool(SPP sp, void (*struct_update)(SPP, int));

//The function pointer is to a function which initializes the kind of struct
//that you wish to fill the pool with.
SPP init_smartItemPool(int count, void *(init_struct)());

void free_smartItemPool(SPP sp);

#endif