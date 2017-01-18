#pragma once

#include "EntityMoving.h"

class Projectile :public EntityMoving {

protected:

	//The velocity of the projectile
	int velX, velY;

public:

	Projectile(std::string texturePath, SDL_Renderer* renderer, Settings* settings, int localX = DEFAULT_POS, int localY = DEFAULT_POS,
		int width = DEFAULT_SIZE, int height = DEFAULT_SIZE, int localVelX = 0, int localVelY = 0) :
		EntityMoving(texturePath, renderer, settings, localX, localY, width, height, localVelX, localVelY) {

		this->velX = localVelX;
		this->velY = localVelY;
	}

	~Projectile() {
	}


};

