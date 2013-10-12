#ifndef H_DEFINITIONS
#define H_DEFINITIONS

#include <allegro5/allegro.h>

//#define ROOT
extern const int SCREEN_W;
extern const int SCREEN_H;
extern const int MARGIN;
extern const int FPS;
extern const int PROJ_POOL_SIZE;
extern const int AST_POOL_SIZE;
extern const int ENEMY_POOL_SIZE;
extern const int ENEMY_BOLT_POOL_SIZE;
extern const int BACKDROP_H;
extern const int BACKDROP_W;
extern const int SHOT_COOLDOWN_MAX;
extern const int AST_COOLDOWN_MAX;
extern int SHOT_SPREAD;
extern int SHOT_OFFSET_X;
extern int SHOT_OFFSET_Y;
extern float planet_sm_theta;
extern float viewing_angle;
extern float orbit_r;
extern float cameraX;
extern float cameraY;

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
extern enum {SHIP, BOLT, ASTEROID, ENEMY, BLAST, ENEMYBOLT};

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

extern VECTOR struct_zero_vector;
extern VP zero_vec;
extern int numcolgroups;

extern int i;
//Standard velocity.
extern float stdv;
//Value to scale x and y vel by if both keys are pressed.
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
extern ALLEGRO_BITMAP *shipFrames[120];
extern ALLEGRO_BITMAP *backdrop;
extern ALLEGRO_BITMAP *bg_stars;
extern ALLEGRO_BITMAP *planet_lg;
extern ALLEGRO_BITMAP *planet_sm;

extern PROJP ship;
extern int ship_spread_index;
extern int ship_cooldown;
extern int ast_cooldown;

extern SPP sl_pool;
extern SPP ast_pool;
extern SPP blast_pool;
extern SPP enemy_pool;
extern SPP enemy_bolt_pool;
extern SPP node_pool;

extern enum {KEY_UP, KEY_DOWN, KEY_LEFT, KEY_RIGHT, KEY_SPACE};
extern bool key[5];

extern COLLBOX **collision_array;

#endif