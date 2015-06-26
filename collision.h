#ifndef COLLISION_H
#define COLLISION_H

#include "struct_pool.h"
#include "definitions.h"

typedef struct collbox {
	NODEP ship;
	NODEP bolts;
	NODEP asteroids;
	NODEP enemies;
	NODEP enemy_bolts;
} COLLBOX, *COLLBOXP;

extern COLLBOX collision_array[SCREEN_W / 100][SCREEN_H / 100];

NODEP init_node();

//========================================

void safe_newBlastEffect(PROJP source);

void ship_aster_coll(PROJP ship, PROJP asteroid);
void ship_bolt_coll(PROJP ship, PROJP bolt);
void bolt_aster_coll(PROJP bolt, PROJP asteroid);
void bolt_enemy_coll(PROJP bolt, PROJP enemy);
void handleCollision(PROJP proj1, PROJP proj2);

//Clears the collision array's buckets.
void clear_collboxes();

//Returns 0 if the point is not in given bounds, 0 to width, 0 to height.
int point_in_bounds(int width, int height, int pointX, int pointY);

//Checks if a point for a projectile is valid, checks it in to the collision array if it is.
void point_checkin(PROJP pp, int pointX, int pointY);
void check_in_proj(PROJP pp);

//Adds the projectiles from a smartpool to the collision array.
void check_in_smartpool(SPP sp);

//Returns 1 if the two projectiles are box colliding.
int box_colliding(PROJP proj1, PROJP proj2);
void find_collbox_collisions(COLLBOXP cbp);
void do_collision();

#endif