#pragma once
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <list>
#include <iterator>
#include "tube.hpp"
#include "bird.hpp"

using namespace std;

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int TUBE_MIN_Y = 4;
const int TUBE_MAX_Y = 2;
const int FPS = 60;

ALLEGRO_DISPLAY *window = NULL;
ALLEGRO_BITMAP *backgroundScreen = NULL;
ALLEGRO_BITMAP *loseScreen = NULL;

ALLEGRO_EVENT_QUEUE *event_queue = NULL;
ALLEGRO_TIMER* timer = NULL;

Bird bird = Bird("yellow", SCREEN_WIDTH, SCREEN_HEIGHT);

list <Tube> tubes;

bool init();
bool loadMedia_tubes();
void close();