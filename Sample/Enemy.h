#pragma once

#include "EntityLiving.h"

class Enemy : public EntityLiving {



public:

	Enemy() : EntityLiving() {}

	Enemy(std::string texturePath, SDL_Renderer* renderer, Settings* settings, int localX = DEFAULT_POS, int localY = DEFAULT_POS, 
		int width = DEFAULT_SIZE, int height = DEFAULT_SIZE, int localVelX = 0, int localVelY = 0, int health = DEFAULT_HEALTH) :

		EntityLiving(texturePath, renderer, settings, localX, localY, width, height, localVelX, localVelY, health)

	{}

	~Enemy() {

	}
};

