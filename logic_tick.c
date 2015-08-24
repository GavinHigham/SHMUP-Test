#include "logic_tick.h"
#include "definitions.h"
#include "proj.h"
#include "collision.h"
#include "game_entities.h"
#include "game_pools.h"
#include <math.h>
//int logicTick = 0;

void aimEnemyShot(PROJP ship, PROJP enemyShot) {
	float velocity = 5;
	float xDist = ship->posX - enemyShot->posX;
	float yDist = ship->posY - enemyShot->posY;
	float hyp = sqrt(pow(xDist, 2) + pow(yDist, 2));
	enemyShot->velX = (xDist / hyp) * velocity;
	enemyShot->velY = (yDist / hyp) * velocity;
}

void shipExplosion(PROJP ship, PROJP explosion) {
	float xOffset = 20;
	float yOffset = 15;
	explosion = (PROJP)new_pool_item(blast_pool);
	if (explosion) {
		explosion->posX = ship->posX + xOffset + (rand() % 55);
		explosion->posY = ship->posY + yOffset + (rand() % 14);
		explosion->velX = ship->velX * 0.6;
		explosion->velY = ship->velY * 0.6;
	}
}

void logic_tick()
{
	//printf("timescale: %f\n", timescale);
	backAx = backAx + (timescale * 9);
	if (backAx >= 960) backAx -= 1920;

	if (regen > 0) regen --;

	//timescale = (100 - attention) / 100.0;
	//if (timescale < 0.01) timescale = 0.01;

	if (!regen) {
		ship->health += (meditation / 50);
		regen = REGEN_COOLDOWN_MAX;
	}
	if (ship->health < 0) {
		ship->health = 100;
		explosion_countdown = 1500;
		lost = true;
	}
	if (lost && explosion_countdown > 0) {
		explosion_countdown -= timescale;
		PROJP blastEffect = (PROJP)new_pool_item(blast_pool);
		blastEffect->health = 34;
		shipExplosion(ship, blastEffect);
	}

	if (ship_cooldown > 0) ship_cooldown -= timescale;
	if (ast_cooldown > 0) ast_cooldown -= timescale;
	if (enemy_cooldown > 0) enemy_cooldown -= timescale;
	if (enemy_bolt_cooldown > 0) enemy_bolt_cooldown -= timescale;

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
		shipFrame += 3 * timescale;
		if (shipFrame > 58) shipFrame = 58;
		if (backdropy < 0) backdropy += 0.1;
	}
	if(key[KEY_DOWN]) {
		ship->velY += stdv;
		shipFrame -= 3 * timescale;
		if (shipFrame < 1) shipFrame = 1;
		if (backdropy + BACKDROP_H > SCREEN_H) backdropy -= 0.1;
	}
	if(key[KEY_LEFT]) {
		ship->velX -= stdv;
		if (backdropx < 0) backdropx += 0.1;
	}
	if(key[KEY_RIGHT]) {
		ship->velX += stdv;
		if (backdropx + BACKDROP_W > SCREEN_W) backdropx -= 0.1;
	}

	if (ship->velX && ship->velY) {
		ship->velX *= diagscale;
		ship->velY *= diagscale;
	}

	if (shipFrame > 29) shipFrame -= 2 * timescale;
	if (shipFrame < 29) shipFrame += 2 * timescale;

	update_proj_position(ship);

	//Update the ship's laser pool projectile positions.
	update_pool(sl_pool, &proj_update);

	//Creation and swapping of laser projectiles.
	if (key[KEY_SPACE] && ship_cooldown <= 0 && sl_pool->liveIndex+1 < sl_pool->poolsize) {
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
		if (ship_cooldown <= 0) ship_cooldown = SHOT_COOLDOWN_MAX;
	}
	
	//Update the asteroid positions.
	update_pool(ast_pool, &proj_update);
	
	for (int i = 0; i < 6; i++) {
		//Creation and swapping of asteroids.
		if (ast_cooldown <= 0 && ast_pool->liveIndex+1 < ast_pool->poolsize) {
			PROJP tmp_new = (PROJP)new_pool_item(ast_pool);
			tmp_new->health = 1;
			tmp_new->posX = SCREEN_W + MARGIN;
			tmp_new->posY = (rand() % SCREEN_H);
			tmp_new->velX = (rand() % 3) - 4;
			tmp_new->velY = (rand() % 5) - 2;
			if (ast_cooldown <= 0) ast_cooldown = AST_COOLDOWN_MAX;
			//printf("%i\n", ast_pool->liveIndex);
		}
	}

	update_pool(enemy_pool, &proj_update);

	for (int i = 0; i < 10; i++) {
		//Creation and swapping of enemies.
		if (enemy_cooldown <= 0 && enemy_pool->liveIndex+1 < enemy_pool->poolsize) {
			PROJP tmp_new = (PROJP)new_pool_item(enemy_pool);
			tmp_new->health = 5;
			tmp_new->posX = SCREEN_W + MARGIN;
			tmp_new->posY = (rand() % SCREEN_H);
			tmp_new->velX = - 2.5;
			if (enemy_cooldown <= 0) enemy_cooldown = ENEMY_COOLDOWN_MAX;
		}
	}

	update_pool(enemy_bolt_pool, &proj_update);

	for (int i = 0; i < 2; i++) {
		if (enemy_pool->liveIndex > 0) {
			PROJP aggressor = enemy_pool->pool[rand() % (enemy_pool->liveIndex)];
			//Creation and swapping of enemy bolts.
			if (!proj_offscreen(aggressor, SCREEN_W, SCREEN_H, -10) && enemy_bolt_cooldown <= 0 && enemy_bolt_pool->liveIndex < enemy_bolt_pool->poolsize) {
				PROJP tmp_new = (PROJP)new_pool_item(enemy_bolt_pool);
				tmp_new->health = 1;
				tmp_new->posX = aggressor->posX + 15;
				tmp_new->posY = aggressor->posY + 50;
				aimEnemyShot(ship, tmp_new);
				if (enemy_bolt_cooldown <= 0) enemy_bolt_cooldown = ENEMY_BOLT_COOLDOWN_MAX;
			}
		}
	}

	update_pool(blast_pool, &proj_update);
	for (int i = 0; i < blast_pool->liveIndex; i++) {
		if (((PROJP)blast_pool->pool[i])->health > 0) ((PROJP)blast_pool->pool[i])->health--;
	}
	
	clear_collboxes();
	//printf("It broke after clearing.\n");
	//printf("Checking in the ship:\n");
	check_in_proj(ship);
	//printf("It broke after ship check-in\n");
	check_in_smartpool(sl_pool);
	check_in_smartpool(ast_pool);
	check_in_smartpool(enemy_pool);
	check_in_smartpool(enemy_bolt_pool);
	//printf("Smartpool check-in was successful.\n");
	do_collision();
	//printf("Collision was successful.\n");

}