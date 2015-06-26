//C stuff.
#include <math.h>

#include "game_draw.h"
#include "game_entities.h"
#include "game_pools.h"
#include "trig.h"

#define VERTSPERQUAD 6

ALLEGRO_VERTEX ast_vtx[AST_POOL_SIZE*6];

void setVertex(ALLEGRO_VERTEX vtx[], int i, float x, float y, float z, float u, float v, ALLEGRO_COLOR color) {
	vtx[i].x = x;
	vtx[i].x = x;
	vtx[i].y = y;
	vtx[i].z = z;
	vtx[i].color = color;
	vtx[i].u = u;
	vtx[i].v = v;
}

//Draw all the things.
void game_draw()
{
	//Calculate dynamic planet locations and sizes.
	float planet_sm_theta_rad = deg_to_rad(planet_sm_theta);
	float planet_distance = sqrt(pow(cameraX - orbit_r * cos(planet_sm_theta_rad), 2) + pow(cameraY - orbit_r * sin(planet_sm_theta_rad), 2));
	float w_screen = atan2(200, planet_distance) / deg_to_rad(viewing_angle) * 580;
	float x_screen = cos(planet_sm_theta_rad) * (SCREEN_W / 2) - (w_screen / 2) + (SCREEN_W / 2);
	float backdropx_less = backdropx / 0.90;
	float backdropy_less = backdropy / 0.90;
	
	redraw = false;
	//al_clear_to_color(al_map_rgb(255,255,255));
	//al_draw_bitmap(backdrop, backdropx, backdropy, 0);

	//Draw the stars behind the planets.
	al_draw_bitmap(bg_starsA, backdropx + backAx, backdropy, 0);
	al_draw_bitmap(bg_starsB, backdropx + backAx + 960, backdropy, 0);
	al_draw_bitmap(bg_starsB, backdropx + backAx - 960, backdropy, 0);
	//If the small planet is behind the big planet, draw it first.
	if (planet_sm_theta >= 180 || planet_sm_theta < 0)
		al_draw_scaled_bitmap(planet_sm, 0, 0, 580, 580, x_screen + backdropx_less, 700 + backdropy_less - (w_screen / 2), w_screen, w_screen, 0);
	//Draw the big planet.
	al_draw_scaled_bitmap(planet_lg, 0, 0, 1000, 1000, backdropx_less + 160, 450 + backdropy_less, 500, 500, 0); //Hard coded values for planet_lg source size.
	//If the small planet is in front of the big planet, draw it second.
	if (planet_sm_theta > 0 && planet_sm_theta < 180)
		al_draw_scaled_bitmap(planet_sm, 0, 0, 580, 580, x_screen + backdropx_less, 700 + backdropy_less - (w_screen / 2), w_screen, w_screen, 0);

	//printf("%i\n", ast_pool->liveIndex);
	ALLEGRO_COLOR color = al_map_rgb(255, 255, 255);
	for (int i = 0; i < ast_pool->liveIndex; i++) {
		PROJP currentAst = ((PROJP)ast_pool->pool[i]);
		int x = currentAst->posX;
		int y = currentAst->posY;
		int frame = currentAst->animFrame;
		int vi = i*VERTSPERQUAD; //Vertex buffer index.
		setVertex(ast_vtx,   vi, x,    y,    0, frame*25,    0,  color);
		setVertex(ast_vtx, vi+1, x,    y+25, 0, frame*25,    25, color);
		setVertex(ast_vtx, vi+2, x+25, y,    0, frame*25+25, 0,  color);
		setVertex(ast_vtx, vi+3, x+25, y,    0, frame*25+25, 0,  color);
		setVertex(ast_vtx, vi+4, x,    y+25, 0, frame*25,    25, color);
		setVertex(ast_vtx, vi+5, x+25, y+25, 0, frame*25+25, 25, color);
	}
	al_draw_prim(ast_vtx, NULL, asteroid, 0, (ast_pool->liveIndex)*VERTSPERQUAD, ALLEGRO_PRIM_TRIANGLE_LIST);

	/*
	for (i = 0; i < ast_pool->liveIndex; i++) {
		//printf("Attempting to draw asteroid %4i\n", i);
		al_draw_bitmap(asteroidFrames[(int)((PROJP)ast_pool->pool[i])->animFrame], ((PROJP)ast_pool->pool[i])->posX, ((PROJP)ast_pool->pool[i])->posY, 0);
		//printf("Successfully drew asteroid  %4i\n", i);
	}
	*/

	//Draw the bolts.
	for (int i = 0; i < sl_pool->liveIndex; i++) {
		boltFrame = (boltFrame + 1) % 12;
		al_draw_bitmap(boltFrames[boltFrame], ((PROJP)sl_pool->pool[i])->posX, ((PROJP)sl_pool->pool[i])->posY, 0);
	}

	//Draw the ship.
	al_draw_bitmap(shipFrames[(int)shipFrame+shipFramesetSwap], ship->posX, ship->posY, 0);

	//Draw enemies.
	for (int i = 0; i < enemy_pool->liveIndex; i++) {
	al_draw_bitmap(badguy, ((PROJP)enemy_pool->pool[i])->posX, ((PROJP)enemy_pool->pool[i])->posY, 0);
	}

	//Draw the enemy bolts.
	for (int i = 0; i < enemy_bolt_pool->liveIndex; i++) {
		al_draw_bitmap(enemy_bolt_sprite, ((PROJP)enemy_bolt_pool->pool[i])->posX, ((PROJP)enemy_bolt_pool->pool[i])->posY, 0);
	}

	//printf("Live blasts: %i", blast_pool->liveIndex);
	//Draw the blasts.
	for (int i = 0; i < blast_pool->liveIndex; i++) {
		al_draw_bitmap(blastFrames[34 - ((PROJP)blast_pool->pool[i])->health], ((PROJP)blast_pool->pool[i])->posX, ((PROJP)blast_pool->pool[i])->posY, 0);
	}

	//Draw the health bar and health bar tray.
	al_draw_bitmap(health_tray, 0, 0, 0);
	int health_tray_width = (4 + 2*(ship->health));
	if (health_tray_width < 4) health_tray_width = 4;
	al_draw_bitmap_region(health_bar, 0, 0, health_tray_width, 19, 0, 0, 0);

	if (lost && explosion_countdown > 0) al_draw_bitmap(loss, 150, 150, 0);

	al_flip_display();
}
