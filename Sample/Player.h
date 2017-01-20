#pragma once

#include "EntityLiving.h"

class Player : public EntityLiving{

public:

	Player() : EntityLiving() {}

	Player(std::string texturePath, SDL_Renderer* renderer, Settings* settings, int localX = DEFAULT_POS, int localY = DEFAULT_POS, 
		int width = DEFAULT_SIZE, int height = DEFAULT_SIZE, int localVelX = 0, int localVelY = 0, int health = DEFAULT_HEALTH) :

		EntityLiving(texturePath, renderer, settings, localX, localY, width, height, localVelX, localVelY, health)

	{}

	~Player() {
		Entity::free();
	}

	//Takes key presses and adjusts the dot's velocity
	void handleEvent(SDL_Event& e) {

		

		if (e.type == SDL_MOUSEBUTTONDOWN) {
			int x, y;
			SDL_GetMouseState(&x, &y);
			std::cout << "clicked x:" << x;
			std::cout << "clicked y:" << y;
			shootBomb(x, y);
		}

		//If a key was pressed
		if (e.type == SDL_KEYDOWN && e.key.repeat == 0) {
			//Adjust the velocity
			switch (e.key.keysym.sym) {
				case SDLK_w: velY -= DEFAULT_VELOCITY; break;
				case SDLK_s: velY += DEFAULT_VELOCITY; break;
				case SDLK_a: velX -= DEFAULT_VELOCITY; break;
				case SDLK_d: velX += DEFAULT_VELOCITY; break;
			}
		}
		//If a key was released
		else if (e.type == SDL_KEYUP && e.key.repeat == 0) {
			//Adjust the velocity
			switch (e.key.keysym.sym) {
				case SDLK_w: velY += DEFAULT_VELOCITY; break;
				case SDLK_s: velY -= DEFAULT_VELOCITY; break;
				case SDLK_a: velX += DEFAULT_VELOCITY; break;
				case SDLK_d: velX -= DEFAULT_VELOCITY; break;
			}
		}
	}
};
