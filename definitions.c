#include "definitions.h"

VECTOR struct_zero_vector = {0, 0};
VP zero_vec = &struct_zero_vector;
int numcolgroups = 0;

int i;
short fps = 0;
short logicTick = 0;
//Standard velocity.
float stdv = 4.5;
//Value to scale x and y vel by if both keys are pressed.
float diagscale = 0.71;
int backdropx = 0;
int backdropy = (SCREEN_H - BACKDROP_H) / 2;

ALLEGRO_DISPLAY *display   = NULL;
ALLEGRO_EVENT_QUEUE *event_queue = NULL;
ALLEGRO_TIMER *timer = NULL;

bool redraw = true;
bool doexit = false;

short boltFrame = 0;
int shipFrame = 29;
int shipFramesetSwap = 60;
ALLEGRO_BITMAP *boltFrames[12];
ALLEGRO_BITMAP *asteroidFrames[60];
ALLEGRO_BITMAP *blastFrames[36];
ALLEGRO_BITMAP *backdrop = NULL;
ALLEGRO_BITMAP *shipFrames[120];

PROJP ship;
int ship_spread_index = 0;
int ship_cooldown = SHOT_COOLDOWN;
int ast_cooldown = AST_COOLDOWN;

SPP sl_pool;
SPP ast_pool;
SPP blast_pool;
SPP node_pool;

//enum {KEY_UP, KEY_DOWN, KEY_LEFT, KEY_RIGHT, KEY_SPACE};
bool key[5] = { false, false, false, false };

COLLBOX collision_array[SCREEN_W / 100][SCREEN_H / 100];