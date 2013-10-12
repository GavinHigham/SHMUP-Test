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

void key_down(ALLEGRO_EVENT ev)
{
	switch(ev.keyboard.keycode) {
		case ALLEGRO_KEY_W:
			key[KEY_UP] = true;
			break;

		case ALLEGRO_KEY_S:
			key[KEY_DOWN] = true;
			break;

		case ALLEGRO_KEY_A: 
			key[KEY_LEFT] = true;
			break;

		case ALLEGRO_KEY_D:
			key[KEY_RIGHT] = true;
			break;

		case ALLEGRO_KEY_SPACE:
			key[KEY_SPACE] = true;
			break;
	}
}

void key_up(ALLEGRO_EVENT ev)
{
	switch(ev.keyboard.keycode) {
				case ALLEGRO_KEY_W:
					key[KEY_UP] = false;
					break;
			 
				case ALLEGRO_KEY_S:
					key[KEY_DOWN] = false;
					break;
			 
				case ALLEGRO_KEY_A: 
					key[KEY_LEFT] = false;
					break;
			 
				case ALLEGRO_KEY_D:
					key[KEY_RIGHT] = false;
					break;

				case ALLEGRO_KEY_SPACE:
					key[KEY_SPACE] = false;
					break;
			 
				case ALLEGRO_KEY_ESCAPE:
					doexit = true;
					break;
	}
}