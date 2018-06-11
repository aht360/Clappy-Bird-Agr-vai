#include "tube.hpp"

const int TUBE_MIN_Y = 4;
const int TUBE_MAX_Y = 2;

Tube::Tube(double x, double y, int id) {
	tube_top = al_load_bitmap("Resources/tube_top.bmp");	
	tube_bot = al_load_bitmap("Resources/tube_bot.bmp");
	
	this->timer = al_current_time();
	this->x = x;
	this->y = y;
	this->id = id;
	this->w = al_get_bitmap_width(tube_bot);
	this->h = al_get_bitmap_height(tube_bot);
}

bool Tube::move(int screenWidth){
	bool restedPosition = false;
	float now = al_current_time();
	this->x -= 200*(now - timer);

	if(x <= -this->w) {
		resetPosition(screenWidth);
		restedPosition = true;
	} 
	timer = now;
	return restedPosition;
}

void Tube::setTimer(float time){
	this->timer = time;
}

void Tube::resetPosition(int screenWidth) {
	int botTubeY = (rand()%((TUBE_MIN_Y - TUBE_MAX_Y) + 1) + TUBE_MAX_Y)*100;

	this->x = screenWidth + 400 + this->w;
	this->y = botTubeY;
}

void Tube::draw(){
	al_draw_bitmap(tube_bot, x, y, 0);
	al_draw_bitmap(tube_top, x, y - 425, 0);
}

bool Tube::checkScore(const int width, float bird_x){
	if(this->x >= bird_x-2.5 && this->x <= bird_x+2.5){
		return true;
	} else {
		return false;
	}
}

float Tube::getX(){
	return this->x;
}

float Tube::getY(){
	return this->y;
}
