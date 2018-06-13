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

	}else if(velocity<=18 && velocity >= -18){
		al_draw_bitmap(birdNormal, x, y, 0);
		
	}else{
		al_draw_bitmap(birdUp, x, y, 0);
	}
}

void Bird::accel(bool isClap){
	if(isClap){
		velocity = -365;
	}
	velocity += 25;
	//printf("%f", now-timer);
}

void Bird::update(){
	float now = al_current_time();
	y += velocity*(now-timer);

	if(y < 0)
		y = 0;
	timer = now;
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

 bool Bird::isCollision(Tube tube, const int height){
 	float botTubeY, botTubeX, topTubeY, topTubeX, birdW, birdH;
 	botTubeY = tube.getY();
 	botTubeX = tube.getX();

 	topTubeY = botTubeY - 425;
 	topTubeX = botTubeX;

 	float hitboxX, hitboxY;
 	hitboxX = x + 3;
 	hitboxY = y + 3;

  	if(velocity>1){
  		birdW = al_get_bitmap_width(birdDown) - 3;
  		birdH = al_get_bitmap_height(birdDown) - 3;
  		if(hitboxY+birdH >= height)
  			return true;
  		if((hitboxX < botTubeX + tube.w) && ((hitboxX+birdW) > botTubeX) && (hitboxY <(botTubeY + tube.h)) && ((hitboxY + birdH) > botTubeY))
 			return true;
  		if((hitboxX < topTubeX + tube.w) && ((hitboxX+birdW) > topTubeX) && (hitboxY <(topTubeY + tube.h)) && ((hitboxY + birdH) > topTubeY))
 			return true;
 	}else if(velocity <=18 && velocity >= -18){
  		birdW = al_get_bitmap_width(birdNormal) - 3;
  		birdH = al_get_bitmap_height(birdNormal) - 3;
  		if(hitboxY+birdH >= height)
  			return true;
  		if((hitboxX < botTubeX + tube.w) && ((hitboxX+birdW) > botTubeX) && (hitboxY <(botTubeY + tube.h)) && ((hitboxY + birdH) > botTubeY))
 			return true;
  		if((hitboxX < topTubeX + tube.w) && ((hitboxX+birdW) > topTubeX) && (hitboxY <(topTubeY + tube.h)) && ((hitboxY + birdH) > topTubeY))
 			return true;
 	}else{
  		birdW = al_get_bitmap_width(birdUp) - 3;
  		birdH = al_get_bitmap_height(birdUp) - 3;
  		if(hitboxY+birdH >= height)
  			return true;
  		if((hitboxX < botTubeX + tube.w) && ((hitboxX+birdW) > botTubeX) && (hitboxY <(botTubeY + tube.h)) && ((hitboxY + birdH) > botTubeY))
 			return true;
  		if((hitboxX < topTubeX + tube.w) && ((hitboxX+birdW) > topTubeX) && (hitboxY <(topTubeY + tube.h)) && ((hitboxY + birdH) > topTubeY))
 			return true;
 	}
 	return false;
 }

void Bird::reset(const int width, const int height){
	x = width/4 - 40;
	y = height/2;

	velocity = 0;
}
