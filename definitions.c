#include "definitions.h"

const int SCREEN_W = 800;
const int SCREEN_H = 600;
const int MARGIN = 300;
const int FPS = 60;
const int PROJ_POOL_SIZE = 1000;
const int AST_POOL_SIZE = 200;
const int ENEMY_POOL_SIZE = 200;
const int ENEMY_BOLT_POOL_SIZE = 200;
const int BACKDROP_H = 1200;
const int BACKDROP_W = 1920;
const int SHOT_COOLDOWN_MAX = 10;
const int AST_COOLDOWN_MAX = 8;
int SHOT_SPREAD = 1;
int SHOT_OFFSET_X = 69;
int SHOT_OFFSET_Y = 20;
float planet_sm_theta = 180;
float viewing_angle = 80;
float orbit_r = 400;
float cameraX = 0;
float cameraY = 800;

VECTOR struct_zero_vector = {0, 0};
VP zero_vec = &struct_zero_vector;
int numcolgroups = 0;

int i;
//Standard velocity.
float stdv = 4.5;
//Value to scale x and y vel by if both keys are pressed.
float diagscale = 0.71;
int backdropx = 0;
int backdropy = 0;

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
ALLEGRO_BITMAP *shipFrames[120];
ALLEGRO_BITMAP *backdrop = NULL;
ALLEGRO_BITMAP *bg_stars = NULL;
ALLEGRO_BITMAP *planet_lg = NULL;
ALLEGRO_BITMAP *planet_sm = NULL;

PROJP ship;
int ship_spread_index = 0;
int ship_cooldown = 0;
int ast_cooldown = 0;

SPP sl_pool;
SPP ast_pool;
SPP blast_pool;
SPP enemy_pool;
SPP enemy_bolt_pool;
SPP node_pool;

bool key[5] = { false, false, false, false };

COLLBOX **collision_array;