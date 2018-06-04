#pragma once
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <string>

class Bird{
	public:
		Bird(std::string color, const int width, const int height);
		void draw();
		void accel(bool isClap);
		void close();
		void reset(const int width, const int height);
		float x;
		float y;
		//bool isCollision(Tube tube, const int height);
	private:
		ALLEGRO_BITMAP *birdNormal;
		ALLEGRO_BITMAP *birdDown;
		ALLEGRO_BITMAP *birdUp;
		float velocity;
		float timer;
};