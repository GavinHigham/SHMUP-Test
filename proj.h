#ifndef H_PROJ
#define H_PROJ
#include "definitions.h"

//Inits a proj and zeroes most of the values.
PROJP init_proj();

//Self explanatory really.
void update_proj_position(PROJP pp);

//Returns 1 if a PROJ has no health.
int no_health(PROJP pp);

//Returns 1 if a projectile is offscreen, 0 otherwise.
//Margin is how many pixels beyond the screen the proj should be to return 1.
int proj_offscreen(PROJP pp, int screen_w, int screen_h, int margin);

//Mostly the same as above.
//This one takes only one argument so it can be passed as a function pointer with filled-in values.
int offscreen(PROJP pp);

//Update function for a projectile.
void proj_update(SPP sp, int i);

#endif