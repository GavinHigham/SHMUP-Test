#pragma once

//#define ROOT
const int SCREEN_W = 800;
const int SCREEN_H = 600;
const int MARGIN = 300;
const int FPS = 60;
const int PROJ_POOL_SIZE = 1000;
const int AST_POOL_SIZE = 2000;
const int ENEMY_POOL_SIZE = 200;
const int ENEMY_BOLT_POOL_SIZE = 200;
const int BACKDROP_H = 1200;
const int BACKDROP_W = 1920;
const int SHOT_COOLDOWN_MAX = 10;
const int AST_COOLDOWN_MAX = 2;
const int REGEN_COOLDOWN_MAX = 20;
const int ENEMY_COOLDOWN_MAX = 40;
const int ENEMY_BOLT_COOLDOWN_MAX = 20;
int SHOT_SPREAD = 1;
int SHOT_OFFSET_X = 69;
int SHOT_OFFSET_Y = 20;
float planet_sm_theta = 180;
float viewing_angle = 80;
float orbit_r = 400;
float cameraX = 0;
float cameraY = 800;
float timescale = 1.0;

typedef long long unsigned int llui;

//A 2D floating-point vector.
typedef struct vector {
	float x;
	float y;
} VECTOR, *VP;

//A 2D integer vector.
typedef struct ivector {
	int x;
	int y;
} IVECT, *IVP;

typedef struct projectile {
	float posX;
	float posY;
	float velX;
	float velY;
	int sizeX;
	int sizeY;
	int offsetX;
	int offsetY;
	//void *next; //Used for collision.
	int animFrame;
	//Used for temporary information.
	//DO NOT EXPECT IT TO BE ACCURATE UNLESS UPDATED AND USED IMMEDIATELY.
	int index;
	struct projectile *next;
	int kind;
	int health;
} PROJ, *PROJP;

//"Kind" will be an integer, but I enumerate its possible values here.
enum {SHIP, BOLT, ASTEROID, ENEMY, BLAST, ENEMYBOLT};

typedef struct smartpool {
	void **pool;
	int poolsize;
	int liveIndex;
} SMARTPOOL, *SPP;

typedef struct node {
	PROJP data;
	struct node *next;
	int index; //Allows for easier killing.
} NODE, *NODEP;

typedef struct nodepool {
	void **pool;
	int poolsize;
	int liveIndex;
} NODEPOOL, *NPP;

typedef struct collbox {
	NODEP ship;
	NODEP bolts;
	NODEP asteroids;
	NODEP enemies;
	NODEP enemy_bolts;
} COLLBOX, *COLLBOXP;

VECTOR struct_zero_vector = {0, 0};
VP zero_vec = &struct_zero_vector;
int numcolgroups = 0;

int i;
//Standard velocity.
float stdv = 4.5;
//Value to scale x and y vel by if both keys are pressed.
float diagscale = 0.71;
int backdropx = 0;
int backdropy = (SCREEN_H - BACKDROP_H) / 2;
float backAx = 0;

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
ALLEGRO_BITMAP *bg_starsA = NULL;
ALLEGRO_BITMAP *bg_starsB = NULL;
ALLEGRO_BITMAP *planet_lg = NULL;
ALLEGRO_BITMAP *planet_sm = NULL;
ALLEGRO_BITMAP *health_tray = NULL;
ALLEGRO_BITMAP *health_bar = NULL;
ALLEGRO_BITMAP *badguy = NULL;
ALLEGRO_BITMAP *enemy_bolt_sprite = NULL;
ALLEGRO_BITMAP *loss = NULL;

PROJP ship;
int ship_spread_index = 0;
float ship_cooldown = SHOT_COOLDOWN_MAX;
float ast_cooldown = AST_COOLDOWN_MAX;
float enemy_cooldown = ENEMY_COOLDOWN_MAX;
float enemy_bolt_cooldown = ENEMY_BOLT_COOLDOWN_MAX;
float explosion_countdown = 0;
bool lost = false;
int attention = 0;
int meditation = 0;
float regen = 0;

SPP sl_pool;
SPP ast_pool;
SPP blast_pool;
SPP enemy_pool;
SPP enemy_bolt_pool;
SPP node_pool;

enum {KEY_UP, KEY_DOWN, KEY_LEFT, KEY_RIGHT, KEY_SPACE};
bool key[5] = { false, false, false, false };

COLLBOX collision_array[SCREEN_W / 100][SCREEN_H / 100];