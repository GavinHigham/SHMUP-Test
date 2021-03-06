//C stuff.
#include "proj.h"
#include "struct_pool.h"
#include <stdio.h>
#include <stdlib.h>
//Allegro stuff.
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
//My stuff.

//Inits a proj and zeroes most of the values.
PROJP init_proj()
{
	PROJP pp = (PROJP)malloc(sizeof(PROJ));
	pp->posX = 0;
	pp->posY = 0;
	pp->velX = 0;
	pp->velY = 0;
	pp->sizeX = 0;
	pp->sizeY = 0;
	pp->offsetX = 0;
	pp->offsetY = 0;
	pp->animFrame = rand() % 60;
	pp->health = 1;
	return pp;
}

//Self explanatory really.
void update_proj_position(PROJP pp)
{
	pp->posX += pp->velX;
	pp->posY += pp->velY;
}

//Returns 1 if a PROJ has no health.
int no_health(PROJP pp)
{
	return (pp->health <= 0);
}

//Returns 1 if a projectile is offscreen, 0 otherwise.
//Margin is how many pixels beyond the screen the proj should be to return 1.
int proj_offscreen(PROJP pp, int screen_w, int screen_h, int margin)
{
	return ((pp->posX > (screen_w + margin)) || (pp->posX < (0 - margin)) ||
		(pp->posY > (screen_h + margin)) || (pp->posY < (0 - margin)) );
}

//Mostly the same as above.
//This one takes only one argument so it can be passed as a function pointer with filled-in values.
int offscreen(PROJP pp)
{
	return proj_offscreen(pp, SCREEN_W, SCREEN_H, MARGIN);
}

//Update function for a projectile.
void proj_update(SPP sp, int i)
{
	PROJP tmp = (PROJP)sp->pool[i];
	if (tmp->health <= 0 || offscreen(tmp)) {
		tmp->health = 0;
		kill_item(sp, i);
	}
	tmp = sp->pool[i]; //A different item may now be at i due to kill_item.
	update_proj_position(tmp);

	tmp->animFrame++;
	tmp->animFrame %= 60;
}

