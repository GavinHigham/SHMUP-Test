#ifndef H_DEFINITIONS
#define H_DEFINITIONS

#include <allegro5/allegro.h>

#define SCREEN_W 800
#define SCREEN_H 600
#define MARGIN 300
#define FPS 60
#define PROJ_POOL_SIZE 1000
#define AST_POOL_SIZE 200
#define SHOT_COOLDOWN 2
#define AST_COOLDOWN 8
#define SHOT_SPREAD 1
#define SHOT_OFFSET_X 69
#define SHOT_OFFSET_Y 20
#define BACKDROP_H 800
#define BACKDROP_W 1280
#define STARNUMBER 200
#define COLLISIONDIVISION 9

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
extern enum {SHIP, BOLT, ASTEROID, ENEMY, BLAST};

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
} COLLBOX, *COLLBOXP;

extern VECTOR struct_zero_vector;
extern VP zero_vec;
extern int numcolgroups;

extern int i; // wtf Gavin?
extern short fps;
extern short logicTick;
extern float stdv;
extern float diagscale;
extern int backdropx;
extern int backdropy;

extern ALLEGRO_DISPLAY *display;
extern ALLEGRO_EVENT_QUEUE *event_queue;
extern ALLEGRO_TIMER *timer;

extern bool redraw;
extern bool doexit;

extern short boltFrame;
extern int shipFrame;
extern int shipFramesetSwap;
extern ALLEGRO_BITMAP *boltFrames[12];
extern ALLEGRO_BITMAP *asteroidFrames[60];
extern ALLEGRO_BITMAP *blastFrames[36];
extern ALLEGRO_BITMAP *backdrop;
extern ALLEGRO_BITMAP *shipFrames[120];

extern PROJP ship;
extern int ship_spread_index;
extern int ship_cooldown;
extern int ast_cooldown;

extern SPP sl_pool;
extern SPP ast_pool;
extern SPP blast_pool;
extern SPP node_pool;

extern enum {KEY_UP, KEY_DOWN, KEY_LEFT, KEY_RIGHT, KEY_SPACE};
extern bool key[5];

extern COLLBOX collision_array[SCREEN_W / 100][SCREEN_H / 100];

#endif