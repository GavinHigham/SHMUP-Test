#ifndef GAME_DRAW_H
#define GAME_DRAW_H

//Allegro stuff.
#include <allegro5/allegro_primitives.h>
#include "definitions.h"

#define VERTSPERQUAD 6

extern ALLEGRO_VERTEX ast_vtx[AST_POOL_SIZE*6];

void setVertex(ALLEGRO_VERTEX vtx[], int i, float x, float y, float z, float u, float v, ALLEGRO_COLOR color);

//Draw all the things.
void game_draw();

#endif