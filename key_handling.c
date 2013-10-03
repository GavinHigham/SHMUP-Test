void key_down(ALLEGRO_EVENT ev)
{
	switch(ev.keyboard.keycode) {
		case ALLEGRO_KEY_W:
			key[KEY_UP] = true;
			break;

		case ALLEGRO_KEY_S:
			key[KEY_DOWN] = true;
			break;

		case ALLEGRO_KEY_A: 
			key[KEY_LEFT] = true;
			break;

		case ALLEGRO_KEY_D:
			key[KEY_RIGHT] = true;
			break;

		case ALLEGRO_KEY_SPACE:
			key[KEY_SPACE] = true;
			break;
	}
}

void key_up(ALLEGRO_EVENT ev)
{
	switch(ev.keyboard.keycode) {
				case ALLEGRO_KEY_W:
					key[KEY_UP] = false;
					break;
			 
				case ALLEGRO_KEY_S:
					key[KEY_DOWN] = false;
					break;
			 
				case ALLEGRO_KEY_A: 
					key[KEY_LEFT] = false;
					break;
			 
				case ALLEGRO_KEY_D:
					key[KEY_RIGHT] = false;
					break;

				case ALLEGRO_KEY_SPACE:
					key[KEY_SPACE] = false;
					break;
			 
				case ALLEGRO_KEY_ESCAPE:
					doexit = true;
					break;
	}
}