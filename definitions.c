#include "definitions.h"

int MARGIN = 300;
int FPS = 60;
const int PROJ_POOL_SIZE = 1000;
const int ENEMY_POOL_SIZE = 200;
const int ENEMY_BOLT_POOL_SIZE = 200;
const int SHOT_COOLDOWN_MAX = 4;
const int AST_COOLDOWN_MAX = 3;
const int REGEN_COOLDOWN_MAX = 20;
const int ENEMY_COOLDOWN_MAX = 45;
const int ENEMY_BOLT_COOLDOWN_MAX = 35;
int SHOT_SPREAD = 0;
int SHOT_OFFSET_X = 69;
int SHOT_OFFSET_Y = 20;
float planet_sm_theta = 180;
float viewing_angle = 80;
float orbit_r = 400;
float cameraX = 0;
float cameraY = 800;
int attention = 0;
int meditation = 0;
float regen = 0;
float timescale = 1;

// If the project compiles and runs, these can be deleted.
// VECTOR struct_zero_vector = {0, 0};
// VP zero_vec = &struct_zero_vector;
int numcolgroups = 0;

//Standard velocity.
float stdv = 4.5;
//Value to scale x and y vel by if both keys are pressed.
float diagscale = 0.71;
float backdropx = 0;
float backdropy = (SCREEN_H - BACKDROP_H) / 2;
float backAx = 0;

ALLEGRO_DISPLAY *display   = NULL;
ALLEGRO_EVENT_QUEUE *event_queue = NULL;
ALLEGRO_TIMER *timer = NULL;

bool redraw = true;
bool doexit = false;

short boltFrame = 0;
float shipFrame = 29;
int shipFramesetSwap = 60;
ALLEGRO_BITMAP *boltFrames[12];
ALLEGRO_BITMAP *asteroidFrames[60];
ALLEGRO_BITMAP *blastFrames[36];
ALLEGRO_BITMAP *shipFrames[120];
ALLEGRO_BITMAP *backdrop = NULL;
ALLEGRO_BITMAP *bg_starsA = NULL;
ALLEGRO_BITMAP *bg_starsB = NULL;
ALLEGRO_BITMAP *planet_lg = NULL;
ALLEGRO_BITMAP *planet_sm = NULL;
ALLEGRO_BITMAP *health_tray = NULL;
ALLEGRO_BITMAP *health_bar = NULL;
ALLEGRO_BITMAP *badguy = NULL;
ALLEGRO_BITMAP *enemy_bolt_sprite = NULL;
ALLEGRO_BITMAP *loss = NULL;
ALLEGRO_BITMAP *asteroid = NULL;

int ship_spread_index = 0;
float ship_cooldown = SHOT_COOLDOWN_MAX;
float ast_cooldown = AST_COOLDOWN_MAX;
float enemy_cooldown = ENEMY_COOLDOWN_MAX;
float enemy_bolt_cooldown = ENEMY_BOLT_COOLDOWN_MAX;
float explosion_countdown = 0;
bool lost = false;
bool key[5] = { false, false, false, false };
