#pragma once

//C stuff.
#include <stdio.h>
#include <stdlib.h>
//Allegro stuff.
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
//My stuff.
#ifndef GUARDCHECK
	#include "definitions.h"
#endif
#include "proj.c"

void logic_tick()
{
	if (regen > 0) regen --;

	timescale = (100 - attention) / 100.0;
	if (timescale == 0) timescale = 0.01;

	if (!regen) {
		ship->health += (meditation / 50);
		regen = REGEN_COOLDOWN_MAX;
	}
	if (ship->health < 0) ship->health = 100;
	if (ship_cooldown > 0) ship_cooldown -= timescale;
	if (ast_cooldown > 0) ast_cooldown -= timescale;

	shipFramesetSwap^=60; //DON'T WORRY ABOUT IT :)
	planet_sm_theta += 0.5 * timescale;
	if (planet_sm_theta > 360) planet_sm_theta -= 360;

	/*
	if (logicTick >= 60) {
		printf("FPS: %2i, Pool Size: %4i, Ship health: %3i\n", fps, ast_pool->liveIndex, ship->health);
		fps = logicTick = 0;
	}
	logicTick++;
	*/

	ship->velX = 0;
	ship->velY = 0;
	//Checking ship movement keys.
	if(key[KEY_UP]) {
		ship->velY -= stdv;
		if (shipFrame < 58) shipFrame+= 3;
		if (backdropy < 0) backdropy++;
	}
	if(key[KEY_DOWN]) {
		ship->velY += stdv;
		if (shipFrame > 1) shipFrame-= 3;
		if (backdropy + BACKDROP_H > SCREEN_H) backdropy--;
	}
	if(key[KEY_LEFT]) {
		ship->velX -= stdv;
		if (backdropx < 0) backdropx++;
	}
	if(key[KEY_RIGHT]) {
		ship->velX += stdv;
		if (backdropx + BACKDROP_W > SCREEN_W) backdropx--;
	}

	if (ship->velX && ship->velY) {
		ship->velX *= diagscale;
		ship->velY *= diagscale;
	}

	if (shipFrame > 29) shipFrame-=2;
	if (shipFrame < 29) shipFrame+=2;

	update_proj_position(ship);

	//Update the ship's laser pool projectile positions.
	update_pool(sl_pool, &proj_update);

	//Creation and swapping of laser projectiles.
	if (key[KEY_SPACE] && !ship_cooldown && sl_pool->liveIndex < sl_pool->poolsize) {
		PROJP tmp_new = (PROJP)new_pool_item(sl_pool);
		tmp_new->health = 1;
		tmp_new->posX = ship->posX + SHOT_OFFSET_X;
		tmp_new->posY = ship->posY + SHOT_OFFSET_Y;
		tmp_new->velX = 15;
		tmp_new->velY = 0;
		//tmp_new->velY = (rand() % SHOT_SPREAD) - (SHOT_SPREAD/2);
		//tmp_new->velY = ship_spread_index - (SHOT_SPREAD/2);
		//Alternate method of having "spread"
		//ship_spread_index--;
		//if (ship_spread_index <= 0) ship_spread_index = SHOT_SPREAD;
		if (ship_cooldown == 0) ship_cooldown = SHOT_COOLDOWN_MAX;
	}
	
	//Update the asteroid positions.
	update_pool(ast_pool, &proj_update);
	
	for (i = 0; i < 10; i++) {
		//Creation and swapping of asteroids.
		if (!ast_cooldown && ast_pool->liveIndex < ast_pool->poolsize) {
			PROJP tmp_new = (PROJP)new_pool_item(ast_pool);
			tmp_new->health = 1;
			tmp_new->posX = SCREEN_W + MARGIN;
			tmp_new->posY = (rand() % SCREEN_H);
			tmp_new->velX = (rand() % 3) - 4;
			tmp_new->velY = (rand() % 5) - 2;
			if (ast_cooldown == 0) ast_cooldown = AST_COOLDOWN_MAX;
			//printf("%i\n", ast_pool->liveIndex);
		}
	}

	update_pool(blast_pool, &proj_update);
	for (i = 0; i < blast_pool->liveIndex; i++) {
		if (((PROJP)blast_pool->pool[i])->health > 0) ((PROJP)blast_pool->pool[i])->health--;
	}
	
	clear_collboxes();
	//printf("It broke after clearing.\n");
	//printf("Checking in the ship:\n");
	check_in_proj(ship);
	//printf("\n");
	//printf("It broke after ship check-in\n");
	check_in_smartpool(sl_pool);
	check_in_smartpool(ast_pool);
	//printf("Smartpool check-in was successful.\n");
	do_collision();
	//printf("Collision was successful.\n");

}