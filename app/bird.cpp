#include "bird.hpp"

Bird::Bird(std::string color, const int width, const int height){
	//load and save images
	std::string bNormal = "Resources/"+color+"/bird_normal.bmp";
	std::string bDown = "Resources/"+color+"/bird_down.bmp";
	std::string bUp = "Resources/"+color+"/bird_up.bmp";

	birdNormal = al_load_bitmap(bNormal.c_str());
	birdDown = al_load_bitmap(bDown.c_str());
	birdUp = al_load_bitmap(bUp.c_str());

	x = width/4 - 40;
	y = height/2;

	velocity = 0;
	timer = al_current_time();
}

Bird::Bird(){
	timer = al_current_time();
}

void Bird::draw(){
	if(velocity>1){
		al_draw_bitmap(birdDown, x, y, 0);

	}else if(velocity<=10 && velocity >= -10){
		al_draw_bitmap(birdNormal, x, y, 0);
		
	}else{
		al_draw_bitmap(birdUp, x, y, 0);
	}
}

void Bird::accel(bool isClap){
	float now = al_current_time();
	if(isClap){
		velocity = -275;
	}
	velocity += 18;
	if(velocity > 350)
		velocity = 350;
	y += velocity*(now-timer);
	//printf("%f", now-timer);
	timer = now;
	if(y <= 0)
		y = 0;
}

void Bird::setTimer(float time){
	timer = time;
}

void Bird::close(){
	al_destroy_bitmap(birdNormal);
	birdNormal = NULL;

	al_destroy_bitmap(birdUp);
	birdUp = NULL;

	al_destroy_bitmap(birdDown);
	birdDown = NULL;
}

// bool Bird::isCollision(Tube tube, const int height){
// 	SDL_Rect bottom_tube, top_tube, bird, aux;
// 	bottom_tube.y = tube.getY();
// 	bottom_tube.x = tube.getX();
// 	bottom_tube.w = tube.tube_bot->w;
// 	bottom_tube.h = tube.tube_bot->h;

// 	top_tube.y = tube.getY() - 425;
// 	top_tube.x = tube.getX();
// 	top_tube.w = tube.tube_top->w;
// 	top_tube.h = tube.tube_top->h;

// 	bird.y = y;
// 	bird.x = x;

//  	if(velocity>1){
//  		bird.w = birdDown->w;
//  		bird.h = birdDown->h;
//  		if(bird.y+bird.h >= height)
//  			return true;
// 		if(SDL_IntersectRect(&bottom_tube, &bird, &aux) == SDL_TRUE || SDL_IntersectRect(&top_tube, &bird, &aux) == SDL_TRUE)
// 			return true;
// 	}else if(velocity <=1 && velocity >= -1){
//  		bird.w = birdNormal->w;
//  		bird.h = birdNormal->h;
//  		if(bird.y+bird.h >= height)
//  			return true;
// 		if(SDL_IntersectRect(&bottom_tube, &bird, &aux) == SDL_TRUE || SDL_IntersectRect(&top_tube, &bird, &aux) == SDL_TRUE)
// 			return true;
// 	}else{
//  		bird.w = birdUp->w;
//  		bird.h = birdUp->h;
//  		if(bird.y+bird.h >= height)
//  			return true;
// 		if(SDL_IntersectRect(&bottom_tube, &bird, &aux) == SDL_TRUE || SDL_IntersectRect(&top_tube, &bird, &aux) == SDL_TRUE)
// 			return true;
// 	}
// 	return false;
// }

void Bird::reset(const int width, const int height){
	x = width/4 - 40;
	y = height/2;

	velocity = 0;
}
