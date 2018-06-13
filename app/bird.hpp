#pragma once
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <stdio.h>
#include <string>
#include "tube.hpp"

class Bird{
	public:
		Bird();
		Bird(std::string color, const int width, const int height);
		void draw();
		void accel(bool isClap);
		void update();
		void close();
		void setTimer(float time);
		void reset(const int width, const int height);
		float x;
		float y;
		bool isCollision(Tube tube, const int height);
		void changeColor(std::string color);
	private:
		ALLEGRO_BITMAP *birdNormal;
		ALLEGRO_BITMAP *birdDown;
		ALLEGRO_BITMAP *birdUp;
		float velocity;
		float timer;
};