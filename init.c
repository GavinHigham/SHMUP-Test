#include "init.h"
#include "struct_pool.h"
#include "proj.h"
#include "collision.h"
///C stuff.
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

void init_random()
{
	//struct timeval tv;
	//gettimeofday(&tv, NULL);
	//Seeding with microseconds.
	//You can re-seed rapidly without getting the same results.
	srand(time(NULL));
}

int init_stuff()
{
	int collision_array_width;
	int collision_array_height;
	init_random();

	if(!al_init())
	{
		fprintf(stderr, "Failed to initialize allegro!\n");
		return -1;
	}
 
	if(!al_install_keyboard())
	{
		fprintf(stderr, "Failed to initialize the keyboard!\n");
		return -1;
	}
 
	timer = al_create_timer(1.0 / FPS);
	if(!timer)
	{
		fprintf(stderr, "Failed to create timer!\n");
		return -1;
	}

	if(!al_init_image_addon())
	{
		fprintf(stderr, "Failed to initialize al_init_image_addon!\n");
		return -1;
	}
 
	display = al_create_display(SCREEN_W, SCREEN_H);
	if(!display)
	{
		fprintf(stderr, "Failed to create display!\n");
		al_destroy_timer(timer);
		return -1;
	}

	ship = init_proj();
	ship->kind = SHIP;
	ship->health = 100;
	ship->offsetX = 26;
	ship->offsetY = 22;
	ship->sizeX = 45;
	ship->sizeY = 7;
	//Setup the ship's laser pool.
	sl_pool = init_smartItemPool(PROJ_POOL_SIZE, (void *(*)())&init_proj);
	for (i = 0; i < sl_pool->poolsize; i++) {
		PROJP tmp = (PROJP)sl_pool->pool[i];
		tmp->kind = BOLT;
		tmp->sizeX = 50;
		tmp->sizeY = 20;
	}

	//Setup some asteroids for test purposes.
	ast_pool = init_smartItemPool(AST_POOL_SIZE, (void *(*)())&init_proj);
	for (i = 0; i < ast_pool->poolsize; i++) {
		PROJP tmp = (PROJP)ast_pool->pool[i];
		tmp->kind = ASTEROID;
		tmp->offsetX = 6;
		tmp->offsetY = 7;
		tmp->sizeX = 12;
		tmp->sizeY = 12;
	}

	//Setup the pool of "particle" effects.
	blast_pool = init_smartItemPool(PROJ_POOL_SIZE, (void *(*)())&init_proj);
	for (i = 0; i < blast_pool->poolsize; i++) {
		PROJP tmp = (PROJP)blast_pool->pool[i];
		tmp->kind = BLAST;
		tmp->health = 36;
		tmp->animFrame = 0;
	}

	//Setup the enemy pool.
	enemy_pool = init_smartItemPool(ENEMY_POOL_SIZE, (void *(*)())&init_proj);
	for (i = 0; i < enemy_pool->poolsize; i++) {
		PROJP tmp = (PROJP)enemy_pool->pool[i];
		tmp->kind = ENEMY;
		tmp->health = 5;
		tmp->animFrame = 0;
	}

	//Setup the enemy bolt pool.
	enemy_bolt_pool = init_smartItemPool(ENEMY_BOLT_POOL_SIZE, (void *(*)())&init_proj);
	for (i = 0; i < enemy_bolt_pool->poolsize; i++) {
		PROJP tmp = (PROJP)enemy_bolt_pool->pool[i];
		tmp->kind = ENEMYBOLT;
		tmp->health = 1;
		tmp->animFrame = 0;
	}

	//The +1 is for the ship projectile, the *4 is for the 4 corners of each projectile.
	node_pool = init_smartItemPool((AST_POOL_SIZE + PROJ_POOL_SIZE + ENEMY_POOL_SIZE + ENEMY_BOLT_POOL_SIZE + 1) * 4, (void *(*)())&init_node);

	// Set initial backdrop y position because this can't be done in the definitions C file beause reasons
	backdropy = (SCREEN_H - BACKDROP_H) / 2;

	// More "non-const" initialization??
	ship_cooldown = SHOT_COOLDOWN_MAX;
	ast_cooldown = AST_COOLDOWN_MAX;

	// Set up collision array
	collision_array_width = (SCREEN_W / 100);
	collision_array_height = (SCREEN_H / 100);
	collision_array = (COLLBOX **)malloc(collision_array_width*sizeof(COLLBOX *));
	for(i = 0; i < collision_array_width; i++)
		collision_array[i] = (COLLBOX *)malloc(collision_array_height*sizeof(COLLBOX));

	//Return 0 if everything went okay.
	return 0;
}