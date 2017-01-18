#pragma once

#include "Entity.h"

class EntityMoving : public Entity{

protected:

	int velX, velY;

public:

	EntityMoving() {

	}

	EntityMoving(std::string texturePath, SDL_Renderer* renderer, Settings* settings, int localX = DEFAULT_POS, int localY = DEFAULT_POS,
		int width = DEFAULT_SIZE, int height = DEFAULT_SIZE, int localVelX = 0, int localVelY = 0) :
		Entity(texturePath, renderer, settings, localX, localY, width, height) {

		

	}

	~EntityMoving() {
	}
};

