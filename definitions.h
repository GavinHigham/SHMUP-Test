#ifndef DEFINITIONS_H
#define DEFINITIONS_H
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>

//#define ROOT
#define SCREEN_W 800
#define SCREEN_H 600
#define BACKDROP_H 1200
#define BACKDROP_W 1920
#define AST_POOL_SIZE 2000
#define PROJ_POOL_SIZE 1000
#define ENEMY_POOL_SIZE 200
#define ENEMY_BOLT_POOL_SIZE 200
#define SHOT_COOLDOWN_MAX 4
#define AST_COOLDOWN_MAX 3
#define REGEN_COOLDOWN_MAX 20
#define ENEMY_COOLDOWN_MAX 45
#define ENEMY_BOLT_COOLDOWN_MAX 35
extern int MARGIN;
extern int FPS;
extern int SHOT_SPREAD;
extern int SHOT_OFFSET_X;
extern int SHOT_OFFSET_Y;
extern float planet_sm_theta;
extern float viewing_angle;
extern float orbit_r;
extern float cameraX;
extern float cameraY;
extern int attention;
extern int meditation;
extern float regen;
extern float timescale;

typedef long long unsigned int llui;

// If the project compiles and runs, these can be deleted.
// //A 2D floating-point vector.
// typedef struct vector {
// 	float x;
// 	float y;
// } VECTOR, *VP;
//
// //A 2D integer vector.
// typedef struct ivector {
// 	int x;
// 	int y;
// } IVECT, *IVP;

//"Kind" will be an integer, but I enumerate its possible values here.
enum {SHIP, BOLT, ASTEROID, ENEMY, BLAST, ENEMYBOLT};
enum {KEY_UP, KEY_DOWN, KEY_LEFT, KEY_RIGHT, KEY_SPACE};

// If the project compiles and runs, these can be deleted.
// VECTOR struct_zero_vector = {0, 0};
// VP zero_vec = &struct_zero_vector;
extern int numcolgroups;

//Standard velocity.
extern float stdv;
//Value to scale x and y vel by if both keys are pressed.
extern float diagscale;
extern float backdropx;
extern float backdropy;
extern float backAx;

ALLEGRO_DISPLAY *display;
ALLEGRO_EVENT_QUEUE *event_queue;
ALLEGRO_TIMER *timer;

extern bool redraw;
extern bool doexit;

extern short boltFrame;
extern float shipFrame;
extern int shipFramesetSwap;
extern ALLEGRO_BITMAP *boltFrames[12];
extern ALLEGRO_BITMAP *asteroidFrames[60];
extern ALLEGRO_BITMAP *blastFrames[36];
extern ALLEGRO_BITMAP *shipFrames[120];
extern ALLEGRO_BITMAP *backdrop;
extern ALLEGRO_BITMAP *bg_starsA;
extern ALLEGRO_BITMAP *bg_starsB;
extern ALLEGRO_BITMAP *planet_lg;
extern ALLEGRO_BITMAP *planet_sm;
extern ALLEGRO_BITMAP *health_tray;
extern ALLEGRO_BITMAP *health_bar;
extern ALLEGRO_BITMAP *badguy;
extern ALLEGRO_BITMAP *enemy_bolt_sprite;
extern ALLEGRO_BITMAP *loss;
extern ALLEGRO_BITMAP *asteroid;

extern int ship_spread_index;
extern float ship_cooldown;
extern float ast_cooldown;
extern float enemy_cooldown;
extern float enemy_bolt_cooldown;
extern float explosion_countdown;
extern bool lost;
extern bool key[5];

#endif