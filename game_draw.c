#include "game_draw.h"
#include "definitions.h"
//C stuff.
#include <stdio.h>
#include <stdlib.h>
//Allegro stuff.
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>


void game_draw()
{
	//Calculate dynamic planet locations and sizes.
	float planet_sm_theta_rad = deg_to_rad(planet_sm_theta);
	float planet_distance = sqrt(pow(cameraX - orbit_r * cos(planet_sm_theta_rad), 2) + pow(cameraY - orbit_r * sin(planet_sm_theta_rad), 2));
	float w_screen = atan2(200, planet_distance) / deg_to_rad(viewing_angle) * 580;
	float x_screen = cos(planet_sm_theta_rad) * (SCREEN_W / 2) - (w_screen / 2) + (SCREEN_W / 2);
	float backdropx_less = backdropx / 0.9;
	float backdropy_less = backdropy / 0.9;
	
	redraw = false;
	//al_clear_to_color(al_map_rgb(255,255,255));
	//al_draw_bitmap(backdrop, backdropx, backdropy, 0);

	//Draw the stars behind the planets.
	al_draw_bitmap(bg_stars, backdropx, backdropy, 0);
	//If the small planet is behind the big planet, draw it first.
	if (planet_sm_theta >= 180 || planet_sm_theta < 0)
		al_draw_scaled_bitmap(planet_sm, 0, 0, 580, 580, x_screen + backdropx_less, 700 + backdropy_less - (w_screen / 2), w_screen, w_screen, 0);
	//Draw the big planet.
	al_draw_scaled_bitmap(planet_lg, 0, 0, 1000, 1000, backdropx_less + 160, 450 + backdropy_less, 500, 500, 0); //Hard coded values for planet_lg source size.
	//If the small planet is in front of the big planet, draw it second.
	if (planet_sm_theta > 0 && planet_sm_theta < 180)
		al_draw_scaled_bitmap(planet_sm, 0, 0, 580, 580, x_screen + backdropx_less, 700 + backdropy_less - (w_screen / 2), w_screen, w_screen, 0);


	for (i = 0; i < ast_pool->liveIndex; i++) {
		//printf("Attempting to draw asteroid %4i\n", i);
		al_draw_bitmap(asteroidFrames[((PROJP)ast_pool->pool[i])->animFrame], ((PROJP)ast_pool->pool[i])->posX, ((PROJP)ast_pool->pool[i])->posY, 0);
		//printf("Successfully drew asteroid  %4i\n", i);
	}

	//Draw the bolts.
	for (i = 0; i < sl_pool->liveIndex; i++) {
		al_draw_bitmap(boltFrames[boltFrame=(++boltFrame%12)], ((PROJP)sl_pool->pool[i])->posX, ((PROJP)sl_pool->pool[i])->posY, 0);
	}

	//Draw the ship.
	al_draw_bitmap(shipFrames[(int)shipFrame+shipFramesetSwap], ship->posX, ship->posY, 0);

	//Draw the blasts.
	for (i = 0; i < blast_pool->liveIndex; i++) {
		al_draw_bitmap(blastFrames[34 - ((PROJP)blast_pool->pool[i])->health], ((PROJP)blast_pool->pool[i])->posX, ((PROJP)blast_pool->pool[i])->posY, 0);
	}

	al_flip_display();
}
