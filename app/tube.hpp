#pragma once
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>

class Tube {
	public:
		ALLEGRO_BITMAP *tube_bot;
		ALLEGRO_BITMAP *tube_top;

		Tube(double x, double y, int id);
		bool move(int screenWidth);
		bool checkScore(const int width, float bird_x);
		void resetPosition(int screenWidth);
		float getX();
		float getY();
	private:
		float x;
		float y;
		int id;
		float timer;
};