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
		case ALLEGRO_KEY_1:
			timescale = 0.1;
			break;
		case ALLEGRO_KEY_2:
			timescale = 0.2;
			break;
		case ALLEGRO_KEY_3:
			timescale = 0.3;
			break;
		case ALLEGRO_KEY_4:
			timescale = 0.4;
			break;
		case ALLEGRO_KEY_5:
			timescale = 0.5;
			break;
		case ALLEGRO_KEY_6:
			timescale = 0.6;
			break;
		case ALLEGRO_KEY_7:
			timescale = 0.7;
			break;
		case ALLEGRO_KEY_8:
			timescale = 0.8;
			break;
		case ALLEGRO_KEY_9:
			timescale = 0.9;
			break;
		case ALLEGRO_KEY_0:
			timescale = 1;
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