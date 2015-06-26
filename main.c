//C stuff.
#include <stdio.h>
#include <stdlib.h>
#ifdef _WIN32
	#include <time.h>
#else
	#include <sys/time.h>
#endif
//Allegro stuff.
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
//My stuff.
#include "definitions.h"
#include "collision.h"
#include "proj.h"
#include "struct_pool.h"
#include "init.c"
#include "tex_load.c"
#include "logic_tick.h"
#include "key_handling.c"
#include "trig.h"
#include "game_draw.h"
//#include <unistd.h>
//#include <string.h>
//#include <sys/types.h>
//#include <sys/socket.h>
//#include <netinet/in.h>
//#include <netdb.h> 
//#include <jansson.h>
//#include "parson/parson.c"

/*
void error(const char *msg)
{
    perror(msg);
    //exit(0);
}

void * parse_the_junk(ALLEGRO_THREAD *le_thread, void *data)
{
    //Setup json objects
    json_error_t *errors = NULL;
    json_t *auth      = json_object();
    json_t *cfg       = json_object();
    json_t *braindata = json_object();
    json_object_set(auth, "appName", json_string("TestFour"));
    json_object_set(auth, "appKey", json_string("ffdab17b99842cd1ed538b2c08472e2b72a9d5c8"));
    json_object_set(cfg, "enableRawOutput", json_false());
    json_object_set(cfg, "format", json_string("Json"));

    char buffer[256];
    int sockfd, portno, n, socket_size;
    unsigned int m = sizeof(socket_size);
    struct sockaddr_in serv_addr;
    struct hostent *server;
    portno = 13854;

    //Network stuff I don't understand. I only accept that it works. For now.
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) 
        error("ERROR opening socket");
    server = gethostbyname("localhost");
    if (server == NULL) {
        fprintf(stderr,"ERROR, no such host\n");
        exit(0);
    }
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr, 
         (char *)&serv_addr.sin_addr.s_addr,
         server->h_length);
    serv_addr.sin_port = htons(portno);
    if (connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0) 
        error("ERROR connecting");
    //Get the socket size.
    //getsockopt(fdsocket,SOL_SOCKET,SO_RCVBUF,(void *)&socket_size, &m);

    char  *cfg_string = json_dumps(cfg, 0);
    char *auth_string = json_dumps(auth, 0);
    //Authenticate!
    n = write(sockfd, auth_string, strlen(auth_string));
    if (n < 0)
         error("ERROR writing to socket");
    sleep(2);
    //Configure!
    n = write(sockfd, cfg_string, strlen(cfg_string));
    if (n < 0) 
         error("ERROR writing to socket");

    printf("Advancing to first \\r.\n");
    bzero(buffer, 256);
    do {
        read(sockfd,buffer,1);
        printf("%c", buffer[0]);
    } while (buffer[0] != '\r');
    printf("Beginning to parse complete packets.\n");
    int i, k = 0;
    while(!doexit)
    {
        bzero(buffer, 256);
        while(read(sockfd,&buffer[k],1) && buffer[k] != '\r' && k < 256) {
            k++;
            //printf("%c", buffer[k]);
        }
        braindata = json_loads(buffer, k, errors);
        json_t *eSense = json_object_get(braindata, "eSense");
        if (eSense != NULL) {
            int attention_tmp = (int)json_integer_value(json_object_get(eSense, "attention"));
            if (attention_tmp != 0) attention = attention_tmp;
            int meditation_tmp = (int)json_integer_value(json_object_get(eSense, "meditation"));
            if (meditation_tmp != 0) meditation = meditation_tmp; 
            printf("a: %i, m: %i\n", attention, meditation);
        }
    }
    close(sockfd);
    free(cfg_string);
    free(auth_string);
    return NULL;
}
*/

int main()
{
    int i;
    /*
	ALLEGRO_THREAD *other_thread = NULL;
	other_thread = al_create_thread(parse_the_junk, &c);
	al_start_thread(other_thread);
    */

	//Initializing a bunch of modules.
	if (init_stuff()) return -1;

	//Loading in the textures.
	if (load_textures()) return -1;

	//Setup the ship projectile.
	ship->posX = SCREEN_W / 4;
	ship->posY = SCREEN_H / 2;

	event_queue = al_create_event_queue();
	if(!event_queue) {
		fprintf(stderr, "failed to create event_queue!\n");
		al_destroy_display(display);
		al_destroy_timer(timer);
		return -1;
	}
 
	al_register_event_source(event_queue, al_get_display_event_source(display));
	al_register_event_source(event_queue, al_get_timer_event_source(timer));
	al_register_event_source(event_queue, al_get_keyboard_event_source());
	al_start_timer(timer);
 
	while(!doexit) {
		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);
		
		if (ev.type == ALLEGRO_EVENT_TIMER) {
			logic_tick();
			redraw = true;
		}
		else if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) break;
		else if(ev.type == ALLEGRO_EVENT_KEY_DOWN) key_down(ev);
		else if(ev.type == ALLEGRO_EVENT_KEY_UP) key_up(ev);
		if(redraw && al_is_event_queue_empty(event_queue))
			game_draw();
	}

	//Destroy the other thread!
	//al_destroy_thread(other_thread);
	//Free all the things!
	for (i = 0; i < 60; i++) al_destroy_bitmap(asteroidFrames[i]);
	for (i = 0; i < 12; i++) al_destroy_bitmap(boltFrames[i]);
	for (i = 0; i < 120; i++) al_destroy_bitmap(shipFrames[i]);
	for (i = 0; i < 35; i++) al_destroy_bitmap(blastFrames[i]);
	al_destroy_bitmap(backdrop);
	al_destroy_bitmap(bg_starsA);
	al_destroy_bitmap(bg_starsB);
	al_destroy_bitmap(planet_lg);
	al_destroy_bitmap(planet_sm);
	al_destroy_bitmap(health_tray);
	al_destroy_bitmap(health_bar);
	al_destroy_bitmap(badguy);
    al_destroy_bitmap(loss);
	al_destroy_timer(timer);
	al_destroy_display(display);
	al_destroy_event_queue(event_queue);
	//free_projectile(ship);
	free_smartItemPool(sl_pool);
	free_smartItemPool(ast_pool);
	free_smartItemPool(blast_pool);
	free_smartItemPool(node_pool);
	free_smartItemPool(enemy_pool);
	free_smartItemPool(enemy_bolt_pool);

	return 0;
}
