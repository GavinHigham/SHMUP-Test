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

int main()
{
	//Initializing a bunch of modules.
	if (init_stuff()) return -1;

	//Loading in the textures.
	if (load_textures()) return -1;

	//Setup the ship projectile.
	ship->posX = SCREEN_W / 4;
	ship->posY = SCREEN_H / 2;

	event_queue = al_create_event_queue();
	if(!event_queue) {
		fprintf(stderr, "failed to create event_queue!\n");
		al_destroy_display(display);
		al_destroy_timer(timer);
		return -1;
	}
 
	al_register_event_source(event_queue, al_get_display_event_source(display));
	al_register_event_source(event_queue, al_get_timer_event_source(timer));
	al_register_event_source(event_queue, al_get_keyboard_event_source());
	al_start_timer(timer);
 
	while(!doexit) {
		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);
		
		if (ev.type == ALLEGRO_EVENT_TIMER) {
			logic_tick();
			redraw = true;
		}
		else if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) break;
		else if(ev.type == ALLEGRO_EVENT_KEY_DOWN) key_down(ev);
		else if(ev.type == ALLEGRO_EVENT_KEY_UP) key_up(ev);
		if(redraw && al_is_event_queue_empty(event_queue)) game_draw();
	}

	//Free all the things!
	for (i = 0; i < 60; i++) al_destroy_bitmap(asteroidFrames[i]);
	for (i = 0; i < 12; i++) al_destroy_bitmap(boltFrames[i]);
	for (i = 0; i < 120; i++) al_destroy_bitmap(shipFrames[i]);
	for (i = 0; i < 35; i++) al_destroy_bitmap(blastFrames[i]);
	al_destroy_bitmap(backdrop);
	al_destroy_timer(timer);
	al_destroy_display(display);
	al_destroy_event_queue(event_queue);
	//free_projectile(ship);
	free_smartItemPool(sl_pool);
	free_smartItemPool(ast_pool);
	free_smartItemPool(blast_pool);
	free_smartItemPool(node_pool);

	return 0;
}
