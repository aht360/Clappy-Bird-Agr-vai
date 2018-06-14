#include "app.hpp"

#define PAUSAR 8
#define VERDE 4
#define ROSA 2
#define AMARELO 1

int main () {

	LibSerial::SerialStream my_serial;
	srand(time(NULL));
	int n = 0;

    int dev = open("/dev/de2i150_altera", O_RDWR);
    
	bool redraw = true;
	float gameTime = 0.0;
	int frames = 0;
	int gameFPS = 0;
	bool quit = false;
	char num ='1';
	bool pointSound = false;
	bool loseSound = false;

	#pragma omp parallel num_threads(3)
	{
		#pragma omp sections
		{
			#pragma omp section
			{
				my_serial.Open("/dev/ttyUSB0");
				while(!my_serial.good()){
					printf("Serial Port closed");
				}

				my_serial.SetBaudRate(LibSerial::SerialStreamBuf::BAUD_9600);

				my_serial.SetCharSize(LibSerial::SerialStreamBuf::CHAR_SIZE_8);

				my_serial.SetFlowControl(LibSerial::SerialStreamBuf::FLOW_CONTROL_NONE);

				my_serial.SetParity(LibSerial::SerialStreamBuf::PARITY_NONE);

				al_rest(3);

				while(!quit){
					my_serial >> num;
					#pragma omp critical (input)
					{
					num = '0';
					}
				}
			}
			#pragma omp section
			{
				while(!quit){
					if(pointSound == true){
							bzzr(300);
							usleep(10000);
							bzzr(200);
						pointSound = false;
					}
					if(loseSound == true){
						bzzr(1342717728);
						usleep(10000);	
						bzzr(1342717728);
						loseSound = false;
					}
				}
			}

			#pragma omp section
			{

				if(!init()){
					printf("Failed to initialize!\n");
				}

				if(!loadMedia_tubes(true)){
					printf("Failed to load tube!\n");
				}

				int bt;
				int sw;
				bird = Bird("yellow", SCREEN_WIDTH, SCREEN_HEIGHT);
				char back = 'd';
				bool paused = true;
				bool buttonPress = false;
				bool addScore = true;
				bool mute = false;
				bool invencible = false;
				bool pedro = false;

				bird.draw();
				al_flip_display();
				al_start_timer(timer);
				int life = 5;
				int score = 0;
				int highScore = 0;
				int activeColor = AMARELO;
				writeLed(life, dev);
				writeScore(score, dev, 0);
				writeScore(highScore, dev, 3);
				
				while (!quit) {
					ALLEGRO_EVENT ev;
					al_wait_for_event(event_queue, &ev);
					bt = readButton(dev);

					if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
						quit = true;
					} else if (ev.type == ALLEGRO_EVENT_TIMER && al_event_queue_is_empty(event_queue) && !paused) {
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

						}

						if(tubes.front().checkScore(SCREEN_WIDTH, bird.x) && addScore){
							score += 1;
							writeScore(score, dev, 0);
							if(mute == false) {
								pointSound = true;	
							}
							addScore = false;
						}

						if(resetedPosition) {
							addScore = true;
							tubes.splice(tubes.end(), tubes, tubes.begin());
						}

						bird.accel(false);
						bird.update();
						if(bird.isCollision(tubes.front(), SCREEN_HEIGHT) && invencible == false){
							life --;
							writeLed(life, dev);
							paused = true;
							al_clear_to_color(al_map_rgb(0, 0, 0));
							al_draw_bitmap(backgroundScreen, 0, 0, 0);
							for (list <Tube>::iterator it = tubes.begin(); it != tubes.end(); it++) {
								(*it).draw();
							}
							bird.draw();
							if(life == 0){
								al_draw_bitmap(loseScreen, 0, 0, 0);
								if(score > highScore) {
									highScore = score;
									writeScore(highScore, dev, 3);
								}
								score = 0;
								writeScore(score, dev, 0);
							}
							al_flip_display();
							if(mute == false)
								loseSound = true;
							derrota(dev);
							#pragma omp critical (input)
							{
								num = '1';
							}
							bird.reset(SCREEN_WIDTH, SCREEN_HEIGHT);
							loadMedia_tubes(!pedro);
							al_draw_bitmap(backgroundScreen, 0, 0, 0);
						}

					}
					if (num == '0') {
						if (paused == true) {
							paused = false;
							addScore = true;
							if(life == 0){
								life = 5;
								score = 0;
								writeScore(score, dev, 0);
								writeLed(life, dev);
							}
							bird.setTimer(al_current_time());
							for (list <Tube>::iterator it = tubes.begin(); it != tubes.end(); it++) {
								(*it).setTimer(al_current_time());
							}
							bird.accel(true);
						} else {
							bird.accel(true);
						}
						#pragma omp critical (input)
						{
							num = '1';
						}
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
					if(bt == 0){
						buttonPress = false;
					}
					if(buttonPress == false && bt != 0){
						buttonPress = true;
						if(bt == PAUSAR){
							if(paused){
								paused = false;

								bird.setTimer(al_current_time());
								for (list <Tube>::iterator it = tubes.begin(); it != tubes.end(); it++) {
									(*it).setTimer(al_current_time());
								}
							}
							else{
								paused = true;
							}
						}
						else if(bt == AMARELO){
							bird.changeColor("yellow");
							activeColor = AMARELO;
						}else if(bt == ROSA){
							bird.changeColor("pink");
							activeColor = ROSA;
						}else if(bt == VERDE){
							bird.changeColor("green");
							activeColor = VERDE;
						}
					}
					
					sw = readSwitch(dev);
					if((sw & (1 << 1)) && back == 'd' && pedro == false){
    					backgroundScreen = al_load_bitmap("Resources/background_night.bmp");
    					back = 'n';
					} else if(!(sw & (1 << 1)) && back == 'n' && pedro == false){
    					backgroundScreen = al_load_bitmap("Resources/background.bmp");
    					back = 'd';
					} else if((sw & 1) && mute == false){
    					mute = true;
					} else if(!(sw & 1) && mute == true){
    					mute = false;
					}else if((sw & (1 << 2)) && invencible == false){
						invencible = true;
					}else if(!(sw & (1 << 2)) && invencible == true){
						invencible = false;
					}else if((sw & (1 << 11)) && (sw & (1 << 13)) && (sw & (1 << 15)) && pedro == false){
						bird.changeColor("pedro");
						pedro = true;
						for (list <Tube>::iterator it = tubes.begin(); it != tubes.end(); it++) {
							(*it).setTimer(al_current_time());
							(*it).changeTube(true);
						}
						backgroundScreen = al_load_bitmap("Resources/background_rio.bmp");
					}else if((!(sw & (1 << 11)) || !(sw & (1 << 13)) || !(sw & (1 << 15))) && pedro == true){
						if(activeColor == AMARELO)
							bird.changeColor("yellow");
						if(activeColor == ROSA)
							bird.changeColor("pink");
						if(activeColor == VERDE)
							bird.changeColor("green");
						pedro = false;
						for (list <Tube>::iterator it = tubes.begin(); it != tubes.end(); it++) {
							(*it).setTimer(al_current_time());
							(*it).changeTube(false);
						}
						if(back == 'd')
							backgroundScreen = al_load_bitmap("Resources/background.bmp");
						else
    						backgroundScreen = al_load_bitmap("Resources/background_night.bmp");

					}
				}
				close();
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

    timer = al_create_timer(1.0 / 60);

 	al_draw_bitmap(backgroundScreen, 0, 0, 0);
    al_flip_display();

    al_register_event_source(event_queue, al_get_keyboard_event_source());
    al_register_event_source(event_queue, al_get_display_event_source(window));
    al_register_event_source(event_queue, al_get_timer_event_source(timer));
 
    return success;
}

bool loadMedia_tubes(bool change){
	bool success = true;

	tubes.clear();

	for(int i = 0; i < 3 && success == true; i++) {
		int botTubeY = (rand()%((TUBE_MIN_Y - TUBE_MAX_Y) + 1) + TUBE_MAX_Y)*100;
		
		tubes.push_back(Tube(SCREEN_WIDTH + 100 + 400*i, botTubeY, i));

		if(tubes.back().tube_bot == NULL || tubes.back().tube_top == NULL){
			printf( "Unable to load image tube.bmp!\n");
			success = false;
		}
		tubes.back().changeTube(!change);
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

void writeLed(int count, int dev){
	int print;
	if(count == 5){
		print = 31;
	}else if(count == 4){
		print = 15;
	}else if(count == 3){
		print = 7;
	}else if(count == 2){
		print = 3;
	}else if(count == 1){
		print = 1;
	}else{
		print = 0;
	}
	write(dev, &print, 1);
}

void derrota(int dev){
	long int k;

	for(int i =0; i < 30; ++i){
	    k = rand()%2000000000;
	    write(dev, &k, 2);
	    usleep(50000);
	}
	k = 0;
	write(dev, &k, 2);
	write(dev, &k, 2);
}

void writeScore(int score, int dev, int hexport){
	int k = 0;
	char str[4];
	sprintf(str, "%04d", score);
	int count = 0;
	for(int i = 3; i>=0; --i){
		k = k | (hexdigit[str[i]-'0'] << (8*count));
		count++;
	}
	k = ~k;

	write(dev, &k, hexport);
	write(dev, &k, hexport);
}

int readButton(int dev){
	int j;
	read(dev, &j, 0);
	j = ~j;
	j = j & 0XF;
	return j;
}

int readSwitch(int dev){
	int sw;
	read(dev, &sw, 1);
	sw &= 0x3FFFF;
	return sw;
}