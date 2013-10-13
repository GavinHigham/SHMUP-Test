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

int load_textures()
{
	/*
	//Load in the backdrop.
	backdrop = al_load_bitmap("MoonBrushTest.jpg");
	if (!backdrop) printf("Backdrop failed to load.\n");
	*/
	bg_starsA = al_load_bitmap("Backdrops/bg_starsA.jpg");
	bg_starsB = al_load_bitmap("Backdrops/bg_starsB.jpg");
	planet_lg = al_load_bitmap("Backdrops/planet_lg2.png");
	planet_sm = al_load_bitmap("Backdrops/planet_sm.png");

	if (!bg_starsA || !bg_starsB || !planet_sm || !planet_lg) printf("Some part of the backdrop failed to load.\n");

	health_tray = al_load_bitmap("HealthBar/HealthBarTray.png");
	health_bar = al_load_bitmap("HealthBar/HealthBar.png");
	loss = al_load_bitmap("Backdrops/loss.png");

	badguy = al_load_bitmap("BadGuy/BadGuy.png");
	enemy_bolt_sprite = al_load_bitmap("EnemyBolt/EnemyBolt.png");

	//Loading in the bolt frames.
	for (i = 0; i < 12; i++) {
		char path[] = "Bolt/bolt0000.png\0";
		boltFrames[i] = NULL;
		path[11] = i/10 + '0';
		path[12] = i%10 + '0';
		boltFrames[i] = al_load_bitmap(path);
	}

	//Loading in the asteroid frames.
	for (i = 0; i < 60; i++) {
		char path[] = "Aster4/aster0000.png\0";
		asteroidFrames[i] = NULL;
		//printf("Loading %2i: ", i);
		path[14] = i/10 + '0';
		path[15] = i%10 + '0';
		asteroidFrames[i] = al_load_bitmap(path);
		//if (asteroidFrames[i]) printf("Successfully loaded frame %2i from %s\n", i, path);
		if (!(al_get_bitmap_flags(asteroidFrames[i]) & ALLEGRO_VIDEO_BITMAP))
			printf("Asteroid %2i is not hardware-accelerated!\n", i);
	}

	//Loading ship frames.
	for (i = 0; i < 60; i++) {
		char path[] = "Ship1/ship0000.png\0";
		shipFrames[i] = NULL;
		path[12] = i/10 + '0';
		path[13] = i%10 + '0';
		shipFrames[i] = al_load_bitmap(path);
	}
	//These are an alternate set with a different seed value for flares.
	//That way the ship rockets never appear static.
	for (i = 0; i < 60; i++) {
		char path[] = "Ship2/ship0000.png\0";
		shipFrames[i+60] = NULL;
		path[12] = i/10 + '0';
		path[13] = i%10 + '0';
		shipFrames[i+60] = al_load_bitmap(path);
	}
	
	//Loading in the explosion frames.
	for (i = 0; i < 35; i++) {
		char path[] = "smoke/smoke0000.png\0";
		blastFrames[i] = NULL;
		//printf("Loading %2i: ", i);
		path[13] = i/10 + '0';
		path[14] = i%10 + '0';
		blastFrames[i] = al_load_bitmap(path);
		//if (blastFrames[i]) printf("Successfully loaded frame %2i from %s\n", i, path);
		if (!(al_get_bitmap_flags(blastFrames[i]) & ALLEGRO_VIDEO_BITMAP))
			printf("Blast %2i is not hardware-accelerated!\n", i);
	}

	return 0;
}