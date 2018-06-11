#pragma once
#include <allegro5/allegro.h>
#include <omp.h>
#include <SerialStream.h>
#include <SerialPort.h>
#include <allegro5/allegro_image.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <unistd.h>
#include <cstdlib>
#include <fcntl.h>
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

unsigned char hexdigit[] = {0x3F, 0x06, 0x5B, 0x4F,
                            0x66, 0x6D, 0x7D, 0x07, 
                            0x7F, 0x6F, 0x77, 0x7C,
                            0x39, 0x5E, 0x79, 0x71};
                            
ALLEGRO_DISPLAY *window = NULL;
ALLEGRO_BITMAP *backgroundScreen = NULL;
ALLEGRO_BITMAP *loseScreen = NULL;

ALLEGRO_EVENT_QUEUE *event_queue = NULL;
ALLEGRO_TIMER* timer = NULL;

Bird bird = Bird("yellow", SCREEN_WIDTH, SCREEN_HEIGHT);

list <Tube> tubes;

LibSerial::SerialStream my_serial;

bool init();
bool loadMedia_tubes();
void close();
void writeLed(int count, int dev);
void derrota(int dev);
void writeScore(int score, int dev);