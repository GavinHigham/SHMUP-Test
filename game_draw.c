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

//Draw all the things.
void game_draw()
{
	redraw = false;
	//al_clear_to_color(al_map_rgb(255,255,255));
	al_draw_bitmap(backdrop, backdropx, backdropy, 0);

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
	fps++;
}
