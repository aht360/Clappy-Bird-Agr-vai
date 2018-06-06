#include "app.hpp"


int main () {

	LibSerial::SerialStream my_serial;
	srand(time(NULL));
	int n = 0;
	int i;

	bool redraw = true;
	float gameTime = 0.0;
	int frames = 0;
	int gameFPS = 0;
	int score = 0;


	my_serial.Open("/dev/ttyUSB0");
	while(!my_serial.good()){
		printf("Serial Port closed");
	}

	my_serial.SetBaudRate(LibSerial::SerialStreamBuf::BAUD_9600);

	my_serial.SetCharSize(LibSerial::SerialStreamBuf::CHAR_SIZE_8);

	my_serial.SetFlowControl(LibSerial::SerialStreamBuf::FLOW_CONTROL_NONE);

	my_serial.SetParity(LibSerial::SerialStreamBuf::PARITY_NONE);

	if(!init()){
		printf("Failed to initialize!\n");
		return -1;
	}

	if(!loadMedia_tubes()){
		printf("Failed to load tube!\n");
		return -1;
	}
	bird = Bird("yellow", SCREEN_WIDTH, SCREEN_HEIGHT);
	bool quit = false;
	bool paused = true;
	bool buttonPress = false;
	bird.draw();
	al_flip_display();
	al_rest(5);
	al_start_timer(timer);
	char num ='1';
	

				while (!quit) {
					ALLEGRO_EVENT ev;
					al_wait_for_event(event_queue, &ev);
					cout << num;
					if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
						quit = true;
					} else if (ev.type == ALLEGRO_EVENT_KEY_DOWN) {
						if (paused == true) {
							if(ev.keyboard.keycode == ALLEGRO_KEY_UP) {
								paused = false;
								bird.setTimer(al_current_time());
								for (list <Tube>::iterator it = tubes.begin(); it != tubes.end(); it++) {
									(*it).setTimer(al_current_time());
								}
								bird.accel(true);
							}
						} else {
							if(ev.keyboard.keycode == ALLEGRO_KEY_UP && buttonPress == false) {
								bird.accel(true);
								buttonPress = true;
							}
						}
					} else if (ev.type == ALLEGRO_EVENT_KEY_UP) {
						if(ev.keyboard.keycode == ALLEGRO_KEY_UP && buttonPress == true) {
							buttonPress = false;
						}
					}
					else if (ev.type == ALLEGRO_EVENT_TIMER && al_event_queue_is_empty(event_queue) && !paused) {
						redraw = true;
						//update fps
						frames++;
						if (al_current_time() - gameTime >= 1) {
							gameTime = al_current_time();
							gameFPS = frames;
							frames = 0;
						}
						//update objects
						bool resetedPosition = false;
						for (list <Tube>::iterator it = tubes.begin(); it != tubes.end(); it++) {
							if((*it).move(SCREEN_WIDTH)){
								resetedPosition = true;
							}
							if((*it).checkScore(SCREEN_WIDTH, bird.x)){
								score += 1;
								printf("Score: %d\n", score);
							}
							
						}
						if(resetedPosition) {
							tubes.splice(tubes.end(), tubes, tubes.begin());
						}

						bird.accel(false);

						if(0){
							paused = true;
							al_draw_bitmap(loseScreen, 0, 0, 0);
							al_flip_display();
							score = 0;
							al_rest(1);
							bird.reset(SCREEN_WIDTH, SCREEN_HEIGHT);
							loadMedia_tubes();
							al_draw_bitmap(backgroundScreen, 0, 0, 0);
						}

						bird.draw();
					}

					if (redraw && al_is_event_queue_empty(event_queue)) {
						al_clear_to_color(al_map_rgb(0, 0, 0));
						al_draw_bitmap(backgroundScreen, 0, 0, 0);
						for (list <Tube>::iterator it = tubes.begin(); it != tubes.end(); it++) {
							(*it).draw();
						}
						bird.draw();
						al_flip_display();
					}

				}
			}
		
	}
	return 0;
}

bool init() {
	bool success = true;

    if (!al_init()) {
       	printf("Falha ao inicializar a Allegro.\n");
        success = false;
    }
 
    if (!al_init_image_addon()) {
        printf("Falha ao inicializar add-on allegro_image.\n");
        success = false;
    }

    if (!al_install_keyboard()) {
        printf("Falha ao inicializar o teclado.\n");
        return false;
    }
 
    window = al_create_display(SCREEN_WIDTH, SCREEN_HEIGHT); //creates window
    al_clear_to_color(al_map_rgb(255, 255, 255)); //sets window color

    if(window == NULL) {
    	printf("Window could not be created!\n");
		success = false;
    }

    event_queue = al_create_event_queue();
    if (!event_queue) {
        printf("Falha ao criar fila de eventos.\n");
        al_destroy_display(window);
        return false;
    }

    backgroundScreen = al_load_bitmap("Resources/background.bmp");

    if(backgroundScreen == NULL) {
    	printf("Background could not be created!\n");
		success = false;
    }

    loseScreen = al_load_bitmap("Resources/lose.bmp");

    if(loseScreen == NULL) {
    	printf("Lose screen could not be created!\n");
		success = false;
    }

    timer = al_create_timer(1.0 / FPS);

 	al_draw_bitmap(backgroundScreen, 0, 0, 0);
    al_flip_display();

    al_register_event_source(event_queue, al_get_keyboard_event_source());
    al_register_event_source(event_queue, al_get_display_event_source(window));
    al_register_event_source(event_queue, al_get_timer_event_source(timer));
 
    return success;
}

bool loadMedia_tubes(){
	bool success = true;

	tubes.clear();

	for(int i = 0; i < 3 && success == true; i++) {
		int botTubeY = (rand()%((TUBE_MIN_Y - TUBE_MAX_Y) + 1) + TUBE_MAX_Y)*100;
		
		tubes.push_back(Tube(SCREEN_WIDTH + 100 + 400*i, botTubeY, i));

		if(tubes.back().tube_bot == NULL || tubes.back().tube_top == NULL){
			printf( "Unable to load image tube.bmp!\n");
			success = false;
		}
	}

	return success;
}

void close() { 
	for (list <Tube>::iterator it = tubes.begin(); it != tubes.end(); it++) {
		al_destroy_bitmap((*it).tube_bot);
		al_destroy_bitmap((*it).tube_top);
		(*it).tube_bot = NULL;
		(*it).tube_top = NULL;
	}

	al_destroy_bitmap(backgroundScreen);
	backgroundScreen = NULL;

	al_destroy_bitmap(loseScreen);
	loseScreen = NULL;

    al_destroy_display(window);
    window = NULL;
}

